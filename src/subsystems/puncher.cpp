#include "main.h"

using namespace okapi;

ControllerButton puncherShootBtn = controller[ControllerDigital::L1];
ControllerButton puncherCockingBtn = controller[ControllerDigital::L2];

namespace puncher
{

puncherStates currState;

Motor puncher(PUNCHER_PORT, true, AbstractMotor::gearset::red);

pros::ADILineSensor lineP(SPORT_PUNCHERB);

pros::ADILineSensor lineCock(SPORT_LINECOCK);

// uses line sensors to detect whether the puncher is pulled back for ball intake
bool isCocked()
{
  if (lineCock.get_value() > 2100)
  {
    return true;
  }
  return false;
}

// uses line sensors to detect whether a ball is on the puncher
bool isLoaded()
{
  if (lineP.get_value() < 2300)
  {
    return true;
  }
  return false;
}

void update()
{
  if (puncherShootBtn.isPressed() && !puncherCockingBtn.isPressed())
  {
    currState = shooting; // begin shooting on button press; will cock automatically after shooting
  }
  if (isCocked())
  {
    printf("big dick energy\n");
  }
}

void act(void *)
{
  while (true)
  {
    switch (currState)
    {
    case notRunning: // stop the puncher from moving
      puncher.setBrakeMode(AbstractMotor::brakeMode::coast);
      puncher.moveVoltage(0);
      break;
    case shooting: // turn the puncher gear to shoot the ball
      puncher.moveRelative(200, 100);
      waitUntilSettled(puncher);
      currState = cocking;
      break;
    case cocking: // pulls back the puncher until line sensors detect the puncher
      if (!isCocked())
      {
        puncher.moveVoltage(12000);
      }
      else
      {
        puncher.moveVoltage(0);
        currState = notRunning;
      }
      break;
    case fullSend: // turn the puncher gear to shoot the ball
      puncher.moveRelative(500, 100);
      waitUntilSettled(puncher);
      currState = cocking;
      break;
    case yield: // for macro in order to take direct control of puncher
      break;
    }
    pros::delay(10);
  }
}

} // namespace puncher
