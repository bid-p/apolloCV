#include "main.h"

autonRoutines autonRoutine = notSelected;

void initProgSkills() {
  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "A");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{16_in, 0_in, 0_deg}}, "B1");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "B2");
}

void executeProgSkills() {
  drive::profileController.setTarget("A", true); // move back slightly to hit
                                                 // flag without angling
  drive::profileController.waitUntilSettled();

  puncher::puncher.moveVoltage(12000); // shoot
  pros::delay(600);
  puncher::puncher.moveVoltage(0);

  drive::profileController.setTarget("B1"); // move slightly forward to perp
                                            // align with first cap
  drive::profileController.waitUntilSettled();

  turnAngleVel(90_deg, 100); // face first cap

  runIntake(200); // start intaking

  drive::profileController.setTarget("B2"); // run into first cap
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("B2", true); // reverse from first cap
  drive::profileController.waitUntilSettled();

  pros::delay(300);

  runIntake(0); // turn off intake

  turnAngleVel(-86_deg, 100); // turn left to face column of flags
  drive::chassisController.setMaxVelocity(50);
  drive::chassisController.moveDistance(-3_in); // move back to hit mid
                                                // flag from close up

  angler::angleController.setTarget(350); // change angle to hit mid flag
  angler::angleController.waitUntilSettled();

  runIntake(-100); // DOUBLECHECKING FOR POTENTIALLY JAMMED BALL
  pros::delay(200);
  runIntake(200);
  pros::delay(700);
  runIntake(0);

  puncher::puncher.moveVoltage(12000); // shoot
  pros::delay(800);
  puncher::puncher.moveVoltage(0);

  drive::chassisController.moveDistance(3_in); // move forward slightly
  drive::chassisController.setMaxVelocity(200);
  turnAngleVel(-9_deg, 100); // turn to face low flag

  drive::profileController.removePath("A"); // free up system memory
                                            // by deleting old paths
  drive::profileController.removePath("B1");
  drive::profileController.removePath("B2");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{52_in, 0_in, 0_deg}}, "C1");

  drive::profileController.setTarget("C1"); // Straight into low flag
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("C1", true); // Reverse from low flag
  drive::profileController.waitUntilSettled();

  turnAngleVel(40_deg, 100); // turn to face second cap

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{47_in, 0_in, 0_deg}}, "D1");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "E");

  runIntake(-200); // reverse intake

  drive::chassisController.setMaxVelocity(150); // slow drive

  drive::profileController.setTarget("D1"); // Run into cap 2 and flip
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("D1", true); // Reverse from cap 2
  drive::profileController.waitUntilSettled();

  drive::chassisController.setMaxVelocity(200); // return drive to full speed

  runIntake(0); // stop intake

  turnAngleVel(-33_deg, 100); // turn to be parallel with field perimeter

  drive::profileController.setTarget("E",
                                     true); // Reverse to align with platforms
  drive::profileController.waitUntilSettled();

  turnAngleVel(90_deg, 100); // face parking platform

  runIntake(200); // start intake to aid in climbing

  drive::chassisController.moveDistance(75_in); // climb platform

  runIntake(0); // stop intake
}

//
//
//
//
//
//
//
//

void initRedNear1() {
  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "A");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{16_in, 0_in, 0_deg}}, "B1");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "B2");
}

