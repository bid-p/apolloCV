#include "main.h"

using namespace okapi;

namespace angler
{

anglerStates currState;

pros::Vision vision(SPORT_VISION, pros::E_VISION_ZERO_CENTER);

int target;

Motor angler(ANGLE_CHANGER_PORT, true, AbstractMotor::gearset::blue);

const double kP = 0;
const double kI = 0;
const double kD = 0;

IterativePosPIDController anglerController = IterativeControllerFactory::posPID(kP, kI, kD, 0, std::make_unique<AverageFilter<5>>());

void update()
{
  // work offloaded to Macro state machine
}

void act(void *)
{
  while (true)
  {
    switch (currState)
    {
    case notRunning: // Turns off angler
      anglerController.flipDisable(true);
      angler.setBrakeMode(AbstractMotor::brakeMode::coast);
      angler.moveVoltage(0);
      break;
    case toTarget: // Sets angler position to given target
      anglerController.flipDisable(true);
      angler.moveAbsolute(target, 600);
      // waitUntilSettled(angler, 5, 5, 10_ms);
      // currState = brake;
      break;
    case brake: // Shorts the motor terminals to replicate
                //PID hold without current use
      anglerController.flipDisable(true);
      angler.setBrakeMode(AbstractMotor::brakeMode::hold);
      angler.moveVoltage(0);
      break;
    case autoAim:
      anglerController.flipDisable(false);
      if (alliance == red)
      {
      }
      if (alliance == blue)
      {
      }
      break;
    case yield: // yields to give the Macro state machine
                // access to the angler
      anglerController.flipDisable(true);
      break;
    }
    pros::delay(10);
  }
}

} // namespace angler
