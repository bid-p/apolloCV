#include "main.h"

using namespace okapi;

ControllerButton angleCloseHigh = controller[ControllerDigital::down];
ControllerButton angleCloseMidBtn = controller[ControllerDigital::up];
ControllerButton angleFarMidBtn = controller[ControllerDigital::left];
ControllerButton angleFarHighBtn = controller[ControllerDigital::right];

ControllerButton singleShotBtn = controller[ControllerDigital::L1];
ControllerButton doubleShotNearBtn = controller[ControllerDigital::L2];
ControllerButton doubleShotFarBtn = controller[ControllerDigital::X];

ControllerButton liftHoldBtn = controller[ControllerDigital::B];

ControllerButton right1 = controller[ControllerDigital::R1];
ControllerButton right2 = controller[ControllerDigital::R2];

int macroTarget1; // target encoder values for angler to shoot first flag in macro
int macroTarget2; // target encoder value for angler to shoot second flag in macro

namespace macro
{

macroStates currState = none;

void update()
{
  if (angleCloseHigh.changedToPressed())
  {
    currState = anglerCH;
  }
  if (angleCloseMidBtn.changedToPressed())
  {
    currState = anglerCM;
  }
  if (angleFarMidBtn.changedToPressed())
  {
    currState = anglerFM;
  }
  if (angleFarHighBtn.changedToPressed())
  {
    currState = anglerFH;
  }
  if (singleShotBtn.changedToPressed())
  {
    currState = singleShot;
  }
  if (doubleShotNearBtn.changedToPressed())
  {
    customShotCall(0, 90);
  }
  if (doubleShotFarBtn.changedToPressed())
  {
    customShotCall(25, 77);
  }
  if (liftHoldBtn.changedToPressed())
  {
    differential::liftTarget = 250;
    currState = liftToTarget;
  } // if Button B pressed, engage lift PID
  if (right1.isPressed() && right2.isPressed())
  {
    currState = poleAlign;
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
    case singleShot: // shoots a single flag with a single given target encoder value for that flag; for autonomous
      puncher::currState = puncher::cocking;
      // switches out of cocking when sensor value achieved

      // differential::currState = differential::intakeIn;
      // while (!puncher::isLoaded())
      // {
      //   pros::delay(2);
      // } // waits for puncher to load
      // differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler, 50, 5, 10_ms); // waits until angler to stop

      puncher::currState = puncher::shooting;

      macro::currState = none;
      break;
    case customShotDouble: // shoots two flags with the specified target encoder values for those flags; for autonomous
      puncher::currState = puncher::cocking;
      // switches out of cocking when sensor value achieved

      angler::target = macroTarget1;
      angler::currState = angler::toTarget;
      // will switch out of toTarget automatically when target reached

      // should automatically stop when ball loads into puncher

      differential::currState = differential::intakeIn;
      while (!puncher::isLoaded())
      {
        pros::delay(2);
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler, 50, 5, 10_ms); // waits until angler to stop

      puncher::currState = puncher::shooting;

      while (puncher::currState != puncher::cocking)
      {
        pros::delay(2);
      }

      angler::target = macroTarget2;
      angler::currState = angler::toTarget;

      differential::currState = differential::intakeIn;
      while (!puncher::isLoaded())
      {
        pros::delay(2);
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler, 50, 5, 10_ms); // waits until angler to stop

      puncher::currState = puncher::shooting;

      macro::currState = none;
      break;
    case doubleShotNoWait:
      puncher::currState = puncher::cocking;
      // switches out of cocking when sensor value achieved

      angler::target = macroTarget1;
      angler::currState = angler::toTarget;
      // will switch out of toTarget automatically when target reached

      // should automatically stop when ball loads into puncher

      differential::currState = differential::intakeIn;
      while (!puncher::isLoaded())
      {
        pros::delay(2);
      } // waits for puncher to load
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler, 50, 5, 10_ms); // waits until angler to stop

      puncher::currState = puncher::shooting;

      while (puncher::currState != puncher::cocking)
      {
        pros::delay(2);
      }

      angler::target = macroTarget2;
      angler::currState = angler::toTarget;

      differential::currState = differential::intakeIn;
      pros::delay(1000); // doesn't wait for ball to be loaded, because it may or may not be there
      if (!puncher::isLoaded())
      {
        macro::currState = none;
        break; // if puncher not loaded do not shoot again
      }
      differential::currState = differential::notRunning;

      waitUntilSettled(angler::angler, 50, 5, 10_ms); // waits until angler to stop

      puncher::currState = puncher::shooting;

      macro::currState = none;
      break;
    case anglerCH: // changes the angler to target the high flag from the close tile
      angler::target = 0;
      angler::currState = angler::toTarget;
      break;
    case anglerCM: // changes the angler to target the high flag from the middle tile
      angler::target = 90;
      angler::currState = angler::toTarget;
      break;
    case anglerFM: // changes the angler to target the middle flag from the far tile
      angler::target = 77;
      angler::currState = angler::toTarget;
      break;
    case anglerFH: // changes the angler to target the high flag from the far title
      angler::target = 25;
      angler::currState = angler::toTarget;
      break;
    case liftToTarget:
      differential::currState = differential::targetTransition;

      while ((differential::liftVal <= differential::liftTarget - 10) && (differential::liftVal >= differential::liftTarget + 10))
      {
        pros::delay(10);
      }

      differential::currState = differential::liftHold;
      break;
    case poleAlign:
      drive::chassisController.moveDistance(-10_in);

      differential::liftTarget = 250;

      differential::currState = differential::targetTransition;

      while ((differential::liftVal <= differential::liftTarget - 10) && (differential::liftVal >= differential::liftTarget + 10))
      {
        pros::delay(10);
      }

      differential::currState = differential::liftHold;

      drive::chassisController.waitUntilSettled();

      differential::liftTarget = 3600;

      differential::currState = differential::targetTransition;

      while ((differential::liftVal <= differential::liftTarget - 10) && (differential::liftVal >= differential::liftTarget + 10))
      {
        pros::delay(10);
      }

      differential::currState = differential::notRunning;
      break;
    }
    pros::delay(10);
  }
}

} // namespace macro

// overloaded function: two arguments means two shots
void customShotCall(int target1, int target2, bool noWait)
{
  macroTarget1 = target1;
  macroTarget2 = target2;

  if (noWait)
  {
    macro::currState = macro::macroStates::doubleShotNoWait;
  }
  else
  {
    macro::currState = macro::macroStates::customShotDouble;
  }
}

// overloaded function: one argument means single shot
void customShotCall(int target1)
{
  macroTarget1 = target1;

  macro::currState = macro::macroStates::singleShot;
}