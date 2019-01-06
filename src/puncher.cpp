#include "main.h"

using namespace okapi;

enum {
  puncherNotRunning = 'x',
  puncherShooting = 's',
  puncherCocking = 'c',
} puncherState = puncherNotRunning;
enum {
  /*angleUp = 'u',
  angleDown = 'd',*/
  angleHold = 'h',
  angleNotRunning = 'x',
} angleState = angleNotRunning;
enum {
  macroReady = '1',
  macroFirstShot = '2',
  macroLoad = '3',
  macroBeginShot = '4',
  macroSecondShot = '5',
  macroNotRunning = 'x',
} macroState = macroNotRunning;

double angleTarget;

Motor puncher(PUNCHER_PORT, true, AbstractMotor::gearset::red);
Motor angleChanger(ANGLE_CHANGER_PORT, true, AbstractMotor::gearset::green);
AsyncPosIntegratedController angleController =
    AsyncControllerFactory::posIntegrated(angleChanger);
AsyncPosIntegratedController puncherController =
    AsyncControllerFactory::posIntegrated(puncher);

ControllerButton angleFarMidBtn = controller[ControllerDigital::left];
ControllerButton angleFarHighBtn = controller[ControllerDigital::right];
ControllerButton angleCloseHighBtn = controller[ControllerDigital::down];
ControllerButton angleMidHighBtn = controller[ControllerDigital::up];

ControllerButton puncherOnBtn = controller[ControllerDigital::L1];
ControllerButton puncherCockingBtn = controller[ControllerDigital::L2];

ControllerButton macroAbort1Btn = controller[ControllerDigital::R1];
ControllerButton macroAbort2Btn = controller[ControllerDigital::R2];
ControllerButton macroFarBtn = controller[ControllerDigital::X];

Timer macroTimer;
Timer cockingTimer;

int macroHighTarget;
int macroMidTarget;

char getPuncherState() { return puncherState; }

char getAngleState() { return angleState; }

char getMacroState() { return macroState; }

void abortPuncher() {
  angleState = angleNotRunning;
  puncherState = puncherNotRunning;
}

void updateMacro() {
  // abort
  if(macroAbort1Btn.isPressed() && macroAbort2Btn.isPressed()) {
    macroState = macroNotRunning;
    return;
  }

  // actions
  switch(macroState) {
    case macroReady:
    angleTarget = macroHighTarget;
    angleState = angleHold;
    break;
    case macroFirstShot:
    puncherState = puncherShooting;
    break;
    case macroLoad:
    loadBall();
    puncherState = puncherCocking;
    angleState = angleHold;
    angleTarget = macroMidTarget; // mid flag
    break;
    case macroBeginShot:
    puncherState = puncherShooting;
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
  if(macroState == macroBeginShot && macroTimer.readDt() >= 300_ms) { // the ball bounces around a little before isLoaded is true, so start the shot regardless of whether it is loaded
    macroState = macroSecondShot;
  }
  if(macroState == macroLoad && isLoaded() && abs(angleChanger.getPosition() - angleTarget) < 5) {
    macroState = macroBeginShot;
    macroTimer.getDt();
  }
  if(macroState == macroFirstShot && !isLoaded()) {
    macroState = macroLoad;
    puncher.tarePosition();
    cockingTimer.getDt();
  }
  if(macroState == macroReady && abs(angleChanger.getPosition() - angleTarget) < 5) {
    macroState = macroFirstShot;
  }
}

void updatePuncher() {
  // default states
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

  //angler state transition
  if (angleCloseHighBtn.changedToPressed()) {
    angleTarget = 25;
    angleState = angleHold;
    //angleState = angleDown;
  }
  if(angleMidHighBtn.changedToPressed()) {
    angleTarget = 0;
    angleState = angleHold;
    //angleState = angleUp;
  }
  if (angleFarHighBtn.changedToPressed()) {
    angleTarget = 60;
    angleState = angleHold;
  }
  if(angleFarMidBtn.changedToPressed()) {
    angleTarget = 200;
    angleState = angleHold;
  }

  // puncher state transition
  if (puncherOnBtn.isPressed()) {
    puncherState = puncherShooting;
  }
  if (puncherCockingBtn.changedToPressed()) {
    puncher.tarePosition(); // the puncher motor has to be reset before it is
                            // set to the cocked position
    puncherState = puncherCocking;
    cockingTimer.getDt();
  }

  // start macro
  if(puncherCockingBtn.isPressed() && puncherOnBtn.isPressed()) {
    macroState = macroReady;
    macroHighTarget = 0;
    macroMidTarget = 125;
  }
  if(macroFarBtn.isPressed()) {
    macroState = macroReady;
    macroHighTarget = 70;
    macroMidTarget = 165;
  }
}

bool hold = false;

void puncherAct() {
  switch (angleState) {
  // no more manual angle changing
  /*case angleUp:
  angleChanger.moveVoltage(5000);
  angleTarget = angleChanger.getPosition();
  break;
  case angleDown:
  angleChanger.moveVoltage(-5000);
  angleTarget = angleChanger.getPosition();
  break;
*/
  case angleHold: // hold only every other time when close, otherwise it stalls
    if (abs(angleChanger.getPosition() - angleTarget) < 5) {
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
    if(cockingTimer.readDt() <= 500_ms) { // time based cocking
      puncher.moveVoltage(12000);
    } else {
      puncher.moveVoltage(0);
    }
    break;
  }
}

Timer timeOutMacro;

// for auton
void runNearMacro() {
  macroState = macroReady;
  timeOutMacro.getDt();
  macroHighTarget = 30;
  macroMidTarget = 125;
  while(macroState != macroNotRunning && timeOutMacro.readDt() < 2500_ms) {
    updateMacro();

    puncherAct();
    diffAct();
  }
}

// for auton
void runFarMacro() {
  macroState = macroReady;
  timeOutMacro.getDt();
  macroHighTarget = 70;
  macroMidTarget = 180;
  while(macroState != macroNotRunning && timeOutMacro.readDt() < 2500_ms) {
    updateMacro();

    puncherAct();
    diffAct();
  }
}
