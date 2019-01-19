#include "main.h"

using namespace okapi;

namespace angler
{

anglerStates currState;

int target;

Motor angler(ANGLE_CHANGER_PORT, true, AbstractMotor::gearset::blue);

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
      angler.setBrakeMode(AbstractMotor::brakeMode::coast);
      angler.moveVoltage(0);
      break;
    case toTarget: // Sets angler position to given target
      angler.moveAbsolute(target, 600);
      waitUntilSettled(angler);
      currState = brake;
      break;
    case brake: // Shorts the motor terminals to replicate
                //PID hold without current use
      angler.setBrakeMode(AbstractMotor::brakeMode::brake);
      angler.moveVoltage(0);
      break;
    case yield: // yields to give the Macro state machine 
                // access to the angler
      break;
    }
    pros::delay(5);
  }
}

} // namespace angler
