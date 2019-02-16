#include "main.h"
using namespace okapi;
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonStates() // Prints helpful robot stats during auton period
{
}

void autonomous()
{
  pros::Task odometryPrint(odometry::printPosition, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Position Print --> Screen");

  drive::currState = drive::driveStates::yield;
  differential::currState = differential::differentialStates::yield;
  puncher::currState = puncher::puncherStates::yield;
  angler::currState = angler::anglerStates::yield;
  // Overrides states to yield during autonomous period

  // autonStates();

  switch (autonRoutine) // Executes auton routine based on auton selector
  {
  case notSelected:
    break;
  case progSkills:
    executeProgSkills();
    break;

  case redNear1:
    executeRedNear1();
    break;

  case redNear2:
    executeRedNear2();
    break;

  case redFar1:
    executeRedFar1();
    break;

  case redFar2:
    executeRedFar2();
    break;

  case blueNear1:
    executeBlueNear1();
    break;

  case blueNear2:
    executeBlueNear2();
    break;

  case blueFar1:
    executeBlueFar1();
    break;

  case blueFar2:
    executeBlueFar2();
    break;
  }

  // executeRedNear1();
  // executeProgSkills();
  // executeRedFar1();
  // executeRedFar2();

  // turnAngleVel(3600_deg, 100);

  // drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::brake);

  // odometryPrint.suspend();

  lv_obj_clean(lv_scr_act());
}
