#include "main.h"

using namespace okapi;

bool running = false;

Motor driveL1(DRIVE_PORT_L1, false, AbstractMotor::gearset::green);
Motor driveL2(DRIVE_PORT_L2, false, AbstractMotor::gearset::green);
Motor driveR1(DRIVE_PORT_R1, false, AbstractMotor::gearset::green);
Motor driveR2(DRIVE_PORT_R2, false, AbstractMotor::gearset::green);

auto drive = ChassisControllerFactory::create(
	{DRIVE_PORT_L1, DRIVE_PORT_L2},
	{-DRIVE_PORT_R1, -DRIVE_PORT_R2},
	AbstractMotor::gearset::green,
	{4.125_in, 12.727_in}
);

Controller controller;

char getDriveState() {
  return running ? 'r' : 'x';
}

void abortDrive() {
  running = false;
}

void updateDrive() {
  if(controller.getAnalog(ControllerAnalog::leftY) != 0 || controller.getAnalog(ControllerAnalog::rightY) != 0) {
    running = true;
  } else {
    running = false;
  }
}

void driveAct() {
  drive.setBrakeMode(AbstractMotor::brakeMode::coast);
  if(running) {
      drive.tank(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightY));
  } else {
    drive.tank(0, 0);
  }
}
