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

  //  executeRedNear1(); // column  NO PARK
  // executeRedFar1(); // middle flag with two caps with park
  // executeBlueNear1(); // column  NO PARK
  // executeBlueFar1(); // middle flag with two caps with
  // park

  // executeProgSkills(); // column with two caps and center park

  switch (autonRoutine) {
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
}
