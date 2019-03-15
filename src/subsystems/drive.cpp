#include "main.h"

using namespace okapi;

namespace drive
{

driveStates currState;

Motor driveL1(DRIVE_L1, false, AbstractMotor::gearset::green);
Motor driveL2(DRIVE_L2, false, AbstractMotor::gearset::green);
Motor driveR1(DRIVE_R1, false, AbstractMotor::gearset::green);
Motor driveR2(DRIVE_R2, false, AbstractMotor::gearset::green);

TimeUtil chassisUtil = TimeUtilFactory::withSettledUtilParams(50, 5, 100_ms);
TimeUtil profiledUtil = TimeUtilFactory::withSettledUtilParams(50, 5, 100_ms);

okapi::MotorGroup leftMotorGroup({DRIVE_L1, DRIVE_L2});
okapi::MotorGroup rightMotorGroup({DRIVE_R1, DRIVE_R2});

AsyncPosIntegratedController leftController(std::shared_ptr<MotorGroup>(&leftMotorGroup), chassisUtil);
AsyncPosIntegratedController rightController(std::shared_ptr<MotorGroup>(&rightMotorGroup), chassisUtil);

SkidSteerModel integratedChassisModel = ChassisModelFactory::create({DRIVE_L1, DRIVE_L2}, {-DRIVE_R1, -DRIVE_R2}, 200);
SkidSteerModel discreteChassisModel = ChassisModelFactory::create({DRIVE_L1, DRIVE_L2}, {-DRIVE_R1, -DRIVE_R2}, odometry::leftEnc, odometry::rightEnc, 200);

// ChassisScales integratedScale = std_initializer_list<ChassisScales>(4.125_in, 13.273906_in);
// ChassisScales discreteScale = std_initializer_list<ChassisScales>(2.75_in, 7.402083_in);

ChassisControllerIntegrated chassisController(
    chassisUtil,
    std::shared_ptr<SkidSteerModel>(&integratedChassisModel),
    std::unique_ptr<AsyncPosIntegratedController>(&leftController),
    std::unique_ptr<AsyncPosIntegratedController>(&rightController),
    AbstractMotor::gearset::green, {4.125_in, 13.274708_in});

AsyncMotionProfileController profileController(
    profiledUtil,
    1.00, // max vel
    2.0,  // max accel
    10.0, //max jerk
    std::shared_ptr<SkidSteerModel>(&integratedChassisModel),
    {4.125_in, 13.274708_in},
    AbstractMotor::gearset::green);

pathfollowing::AdaptivePurePursuit appc(
    std::make_unique<IterativePosPIDController>(0.05, 0.000, 0.00, 0, TimeUtilFactory::create(), std::make_unique<AverageFilter<5>>()),
    std::make_unique<IterativePosPIDController>(/*0.012*/ .012, 0.000, /*20.0*/ 0.0, 0.0, TimeUtilFactory::create(), std::make_unique<AverageFilter<5>>()),
    10, 20.0); // the number before the Kf is the lookahead global, but it will use the path's lookahead by default

// .055
// .8 0.0 0.01
void update()
{
    if (abs(controller.getAnalog(ControllerAnalog::leftY)) > joyDeadband ||
        abs(controller.getAnalog(ControllerAnalog::rightY)) > joyDeadband)
    {
        currState = running; // begin running drive once small threshold on joystick is reached
    }
}

void act(void *)
{
    while (true)
    {

        pros::lcd::print(0, "%f", drive::driveL1.getPosition());
        pros::lcd::print(1, "%c", drive::currState);

        switch (currState)
        {
        case notRunning: // the drive should not be moving; brake
            chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);
            chassisController.stop();
            break;

        case running: // the drive moves according to joysticks
            chassisController.tank(
                controller.getAnalog(ControllerAnalog::leftY) * 1.0,
                controller.getAnalog(ControllerAnalog::rightY) * 1.0,
                joyDeadband * 1.0);
            currState = notRunning;
            break;

        case yield: // for macro in order to take direct control of drive
            break;
        }

        pros::delay(10);
    }
}

// Helper function to facilitate turning during auton
void turn(QAngle angle, double maxVel, bool odom, bool async)
{
    drive::chassisController.setMaxVelocity(maxVel);
    if (async)
    {
        if (odom)
        {
            double angleError = std::atan2(sin(angle.convert(radian) - odometry::currAngle.convert(radian)), cos((angle.convert(radian) - odometry::currAngle.convert(radian))));
            drive::chassisController.turnAngleAsync(angleError * radian);
        }
        else
        {
            drive::chassisController.turnAngleAsync(angle);
        }
    }
    else
    {
        if (odom)
        {
            double angleError = std::atan2(sin(angle.convert(radian) - odometry::currAngle.convert(radian)), cos((angle.convert(radian) - odometry::currAngle.convert(radian))));
            drive::chassisController.turnAngle(angleError * radian);
            drive::chassisController.waitUntilSettled();
        }
        else
        {
            drive::chassisController.turnAngle(angle);
            drive::chassisController.waitUntilSettled();
        }
    }
    drive::chassisController.setMaxVelocity(200);
}

} // namespace drive

// Remove path to clear up memory
void removePaths(std::string path1)
{
    drive::profileController.removePath(path1);
}

// Remove 2 paths at once to clear up memory
void removePaths(std::string path1, std::string path2)
{
    drive::profileController.removePath(path1);
    drive::profileController.removePath(path2);
}