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
void autonomous() {
 //executeRedNear1(); // column , 1 middle flag, 2 caps
 //executeRedNear2();// column, park, 1 cap
   //executeRedFar1(); // two flags, two caps, park
  // executeBlueNear1(); // column, 1 middle flag, 2 caps
  //executeBlueNear2(); //column, park, 1 cap
  // executeBlueFar1(); // two flags, two caps, park
   executeProgSkills(); // column with two caps and center park (possible middle flag)
}
