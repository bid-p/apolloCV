#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

// ControllerButton abortBtn = controller[ControllerDigital::Y];

void states()
{
  pros::lcd::print(1, "Drive state: %c | Drive temp: %i", drive::currState, (int)drive::driveR1.getTemperature());
  pros::lcd::print(2, "Puncher state: %c | Puncher temp: %i", puncher::currState, (int)puncher::puncher.getTemperature());
  pros::lcd::print(3, "Puncher encoder: %i", (int)puncher::puncher.getPosition());
  pros::lcd::print(3, "Angle target: %i", (int)angler::target);
  pros::lcd::print(4, "Angle state: %c | Angle temp: %i", angler::currState, (int)angler::angler.getTemperature());
  pros::lcd::print(5, "Angle encoder: %i", (int)angler::angler.getPosition());
  pros::lcd::print(6, "Diff state: %c | Diff Left temp: %i", differential::currState, (int)differential::diffLeft.getTemperature());
  pros::lcd::print(7, "Macro state: %c", macro::currState);
}

void opcontrol()
{

  pros::lcd::initialize();

  // autonSelector();

  while (true)
  {
    drive::update();
    angler::update();
    puncher::update();
    differential::update();
    macro::update();

    states();

    pros::delay(5);
  }
}