void executeRedNear1() {
  drive::profileController.setTarget("A", true); // move back slightly to hit
                                                 // flag without angling
  drive::profileController.waitUntilSettled();

  puncher::puncher.moveVoltage(12000); // shoot
  pros::delay(600);
  puncher::puncher.moveVoltage(0);

  drive::profileController.setTarget("B1"); // move slightly forward to perp
                                            // align with first cap
  drive::profileController.waitUntilSettled();

  turnAngleVel(90_deg, 100); // face first cap

  runIntake(200); // start intaking

  drive::profileController.setTarget("B2"); // run into first cap
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("B2", true); // reverse from first cap
  drive::profileController.waitUntilSettled();

  pros::delay(300);

  runIntake(0); // turn off intake

  turnAngleVel(-86_deg, 100); // turn left to face column of flags
  drive::chassisController.setMaxVelocity(50);
  drive::chassisController.moveDistance(-3_in); // move back to hit mid
                                                // flag from close up

  angler::angleController.setTarget(350); // change angle to hit mid flag
  angler::angleController.waitUntilSettled();

  runIntake(-100); // DOUBLECHECKING FOR POTENTIALLY JAMMED BALL
  pros::delay(200);
  runIntake(200);
  pros::delay(700);
  runIntake(0);

  puncher::puncher.moveVoltage(12000); // shoot
  pros::delay(800);
  puncher::puncher.moveVoltage(0);

  drive::chassisController.moveDistance(3_in); // move forward slightly
  drive::chassisController.setMaxVelocity(200);
  turnAngleVel(-9_deg, 100); // turn to face low flag

  drive::profileController.removePath("A"); // free up system memory
                                            // by deleting old paths
  drive::profileController.removePath("B1");
  drive::profileController.removePath("B2");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{50_in, 0_in, 0_deg}}, "C1");

  drive::profileController.setTarget("C1"); // Straight into low flag
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("C1", true); // Reverse from low flag
  drive::profileController.waitUntilSettled();

  turnAngleVel(40_deg, 100); // turn to face second cap

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{47_in, 0_in, 0_deg}}, "D1");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "E");

  runIntake(-200); // reverse intake

  drive::chassisController.setMaxVelocity(150); // slow drive

  drive::profileController.setTarget("D1"); // Run into cap 2 and flip
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("D1", true); // Reverse from cap 2
  drive::profileController.waitUntilSettled();

  drive::chassisController.setMaxVelocity(200); // return drive to full speed

  runIntake(0); // stop intake

  turnAngleVel(-33_deg, 100); // turn to be parallel with field perimeter

  drive::profileController.setTarget("E", true); // Reverse to align with
  drive::profileController.waitUntilSettled();

  turnAngleVel(90_deg, 100); // face parking platform

  runIntake(200); // start intake to aid in climbing

  drive::chassisController.moveDistance(75_in); // climb platform

  runIntake(0); // stop intake
}

//
//
//
//
//
//
//

void initRedNear2() {}
void executeRedNear2() {}

//

void initRedFar1() {
  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{43_in, 0_in, 0_deg}}, "A");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{15_in, 0_in, 0_deg}}, "A1");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{80_in, 0_in, 0_deg}}, "B");
  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "B1");
}

void executeRedFar1() {

  angler::angleController.setTarget(120);
  angler::angleController.waitUntilSettled();

  puncher::puncher.moveVoltage(12000); // shoot
  pros::delay(1100);
  puncher::puncher.moveVoltage(0);

  turnAngleVel(59_deg, 100);
  runIntake(200); // start intaking

  drive::profileController.setTarget("A");
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("A1", true);
  drive::profileController.waitUntilSettled();

  turnAngleVel(50_deg, 100);

  drive::chassisController.setMaxVelocity(100);

  runIntake(-200);
  drive::chassisController.setMaxVelocity(100);

  drive::profileController.setTarget("B"); // Run into cap 2
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("B1", true); // Reverse from cap 2
  drive::profileController.waitUntilSettled();

  drive::chassisController.setMaxVelocity(200);

  turnAngleVel(-140_deg, 100);

  runIntake(200);

  drive::chassisController.moveDistance(45_in);

  runIntake(0);
}

//
//
//
// HELLO GReETINGS
//
//
//

void initRedFar2() {}
void executeRedFar2() {}

void initBlueNear1() {
  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "A");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{16_in, 0_in, 0_deg}}, "B1");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "B2");
}

