#include "main.h"

using namespace okapi;

ControllerButton angleCloseHigh = controller[ControllerDigital::down];
ControllerButton angleMidHighBtn = controller[ControllerDigital::up];
ControllerButton angleFarMidBtn = controller[ControllerDigital::left];
ControllerButton angleFarHighBtn = controller[ControllerDigital::right];

namespace angler {

int nearTarget;
int farTarget;

anglerStates currState;

Motor angler(ANGLE_CHANGER_PORT, true, AbstractMotor::gearset::blue);

AsyncPosIntegratedController angleController =
    AsyncControllerFactory::posIntegrated(angler);

void update() {
  if (angleCloseHigh.changedToPressed()) {
    currState = closeHigh; // 350
  }
  if (angleMidHighBtn.changedToPressed()) {
    currState = midHigh; // 0
  }
  if (angleFarMidBtn.changedToPressed()) {
    currState = farMid; // 305
  }
  if (angleFarHighBtn.changedToPressed()) {
    currState = farHigh; // 120
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
    case closeHigh:
      angleController.setTarget(25);
      angleController.flipDisable(false);
      break;
    case midHigh:
      angleController.setTarget(0);
      angleController.flipDisable(false);
      break;
    case farMid:
      angleController.setTarget(200);
      angleController.flipDisable(false);
      break;
    case farHigh:
      angleController.setTarget(95);
      angleController.flipDisable(false);
      break;
    case autoAim:
      // nothing cuz theres no vision code yet lul
      break;
    }
    pros::delay(10);
  }
}

} // namespace angler
