#include "main.h"

using namespace okapi;

enum {
  diffLiftUp = 'u', // L1
  diffLiftDown = 'd', // L2
  diffIntakeIn = 'i', // R1
  diffIntakeOut = 'o', // R2
  diffNotRunning = 'x',
} diffState = diffNotRunning;

ControllerButton liftUp = controller[ControllerDigital::L1];
ControllerButton liftDown = controller[ControllerDigital::L2];
ControllerButton intakeIn = controller[ControllerDigital::R1];
ControllerButton intakeOut = controller[ControllerDigital::R2];

Motor diffLeft(DIFF_PORT_L, false, AbstractMotor::gearset::green);
Motor diffRight(DIFF_PORT_R, true, AbstractMotor::gearset::green);

char getDiffState() {
  return diffState;
}

void abortDiff() {
  diffState = diffNotRunning;
}

void updateDiff() {
  diffState = diffNotRunning;
  if(liftUp.isPressed()) {
    diffState = diffLiftUp;
  }
  if(liftDown.isPressed()) {
    diffState = diffLiftDown;
  }
  if(intakeIn.isPressed()) {
    diffState = diffIntakeIn;
  }
  if(intakeOut.isPressed()) {
    diffState = diffIntakeOut;
  }
}

void diffAct() {
  switch(diffState) {
    case diffLiftUp:
    diffLeft.moveVoltage(12000);
    diffRight.moveVoltage(12000);
    break;
    case diffLiftDown:
    diffLeft.moveVoltage(-12000);
    diffRight.moveVoltage(-12000);
    break;
    case diffIntakeIn:
    diffLeft.moveVoltage(-12000);
    diffRight.moveVoltage(12000);
    break;
    case diffIntakeOut:
    diffLeft.moveVoltage(9000);
    diffRight.moveVoltage(-9000);
    break;
    case diffNotRunning:
    diffLeft.moveVoltage(0);
    diffRight.moveVoltage(0);
    break;
  }
}
