#include "main.h"

using namespace okapi;

ControllerButton liftUp = controller[ControllerDigital::A];
ControllerButton liftDown = controller[ControllerDigital::Y];
ControllerButton intakeIn = controller[ControllerDigital::R1];
ControllerButton intakeOut = controller[ControllerDigital::R2];
Motor diffLeft(DIFF_PORT_L, false, AbstractMotor::gearset::green);
Motor diffRight(DIFF_PORT_R, true, AbstractMotor::gearset::green);

pros::ADILineSensor lineL(SPORT_INTAKE_L);
pros::ADILineSensor lineR(SPORT_INTAKE_R);

pros::ADILineSensor lineP(SPORT_PUNCHERB);

enum {
  diffLiftUp = 'u',    // L1
  diffLiftDown = 'd',  // L2
  diffIntakeIn = 'i',  // R1
  diffIntakeOut = 'o', // R2
  diffNotRunning = 'x',
  diffLiftHold = 'a',
} diffState = diffNotRunning;

bool diffHoldToggle = true;

char getDiffState() { return diffState; }

void abortDiff() { diffState = diffNotRunning; }

bool hasBall() {
  if (lineL.get_value() < 2000 || lineR.get_value() < 2000) {
    return true;
  }
  return false;
}

bool isLoaded() {
  if (lineP.get_value() < 2000) {
    return true;
  }
  return false;
}

void updateDiff() {
  if (!isLoaded()) {
    diffState = diffIntakeIn;
  } // if isn't loaded, run intake
  if (isLoaded() && !hasBall()) {
    diffState = diffIntakeIn;
  } // if is loaded but doesn't have ball ready, keep running intake
  if (isLoaded() && hasBall()) {
    diffState = diffNotRunning;
  } // if has ball ready and is loaded, turn off intake
  diffState = diffNotRunning;
  if (liftUp.isPressed()) {
    diffState = diffLiftUp;
  }

  // AUTOMATED SHIT GETS OVERWRITTEN BY USER?

  if (liftDown.isPressed()) {
    diffState = diffLiftDown;
  }
  if (intakeIn.isPressed() && !intakeOut.isPressed()) {
    diffState = diffIntakeIn;
  }
  if (intakeOut.isPressed() && !intakeIn.isPressed()) {
    diffState = diffIntakeOut;
  }
  if (intakeIn.isPressed() && intakeOut.isPressed()) {
    diffState = diffLiftHold;
  }
}

void diffAct() {
  switch (diffState) {
  case diffNotRunning:
    diffLeft.moveVoltage(0);
    diffRight.moveVoltage(0);
    break;
  case diffLiftUp:
    diffLeft.moveVoltage(12000);
    diffRight.moveVoltage(12000);
    break;
  case diffLiftDown:
    diffLeft.moveVoltage(-12000);
    diffRight.moveVoltage(-12000);
    break;
  case diffIntakeIn:
    diffLeft.moveVelocity(-200);
    diffRight.moveVelocity(200);
    break;
  case diffIntakeOut:
    diffLeft.moveVelocity(-150);
    diffRight.moveVelocity(150);
    break;
  case diffLiftHold:
    diffLeft.moveVoltage(1500);
    diffRight.moveVoltage(1500);
    break;
  }
}

void runIntake(int speed) {
  diffLeft.moveVelocity(-1 * speed);
  diffRight.moveVelocity(1 * speed);
}
