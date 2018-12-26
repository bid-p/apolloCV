#include "main.h"

using namespace okapi;

enum {
  puncherNotRunning = 'x',
  puncherShooting = 's',
  puncherCocking = 'c',
} puncherState = puncherNotRunning;
enum {
  angleUp = 'u',
  angleDown = 'd',
  angleHold = 'h',
  angleNotRunning = 'x',
} angleState = angleNotRunning;
enum {
  macroReady = '0',
  macroFirstShot = '1',
  macroLoad = '2',
  macroBeginShot = '3',
  macroSecondShot = '4',
  macroNotRunning = 'x',
} macroState = macroNotRunning;

double angleTarget;

Motor puncher(PUNCHER_PORT, true, AbstractMotor::gearset::red);
Motor angleChanger(ANGLE_CHANGER_PORT, true, AbstractMotor::gearset::green);
AsyncPosIntegratedController angleController =
    AsyncControllerFactory::posIntegrated(angleChanger);
AsyncPosIntegratedController puncherController =
    AsyncControllerFactory::posIntegrated(puncher);

//ControllerButton angleFar1MidBtn = controller[ControllerDigital::left];
ControllerButton angleFarHighBtn = controller[ControllerDigital::right];
ControllerButton angleCloseMidBtn = controller[ControllerDigital::down];
ControllerButton angleCloseHighBtn = controller[ControllerDigital::up];

ControllerButton angleMidMidBtn = controller[ControllerDigital::X];
ControllerButton angleMidHighBtn = controller[ControllerDigital::B];

ControllerButton puncherOnBtn = controller[ControllerDigital::L1];
ControllerButton puncherCockingBtn = controller[ControllerDigital::L2];

ControllerButton macroAbort1Btn = controller[ControllerDigital::R1];
ControllerButton macroAbort2Btn = controller[ControllerDigital::R2];

char getPuncherState() { return puncherState; }

char getAngleState() { return angleState; }

void abortPuncher() {
  angleState = angleNotRunning;
  puncherState = puncherNotRunning;
}

int timeWait = 0;

void updateMacro() {
  // abort
  if(macroAbort1Btn.isPressed() && macroAbort2Btn.isPressed()) {
    macroState = macroNotRunning;
    return;
  }

  // actions
  switch(macroState) {
    case macroReady:
    angleTarget = 0;
    timeWait = 0;
    angleState = angleHold;
    break;
    case macroFirstShot:
    puncherState = puncherShooting;
    break;
    case macroLoad:
    loadBall();
    puncherState = puncherCocking;
    angleState = angleHold;
    angleTarget = 200; // mid flag
    break;
    case macroBeginShot:
    puncherState = puncherShooting;
    timeWait++;
    break;
    case macroSecondShot:
    puncherState = puncherShooting;
    break;
    case macroNotRunning:
    break;
  }

  // state transitions
  if(macroState == macroSecondShot && !isLoaded()) {
    macroState = macroNotRunning;
    puncherState = puncherNotRunning;
  }
  if(macroState == macroBeginShot && timeWait >= 50) { // the ball bounces around a little before isLoaded is true, so start the shot regardless of whether it is loaded
    macroState = macroSecondShot;
  }
  if(macroState == macroLoad && isLoaded() && abs(angleChanger.getPosition() - angleTarget) < 10) {
    macroState = macroBeginShot;
  }
  if(macroState == macroFirstShot && !isLoaded()) {
    macroState = macroLoad;
    puncher.tarePosition();
  }
  if(macroState == macroReady && abs(angleChanger.getPosition() - angleTarget) < 10) {
    macroState = macroFirstShot;
  }
}
void updatePuncher() {
  if(macroState != macroNotRunning) {
    updateMacro();
    return; // macro overrides normal updates
  }
  if (angleState != angleNotRunning) {
    angleState = angleHold;
  }
  if (puncherState != puncherCocking) {
    puncherState = puncherNotRunning;
  }
  if (angleCloseMidBtn.isPressed()) { //CHANGE TO CHANGEDTOPRESSED
    /*angleTarget = 200;
    angleState = angleHold;*/
    angleState = angleDown; // this is temporarily manual angle changing
  }
  if (angleCloseHighBtn.isPressed()) { //CHANGE TO CHANGEDTOPRESSED
    /*angleTarget = 0;
    angleState = angleHold;*/
    angleState = angleUp; // this is temporarily manual angle changing
  }
  if (angleFarHighBtn.changedToPressed()) {
    angleTarget = 95;
    angleState = angleHold;
  }
  if (puncherOnBtn.isPressed()) {
    puncherState = puncherShooting;
  }
  if (puncherCockingBtn.changedToPressed()) {
    puncher.tarePosition(); // the puncher motor has to be reset before it is
                            // set to the cocked position
    puncherState = puncherCocking;
  }
  if(puncherCockingBtn.isPressed() && puncherOnBtn.isPressed()) {
    macroState = macroReady;
  }
}

bool hold = false;

void puncherAct() {
  switch (angleState) {
  // no more manual angle changing
  case angleUp:
  angleChanger.moveVoltage(12000);
  angleTarget = angleChanger.getPosition();
  break;
  case angleDown:
  angleChanger.moveVoltage(-12000);
  angleTarget = angleChanger.getPosition();
  break;

  case angleHold: // hold only every other time when close, otherwise it stalls
    if (abs(angleChanger.getPosition() - angleTarget) < 10) {
      if (hold) {
        angleController.setTarget(angleTarget);
      } else {
        angleChanger.moveVoltage(0);
      }
    } else {
      angleController.setTarget(angleTarget); // when far just do pid everytime
                                              // (or else it doesn't go up)
    }
    hold = !hold;
    break;
  case angleNotRunning:
    angleChanger.moveVoltage(0);
    break;
  }
  switch (puncherState) {
  case puncherNotRunning:
    puncher.moveVoltage(0);
    break;
  case puncherShooting:
    puncher.moveVoltage(12000);
    break;
  case puncherCocking:
    puncherController.setTarget(400);
    break;
  }
}
