#include "main.h"

using namespace okapi;

ControllerButton angleCloseHigh = controller[ControllerDigital::down];
ControllerButton angleMidHighBtn = controller[ControllerDigital::up];
ControllerButton angleFarMidBtn = controller[ControllerDigital::left];
ControllerButton angleFarHighBtn = controller[ControllerDigital::right];

ControllerButton doubleShotNearBtn1 = controller[ControllerDigital::L1];
ControllerButton doubleShotNearBtn2 = controller[ControllerDigital::L2];

ControllerButton doubleShotFarBtn = controller[ControllerDigital::L2];

int macroTarget1;
int macroTarget2;

namespace macro
{

macroStates currState = none;

void update()
{
  if (angleCloseHigh.changedToPressed())
  {
    currState = anglerCH; // 350
  }
  if (angleMidHighBtn.changedToPressed())
  {
    currState = anglerMH; // 0
  }
  if (angleFarMidBtn.changedToPressed())
  {
    currState = anglerFM; // 305
  }
  if (angleFarHighBtn.changedToPressed())
  {
    currState = anglerFH; // 120
  }
  if (doubleShotNearBtn1.isPressed() && doubleShotNearBtn2.isPressed())
  {
    currState = doubleShotNear;
  }
  if (doubleShotFarBtn.isPressed())
  {
    currState = doubleShotFar;
  }
}

void act(void *)
{
  while (true)
  {
    switch (currState)
    {
    case none:
      break;
    case doubleShotNear:
      puncher::currState = puncher::cocking;
      // switches out of cocking when sensor value achieved

      angler::target = 0;
      angler::currState = angler::toTarget;
      // will switch out of toTarget automatically when target reached

      // should automatically stop when ball loads into puncher

      while (!puncher::isLoaded())
      {
        pros::delay(10);
        differential::currState = differential::intakeIn;
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler); // waits until angler to stop

      puncher::currState = puncher::shooting;
      waitUntilSettled(puncher::puncher);

      puncher::currState = puncher::cocking;

      angler::target = 120;
      angler::currState = angler::toTarget;

      while (!puncher::isLoaded())
      {
        pros::delay(10);
        differential::currState = differential::intakeIn;
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      puncher::currState = puncher::shooting;

      macro::currState = none;
      break;
    case doubleShotFar:

      puncher::currState = puncher::cocking;
      // switches out of cocking when sensor value achieved

      angler::target = 0;
      angler::currState = angler::toTarget;
      // will switch out of toTarget automatically when target reached

      while (!puncher::isLoaded())
      {
        pros::delay(10);
        differential::currState = differential::intakeIn;
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler); // waits until angler to stop

      puncher::currState = puncher::shooting;
      waitUntilSettled(puncher::puncher);

      puncher::currState = puncher::cocking;

      angler::target = 120;
      angler::currState = angler::toTarget;

      while (!puncher::isLoaded())
      {
        pros::delay(10);
        differential::currState = differential::intakeIn;
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler);

      puncher::currState = puncher::shooting;

      macro::currState = none;
      break;
    case customShotDouble:
      puncher::currState = puncher::cocking;
      // switches out of cocking when sensor value achieved

      angler::target = macroTarget1;
      angler::currState = angler::toTarget;
      // will switch out of toTarget automatically when target reached

      while (!puncher::isLoaded())
      {
        pros::delay(10);
        differential::currState = differential::intakeIn;
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler); // waits for angler to stop

      puncher::currState = puncher::shooting;
      waitUntilSettled(puncher::puncher);

      puncher::currState = puncher::cocking;

      angler::target = macroTarget2;
      angler::currState = angler::toTarget;

      while (!puncher::isLoaded())
      {
        pros::delay(10);
        differential::currState = differential::intakeIn;
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler);

      puncher::currState = puncher::shooting;

      macro::currState = none;
      break;
    case customShotSingle:
      puncher::currState = puncher::cocking;
      // switches out of cocking when sensor value achieved

      angler::target = macroTarget1;
      angler::currState = angler::toTarget;
      // will switch out of toTarget automatically when target reached

      while (!puncher::isLoaded())
      {
        pros::delay(10);
        differential::currState = differential::intakeIn;
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler); // waits for angler to stop

      puncher::currState = puncher::shooting;
      waitUntilSettled(puncher::puncher);

      macro::currState = none;

      break;
    case anglerCH:
      angler::target = 25;
      angler::currState = angler::toTarget;
      break;
    case anglerMH:
      angler::target = 0;
      angler::currState = angler::toTarget;
      break;
    case anglerFM:
      angler::target = 200;
      angler::currState = angler::toTarget;
      break;
    case anglerFH:
      angler::target = 95;
      angler::currState = angler::toTarget;
      break;
    }
    pros::delay(10);
  }
}

} // namespace macro

void customShotCall(int target1, int target2)
{
  macroTarget1 = target1;
  macroTarget2 = target2;

  macro::currState = macro::macroStates::customShotDouble;
}

void customShotCall(int target1) {
  macroTarget1 = target1;
  
  macro::currState = macro::macroStates::customShotSingle;
}