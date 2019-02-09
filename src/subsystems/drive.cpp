#include "main.h"

using namespace okapi;

namespace drive
{

driveStates currState;

Motor driveL1(DRIVE_PORT_L1, false, AbstractMotor::gearset::green);
Motor driveL2(DRIVE_PORT_L2, false, AbstractMotor::gearset::green);
Motor driveR1(DRIVE_PORT_R1, false, AbstractMotor::gearset::green);
Motor driveR2(DRIVE_PORT_R2, false, AbstractMotor::gearset::green);

ChassisControllerIntegrated chassisController =
    ChassisControllerFactory::create(
        {DRIVE_PORT_L1, DRIVE_PORT_L2}, {-DRIVE_PORT_R1, -DRIVE_PORT_R2},
        AbstractMotor::gearset::green, {4.125_in, 13.2054_in});

AsyncMotionProfileController profileController =
    AsyncControllerFactory::motionProfile(1.00, 2.0,
                                          10.0, // maxvel, accel, max jerk
                                          chassisController);

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

// helper function for turning in autonomous
void turnAngleVel(QAngle angle, double maxVel)
{
  drive::chassisController.setMaxVelocity(maxVel);
  drive::chassisController.turnAngle(angle);
  drive::chassisController.setMaxVelocity(200);
}

// helper function to remove profiled paths from memory two at a time
void removePaths(std::string path1, std::string path2)
{
  drive::profileController.removePath(path1);
  drive::profileController.removePath(path2);
}
