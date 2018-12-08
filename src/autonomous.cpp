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
  //executeRedNear1(); //column  NO PARK
  //executeRedNear2(); //two flags with park
  executeRedFar1();  // middle flag with two caps with park
  //executeRedFar2(); // middle flag with two caps NO PARK
  //executeBlueNear1(); //column  NO PARK
  //executeBlueNear2(); //two flags with park
  //executeBlueFar1();  // middle flag with two caps with park
  //executeBlueFar2(); // middle flag with two caps NO PARK

  //executeProgSkills(); // column with two caps and center park
}
