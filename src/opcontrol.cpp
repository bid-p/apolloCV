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
  double x = odometry::currX.convert(okapi::inch);
  double y = odometry::currY.convert(okapi::inch);
  double angle = odometry::currAngle.convert(okapi::degree);

  // pros::lcd::print(1, "Drive state: %c | Drive temp: %d", drive::currState, (int)drive::driveR1.getTemperature());
  // pros::lcd::print(2, "Puncher state: %c | Puncher temp: %d", puncher::currState, (int)puncher::puncher.getTemperature());
  pros::lcd::print(7, "Ang Target: %d | Ang Enc: %d | Ang Temp: %d", (int)angler::target, (int)angler::angler.getPosition(), (int)angler::angler.getTemperature());
  // pros::lcd::print(4, "Diff state: %c | Diff Left temp: %d", differential::currState, (int)differential::diffLeft.getTemperature());
  // pros::lcd::print(5, "Macro state: %c", macro::currState);
}

void opcontrol()
{

  pros::lcd::initialize();

  while (true)
  {

    // printf("%d\n", pros::millis());
    //printf("%f\n", puncher::puncher.get_torque());

    states();

    // i'm alive!

    // All of our work has been offloaded to external tasks, so the main
    // while loop is empty.

    pros::delay(10);
  }
}
