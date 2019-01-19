#include "main.h"

using namespace okapi;

ControllerButton liftUpBtn = controller[ControllerDigital::A];
ControllerButton liftDownBtn = controller[ControllerDigital::Y];
ControllerButton intakeInBtn = controller[ControllerDigital::R1];
ControllerButton intakeOutBtn = controller[ControllerDigital::R2];

namespace differential
{

differentialStates currState;

Motor diffLeft(DIFF_PORT_L, false, AbstractMotor::gearset::green);
Motor diffRight(DIFF_PORT_R, true, AbstractMotor::gearset::green);

Timer timerBallBrake;
pros::ADILineSensor lineL(SPORT_INTAKE_L);
pros::ADILineSensor lineR(SPORT_INTAKE_R);

bool hasBall()
{
  if (lineL.get_value() < 2000 || lineR.get_value() < 2000)
  {
    return true;
  }
  return false;
} // Function that returns whether a ball has been detected in the intake

void update()
{
  // if (puncher::isLoaded())
  // {
  //   printf("loaded\n");
  // }

  // if (differential::hasBall())
  // {
  //   printf("has ball\n");
  // }

  // printf("greetings\n");

  // AUTOMATED CHECKERS
  /*if (currState == intakeIn && !puncher::isLoaded())
  {
    currState = intakeIn;
  } // if puncher isn't loaded, run intake
  if (currState == intakeIn && puncher::isLoaded() && !hasBall())
  {
    currState = intakeIn;
  } // if is loaded but doesn't have ball ready, keep running intake*/

  if (currState == intakeIn && puncher::isLoaded() && hasBall())
  {
    currState = ballBrake;
    timerBallBrake.getDt();
  } // Once balls have been detected in puncher & intake, run ball brake
  if (currState == ballBrake && timerBallBrake.getDt() <= 20_ms)
  {
    currState = notRunning;
  } // Reverses intake at 83.3% speed for 20ms so that ball doesn't
    // overshoot due to speed of the intake

  // USER INPUT
  if (intakeInBtn.isPressed() && intakeOutBtn.isPressed())
  {
    currState = liftHold;
  } // if both buttons are pressed, run lift PID
  if (liftUpBtn.isPressed())
  {
    currState = liftUp;
  }
  if (liftDownBtn.isPressed())
  {
    currState = liftDown;
  }
  if (intakeInBtn.isPressed() && !intakeOutBtn.isPressed())
  {
    currState = intakeIn;
  }
  if (intakeOutBtn.isPressed() && !intakeInBtn.isPressed())
  {
    currState = intakeOut;
  }
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
      diffLeft.moveVelocity(200);
      diffRight.moveVelocity(200);
      currState = notRunning;
      break;
    case liftDown: // Both differential motors same direction
      diffLeft.moveVelocity(-200);
      diffRight.moveVelocity(-200);
      currState = notRunning;
      break;
    case intakeIn:
      diffLeft.moveVoltage(-12000);
      diffRight.moveVoltage(12000);
      break;
    case intakeOut: // Reverses intake at 83.3% power
      diffLeft.moveVoltage(10000);
      diffRight.moveVoltage(-10000);
      currState = notRunning;
      break;
    case liftHold: // lift hold PID
      diffLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
      diffRight.setBrakeMode(AbstractMotor::brakeMode::hold);
      diffLeft.moveVoltage(0);
      diffRight.moveVoltage(0);
      break;
    case ballBrake:
      diffLeft.moveVoltage(10000);
      diffRight.moveVoltage(-10000);
      // Robot outtakes without yielding control back to notRunning state
      break;
    case intakeOutNY:
      diffLeft.moveVoltage(10000);
      diffRight.moveVoltage(-10000);
      // For use in auton, keeps intake running in the reverse
      // diretion to flip caps
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