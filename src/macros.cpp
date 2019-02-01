#include "main.h"

using namespace okapi;

ControllerButton angleCloseHigh = controller[ControllerDigital::down];
ControllerButton angleMidHighBtn = controller[ControllerDigital::up];
ControllerButton angleFarMidBtn = controller[ControllerDigital::left];
ControllerButton angleFarHighBtn = controller[ControllerDigital::right];

ControllerButton doubleShotNearBtn1 = controller[ControllerDigital::L1];
ControllerButton doubleShotNearBtn2 = controller[ControllerDigital::L2];

ControllerButton doubleShotFarBtn = controller[ControllerDigital::X];

int macroTarget1; // target encoder values for angler to shoot first flag in macro
int macroTarget2; // target encoder value for angler to shoot second flag in macro

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
    case none: // macro is not activated
      break;
    case doubleShotNear: // shoots two flags from the near tile; for driver control
      puncher::currState = puncher::cocking;
      // switches out of cocking when sensor value achieved

      angler::target = 0;
      angler::currState = angler::toTarget;
      // will switch out of toTarget automatically when target reached

      // should automatically stop when ball loads into puncher

      differential::currState = differential::intakeIn;
      while (!puncher::isLoaded())
      {
        pros::delay(2);
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler); // waits until angler to stop

      puncher::currState = puncher::shooting;
      // waitUntilSettled(puncher::puncher);
      while (puncher::isLoaded())
      {
        pros::delay(2);
      }

      puncher::currState = puncher::cocking;

      angler::target = 120;
      angler::currState = angler::toTarget;

      differential::currState = differential::intakeIn;
      while (!puncher::isLoaded())
      {
        pros::delay(2);
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

      // should automatically stop when ball loads into puncher

      while (!puncher::isLoaded())
      {
        pros::delay(2);
        differential::currState = differential::intakeIn;
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler); // waits until angler to stop

      puncher::currState = puncher::shooting;
      // waitUntilSettled(puncher::puncher);
      while (puncher::isLoaded())
      {
        pros::delay(2);
      }

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
    case customShotDouble: // shoots two flags with the specified target encoder values for those flags; for autonomous
      puncher::currState = puncher::cocking;
      // switches out of cocking when sensor value achieved

      angler::target = 0;
      angler::currState = angler::toTarget;
      // will switch out of toTarget automatically when target reached

      // should automatically stop when ball loads into puncher

      while (!puncher::isLoaded())
      {
        pros::delay(2);
        differential::currState = differential::intakeIn;
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler); // waits until angler to stop

      puncher::currState = puncher::shooting;
      // waitUntilSettled(puncher::puncher);
      while (puncher::isLoaded())
      {
        pros::delay(2);
      }

      puncher::currState = puncher::cocking;

      angler::target = 120;
      angler::currState = angler::toTarget;

      while (!puncher::isLoaded())
      {
        pros::delay(2);
        differential::currState = differential::intakeIn;
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      puncher::currState = puncher::shooting;

      macro::currState = none;
      break;
    case customShotSingle: // shoots a single flag with a single given target encoder value for that flag; for autonomous
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
      while (puncher::isLoaded())
      {
        pros::delay(2);
      }

      macro::currState = none;
      break;
    case anglerCH: // changes the angler to target the high flag from the close tile
      angler::target = 25;
      angler::currState = angler::toTarget;
      break;
    case anglerMH: // changes the angler to target the high flag from the middle tile
      angler::target = 0;
      angler::currState = angler::toTarget;
      break;
    case anglerFM: // changes the angler to target the middle flag from the far tile
      angler::target = 200;
      angler::currState = angler::toTarget;
      break;
    case anglerFH: // changes the angler to target the high flag from the far title
      angler::target = 95;
      angler::currState = angler::toTarget;
      break;
    }
    pros::delay(10);
  }
}

} // namespace macro

// overloaded function: two arguments means two shots
void customShotCall(int target1, int target2)
{
  macroTarget1 = target1;
  macroTarget2 = target2;

  macro::currState = macro::macroStates::customShotDouble;
}

// overloaded function: one argument means single shot
void customShotCall(int target1)
{
  macroTarget1 = target1;

  macro::currState = macro::macroStates::customShotSingle;
}