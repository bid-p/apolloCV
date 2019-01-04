#include "main.h"

using namespace okapi;

ControllerButton angleFar1MidBtn = controller[ControllerDigital::left];
ControllerButton angleFar1HighBtn = controller[ControllerDigital::right];
ControllerButton angleCloseMidBtn = controller[ControllerDigital::down];
ControllerButton angleCloseHighBtn = controller[ControllerDigital::up];
ControllerButton angleFar2MidBtn = controller[ControllerDigital::B];

namespace angler {

tAnglerStates currState;

Motor angler(ANGLE_CHANGER_PORT, true, AbstractMotor::gearset::green);

AsyncPosIntegratedController angleController =
    AsyncControllerFactory::posIntegrated(angler);

void update() {
  if (angleCloseMidBtn.changedToPressed()) {
    currState = closeMid; // 350
  }
  if (angleCloseHighBtn.changedToPressed()) {
    currState = closeHigh; // 0
  }
  if (angleFar1MidBtn.changedToPressed()) {
    currState = far1Mid; // 305
  }
  if (angleFar1HighBtn.changedToPressed()) {
    currState = far1High; // 120
  }
  if (angleFar2MidBtn.changedToPressed()) {
    currState = far2Mid; // 245
  }
}

void act(void *) {
  while (true) {
    switch (currState) {
    case notRunning:
      angleController.flipDisable(true);
      angler.setBrakeMode(AbstractMotor::brakeMode::coast);
      angler.moveVoltage(0);
      break;
    case closeMid:
      angleController.setTarget(350);
      angleController.flipDisable(false);
      break;
    case closeHigh:
      angleController.setTarget(0);
      angleController.flipDisable(false);
      break;
    case far1Mid:
      angleController.setTarget(305);
      angleController.flipDisable(false);
      break;
    case far1High:
      angleController.setTarget(120);
      angleController.flipDisable(false);
      break;
    case far2Mid:
      angleController.setTarget(245);
      angleController.flipDisable(false);
      break;
    }
    pros::delay(10);
  }
}

} // namespace angler
