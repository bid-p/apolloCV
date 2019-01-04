#include "main.h"

using namespace okapi;

ControllerButton puncherShootBtn = controller[ControllerDigital::L1];
ControllerButton puncherCockingBtn = controller[ControllerDigital::L2];

namespace puncher {

tPuncherStates currState;

Motor puncher(PUNCHER_PORT, true, AbstractMotor::gearset::green);

AsyncPosIntegratedController puncherController =
    AsyncControllerFactory::posIntegrated(puncher);

pros::ADILineSensor lineP(SPORT_PUNCHERB);

bool isLoaded() {
  if (lineP.get_value() < 2000) {
    return true;
  }
  return false;
}

void update() {
  if (puncherShootBtn.isPressed()) {
    currState = shooting;
  }
  if (puncherCockingBtn.changedToPressed()) {
    puncher.tarePosition(); // puncher has to be reset before cocked
    currState = cocking;
  }
}

void act(void *) {
  while (true) {
    switch (currState) {
    case notRunning:
      puncherController.flipDisable(true);
      puncher.setBrakeMode(AbstractMotor::brakeMode::coast);
      puncher.moveVoltage(0);
      break;
    case shooting:
      puncherController.flipDisable(true);
      puncher.moveVoltage(12000);
      currState = notRunning;
      break;
    case cocking:
      puncherController.setTarget(250);
      puncherController.flipDisable(false);
      break;
    }
    pros::delay(10);
  }
}

} // namespace puncher
