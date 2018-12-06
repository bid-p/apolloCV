#include "main.h"

using namespace okapi;

enum {
  puncherNotRunning = 'x',
  puncherShooting = 's',
  puncherCocking = 'c',
} puncherState = puncherNotRunning;
enum {
  //angleUp = 'u',
  //angleDown = 'd',
  angleHold = 'h',
  angleNotRunning = 'x',
} angleState = angleNotRunning;

double angleTarget;

Motor puncher(PUNCHER_PORT, true, AbstractMotor::gearset::red);
Motor angleChanger(ANGLE_CHANGER_PORT, true, AbstractMotor::gearset::green);
AsyncPosIntegratedController angleController = AsyncControllerFactory::posIntegrated(angleChanger);
AsyncPosIntegratedController puncherController = AsyncControllerFactory::posIntegrated(puncher);

ControllerButton angleFar1MidBtn = controller[ControllerDigital::left];
ControllerButton angleFar1HighBtn = controller[ControllerDigital::right];
ControllerButton angleCloseMidBtn = controller[ControllerDigital::down];
ControllerButton angleCloseHighBtn = controller[ControllerDigital::up];


ControllerButton angleFar2MidBtn = controller[ControllerDigital::B];

ControllerButton puncherOnBtn = controller[ControllerDigital::L1];
ControllerButton puncherCockingBtn = controller[ControllerDigital::L2];

char getPuncherState() {
  return puncherState;
}

char getAngleState() {
  return angleState;
}

void abortPuncher() {
  angleState = angleNotRunning;
  puncherState = puncherNotRunning;
}

void updatePuncher() {
  if(angleState != angleNotRunning) {
    angleState = angleHold;
  }
  if(puncherState != puncherCocking) {
    puncherState = puncherNotRunning;
  }
  if(angleFar2MidBtn.changedToPressed()) {
    angleTarget = 245;
    angleState = angleHold;
  }
  if(angleCloseMidBtn.changedToPressed()) {
    angleTarget = 350;
    angleState = angleHold;
  }
  if(angleCloseHighBtn.changedToPressed()) {
    angleTarget = 0;
    angleState = angleHold;
  }
  if(angleFar1MidBtn.changedToPressed()) {
    angleTarget = 305;
    angleState = angleHold;
  }
  if(angleFar1HighBtn.changedToPressed()) {
    angleTarget = 120;
    angleState = angleHold;
  }
  if(puncherOnBtn.isPressed()) {
    puncherState = puncherShooting;
  }
  if(puncherCockingBtn.changedToPressed()) {
    puncher.tarePosition(); // the puncher motor has to be reset before it is set to the cocked position
    puncherState = puncherCocking;
  }
}

bool hold = false;

void puncherAct() {
  switch(angleState) {
    // no more manual angle changing
    /*case angleUp:
    angleChanger.moveVoltage(12000);
    angleTarget = angleChanger.getPosition();
    break;
    case angleDown:
    angleChanger.moveVoltage(-12000);
    angleTarget = angleChanger.getPosition();
    break;
    */
    case angleHold: // hold only every other time when close, otherwise it stalls
    if(abs(angleChanger.getPosition() - angleTarget) < 10) {
      if(hold) {
        angleController.setTarget(angleTarget);
      } else {
        angleChanger.moveVoltage(0);
      }
    } else {
      angleController.setTarget(angleTarget); // when far just do pid everytime (or else it doesn't go up)
    }
    hold = !hold;
    break;
    case angleNotRunning:
    angleChanger.moveVoltage(0);
    break;
  }
  switch(puncherState) {
    case puncherNotRunning:
    puncher.moveVoltage(0);
    break;
    case puncherShooting:
    puncher.moveVoltage(12000);
    break;
    case puncherCocking:
    puncherController.setTarget(250);
    break;
  }
}
