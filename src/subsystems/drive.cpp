#include "main.h"

using namespace okapi;

namespace drive {

driveStates currState;

char stateIndicator;

Motor driveL1(DRIVE_PORT_L1, false, AbstractMotor::gearset::green);
Motor driveL2(DRIVE_PORT_L2, false, AbstractMotor::gearset::green);
Motor driveR1(DRIVE_PORT_R1, false, AbstractMotor::gearset::green);
Motor driveR2(DRIVE_PORT_R2, false, AbstractMotor::gearset::green);

ChassisControllerIntegrated chassisController =
    ChassisControllerFactory::create(
        {DRIVE_PORT_L1, DRIVE_PORT_L2}, {-DRIVE_PORT_R1, -DRIVE_PORT_R2},
        AbstractMotor::gearset::green, {4.125_in, 12.727_in});

AsyncMotionProfileController profileController =
    AsyncControllerFactory::motionProfile(/*1.09*/ 2.00, 5.0,
                                          10.0, // maxvel, accel, max jerk
                                          chassisController);

void update() {
  if (abs(controller.getAnalog(ControllerAnalog::leftY)) > joyDeadband ||
      abs(controller.getAnalog(ControllerAnalog::rightY)) > joyDeadband) {
    currState = running;
    stateIndicator = 'r';
  } else {
    currState = notRunning;
    stateIndicator = 'x';
  }
}

void act(void *) {
  while (true) {
    switch (currState) {
    case notRunning:
      chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);
      chassisController.tank(0, 0, 0);
      break;

    case running:
      chassisController.tank(
          controller.getAnalog(ControllerAnalog::leftY) * 1.0,
          controller.getAnalog(ControllerAnalog::rightY) * 1.0,
          joyDeadband * 1.0);
      currState = notRunning;
      break;
    }
    pros::delay(10);
  }
}

} // namespace drive

void turnAngleVel(QAngle angle, double maxVel) {
  drive::chassisController.setMaxVelocity(maxVel);
  drive::chassisController.turnAngle(angle);
  drive::chassisController.setMaxVelocity(200);
}
