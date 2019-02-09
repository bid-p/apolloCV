#include "main.h"

using namespace okapi;

ControllerButton liftUpBtn = controller[ControllerDigital::A];
ControllerButton liftDownBtn = controller[ControllerDigital::Y];
ControllerButton intakeInBtn = controller[ControllerDigital::R1];
ControllerButton intakeOutBtn = controller[ControllerDigital::R2];
ControllerButton liftHoldBtn = controller[ControllerDigital::B];

namespace differential
{

differentialStates currState;

Motor diffLeft(DIFF_PORT_L, true, AbstractMotor::gearset::green);
Motor diffRight(DIFF_PORT_R, false, AbstractMotor::gearset::green);

Timer timerBallBrake;
pros::ADILineSensor lineL(SPORT_INTAKE_L);
// pros::ADILineSensor lineR(SPORT_INTAKE_R);

Potentiometer liftPot(SPORT_LIFT);
AverageFilter<5> liftPotFilter;

int liftVal;

bool hasBall()
{
  if (lineL.get_value() < 2300 /* || lineR.get_value() < 2000*/)
  {
    return true;
  }
  return false;
} // Function that returns whether a ball has been detected in the intake

void update()
{
  liftVal = liftPotFilter.filter(liftPot.get());

  // AUTOMATED CHECKERS
  if (currState == intakeIn && !puncher::isLoaded() && hasBall())
  {
    currState = ballDecel;
  }
  // if (currState == ballDecel && !intakeInBtn.isPressed())
  // {
  //   currState = notRunning;
  // }
  if (currState == ballDecel && puncher::isLoaded())
  {
    currState = intakeIn;
  }

  if (currState == intakeIn && puncher::isLoaded() && hasBall())
  {
    currState = ballBrake;
    timerBallBrake.getDt();
  } // Once balls have been detected in puncher & intake, run ball brake
  if (currState == ballBrake && timerBallBrake.readDt() >= 20_ms)
  {
    currState = notRunning;
  } // Reverses intake at 83.3% speed for 20ms so that ball doesn't
  // overshoot due to speed of the intake

  // bool liftInRange = (liftVal >= 90 || liftVal <= 110);
  if (currState == capHoldTransition && (liftVal >= 90 && liftVal <= 110))
  {
    currState = liftHold;
  }

  // USER INPUT
  if (liftUpBtn.isPressed())
  {
    currState = liftUp;
  }
  if (liftDownBtn.isPressed())
  {
    currState = liftDown;
  }
  if (currState == notRunning && intakeInBtn.isPressed() && !intakeOutBtn.isPressed())
  {
    currState = intakeIn;
  }
  if (intakeOutBtn.isPressed() && !intakeInBtn.isPressed())
  {
    currState = intakeOut;
  }
  if (liftHoldBtn.changedToPressed())
  {
    currState = capHoldTransition;
  } // if Button B pressed, engage lift PID
}

void act(void *)
{
  while (true)
  {
    switch (currState)
    {
    case notRunning:
      diffLeft.setBrakeMode(AbstractMotor::brakeMode::coast);
      diffRight.setBrakeMode(AbstractMotor::brakeMode::coast);
      diffLeft.moveVoltage(0);
      diffRight.moveVoltage(0);
      break;
    case liftUp: // Both differential motors same direction
      diffLeft.moveVelocity(-200);
      diffRight.moveVelocity(-200);
      currState = notRunning;
      // currState = liftHold;
      break;
    case liftDown: // Both differential motors same direction
      diffLeft.moveVelocity(200);
      diffRight.moveVelocity(200);
      currState = notRunning;
      // currState = liftHold;
      break;
    case intakeIn:
      diffLeft.moveVoltage(-12000);
      diffRight.moveVoltage(12000);
      // currState = notRunning;
      break;
    case intakeOut: // Reverses intake at 83.3% power
      diffLeft.moveVoltage(10000);
      diffRight.moveVoltage(-10000);
      currState = notRunning;
      break;
    case liftHold: // lift hold PID
      diffLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
      diffRight.setBrakeMode(AbstractMotor::brakeMode::hold);
      diffLeft.moveVelocity(0);
      diffRight.moveVelocity(0);
      break;
    case ballBrake:
      diffLeft.moveVoltage(10000);
      diffRight.moveVoltage(-10000);
      // Robot outtakes without yielding control back to notRunning state
      break;
    case ballDecel:
      diffLeft.moveVoltage(-5200);
      diffRight.moveVoltage(5200);
      // Robot intakes slower
      break;
    case intakeOutNY:
      diffLeft.moveVoltage(10000);
      diffRight.moveVoltage(-10000);
      // For use in auton, keeps intake running in the reverse
      // direction to flip caps
      break;
    case capHoldTransition:
      if (liftVal <= 100)
      {
        diffLeft.moveVoltage(-10000);
        diffRight.moveVoltage(-10000);
      }
      if (liftVal >= 100)
      {
        diffLeft.moveVoltage(10000);
        diffRight.moveVoltage(10000);
      }
      break;
    case yield:
      break;
    }

    pros::delay(10);
  }
}

} // namespace differential

void runIntake(int speed)
{
  differential::diffLeft.moveVelocity(-1 * speed);
  differential::diffRight.moveVelocity(1 * speed);
}