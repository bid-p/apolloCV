#include "main.h"

using namespace okapi;

ControllerButton puncherShootBtn = controller[ControllerDigital::L1];
ControllerButton puncherCockingBtn = controller[ControllerDigital::L2];

namespace puncher
{

puncherStates currState;

Motor puncher(PUNCHER_PORT, true, AbstractMotor::gearset::red);

// AsyncPosIntegratedController puncherController =
//     AsyncControllerFactory::posIntegrated(puncher);

pros::ADILineSensor lineP(SPORT_PUNCHERB);

pros::ADILineSensor lineCock(SPORT_LINECOCK);

bool isCocked()
{
  if (lineCock.get_value() > 2200)
  {
    return true;
  }
  return false;
}

bool isLoaded()
{
  if (lineP.get_value() < 2000)
  {
    return true;
  }
  return false;
}

void update()
{
  if (puncherShootBtn.isPressed() && !puncherCockingBtn.isPressed())
  {
    currState = shooting;
  }
  // if (puncherCockingBtn.changedToPressed())
  // {
  //   puncher.tarePosition(); // puncher has to be reset before cocked
  //   currState = cocking;
  // }
}

void act(void *)
{
  while (true)
  {
    switch (currState)
    {
    case notRunning:
      puncher.setBrakeMode(AbstractMotor::brakeMode::coast);
      puncher.moveVoltage(0);
      break;
    case shooting:
      puncher.moveRelative(360, 100);
      waitUntilSettled(puncher);
      currState = cocking;
      break;
    case cocking:
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
    case yield:
      break;
    }
    pros::delay(10);
  }
}

} // namespace puncher
