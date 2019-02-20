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

SkidSteerModel chassisModel = ChassisModelFactory::create({DRIVE_L1, DRIVE_L2}, {-DRIVE_R1, -DRIVE_R2}, 200);

ChassisControllerIntegrated chassisController(
    chassisUtil,
    std::shared_ptr<SkidSteerModel>(&chassisModel),
    std::unique_ptr<AsyncPosIntegratedController>(&leftController),
    std::unique_ptr<AsyncPosIntegratedController>(&rightController),
    AbstractMotor::gearset::green, {4.125_in, 13.273906_in});

AsyncMotionProfileController profileController(
    profiledUtil,
    1.00, // max vel
    2.0,  // max accel
    10.0, //max jerk
    std::shared_ptr<SkidSteerModel>(&chassisModel),
    {4.125_in, 13.2054_in},
    AbstractMotor::gearset::green);

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
            chassisController.tank(0, 0, 0);
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

} // namespace drive

// Helper function to facilitate turning during auton
void turnAngleVel(QAngle angle, double maxVel)
{
    drive::chassisController.setMaxVelocity(maxVel);
    drive::chassisController.turnAngle(angle);
    drive::chassisController.waitUntilSettled();
    drive::chassisController.setMaxVelocity(200);
}

void turnAngleVel(QAngle angle, double maxVel, bool async)
{
    drive::chassisController.setMaxVelocity(maxVel);
    if (async)
    {
        drive::chassisController.turnAngleAsync(angle);
        drive::chassisController.waitUntilSettled();
    }
    else
    {
        drive::chassisController.turnAngle(angle);
        drive::chassisController.waitUntilSettled();
    }
    drive::chassisController.setMaxVelocity(200);
}

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