void executeBlueNear1() {
  drive::profileController.setTarget("A", true); // move back slightly to hit
                                                 // flag without angling
  drive::profileController.waitUntilSettled();

  puncher::puncher.moveVoltage(12000); // shoot
  pros::delay(600);
  puncher::puncher.moveVoltage(0);

  drive::profileController.setTarget("B1"); // move slightly forward to perp
                                            // align with first cap
  drive::profileController.waitUntilSettled();

  turnAngleVel(-90_deg, 100); // face first cap

  runIntake(200); // start intaking

  drive::profileController.setTarget("B2"); // run into first cap
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("B2", true); // reverse from first cap
  drive::profileController.waitUntilSettled();

  pros::delay(300);

  runIntake(0); // turn off intake

  turnAngleVel(90_deg, 100); // turn left to face column of flags
  drive::chassisController.setMaxVelocity(50);
  drive::chassisController.moveDistance(-3_in);

  angler::angleController.setTarget(350);
  angler::angleController.waitUntilSettled();

  runIntake(-100);
  pros::delay(200);
  runIntake(200);
  pros::delay(700);
  runIntake(0);

  puncher::puncher.moveVoltage(12000); // shoot
  pros::delay(800);
  puncher::puncher.moveVoltage(0);
  drive::chassisController.moveDistance(3_in);
  drive::chassisController.setMaxVelocity(200);
  turnAngleVel(8_deg, 100);

  drive::profileController.removePath("A");
  drive::profileController.removePath("B1");
  drive::profileController.removePath("B2");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{50_in, 0_in, 0_deg}}, "C1");

  drive::profileController.setTarget("C1"); // S-Curve into low flag
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("C1", true); // S-Curve into low flag
  drive::profileController.waitUntilSettled();

  turnAngleVel(-40_deg, 100);

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{47_in, 0_in, 0_deg}}, "D1");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "E");

  runIntake(-200);

  drive::chassisController.setMaxVelocity(150);

  drive::profileController.setTarget("D1"); // Run into cap 2
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("D1", true); // Reverse from cap 2
  drive::profileController.waitUntilSettled();

  drive::chassisController.setMaxVelocity(200);

  runIntake(0);

  turnAngleVel(33_deg, 100);

  drive::profileController.setTarget("E",
                                     true); // Reverse to align with platforms
  drive::profileController.waitUntilSettled();

  turnAngleVel(-90_deg, 100);

  runIntake(200);

  drive::chassisController.moveDistance(75_in);

  runIntake(0);
}

//
//
//
//
//
//
//

void initBlueNear2() {}
void executeBlueNear2() {}

void initBlueFar1() {
  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{43_in, 0_in, 0_deg}}, "A");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{15_in, 0_in, 0_deg}}, "A1");

  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{80_in, 0_in, 0_deg}}, "B");
  drive::profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "B1");
}

void executeBlueFar1() {

  angler::angleController.setTarget(120);
  angler::angleController.waitUntilSettled();

  puncher::puncher.moveVoltage(12000); // shoot
  pros::delay(1100);
  puncher::puncher.moveVoltage(0);

  turnAngleVel(-59_deg, 100);
  runIntake(200); // start intaking

  drive::profileController.setTarget("A");
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("A1", true);
  drive::profileController.waitUntilSettled();

  turnAngleVel(-50_deg, 100);

  drive::chassisController.setMaxVelocity(100);

  runIntake(-200);
  drive::chassisController.setMaxVelocity(100);

  drive::profileController.setTarget("B"); // Run into cap 2
  drive::profileController.waitUntilSettled();

  drive::profileController.setTarget("B1", true); // Reverse from cap 2
  drive::profileController.waitUntilSettled();

  drive::chassisController.setMaxVelocity(200);

  turnAngleVel(140_deg, 100);

  runIntake(200);

  drive::chassisController.moveDistance(45_in);

  runIntake(0);
}

void initBlueFar2() {}
void executeBlueFar2() {}
