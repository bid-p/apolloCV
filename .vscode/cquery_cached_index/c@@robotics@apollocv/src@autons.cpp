#include "main.h"

void initProgSkills() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{16_in, 0_in, 0_deg}}, "B1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "B2");
}

void executeProgSkills() {
  profileController.setTarget("A", true); // move back slightly to hit
                                          // flag without angling
  profileController.waitUntilSettled();

  puncher.moveVoltage(12000); // shoot
  pros::delay(600);
  puncher.moveVoltage(0);

  profileController.setTarget("B1"); // move slightly forward to perp
                                     // align with first cap
  profileController.waitUntilSettled();

  turnAngleVel(90_deg, 100); // face first cap

  runIntake(200); // start intaking

  profileController.setTarget("B2"); // run into first cap
  profileController.waitUntilSettled();

  profileController.setTarget("B2", true); // reverse from first cap
  profileController.waitUntilSettled();

  pros::delay(300);

  runIntake(0); // turn off intake

  turnAngleVel(-86_deg, 100); // turn left to face column of flags
  chassisController.setMaxVelocity(50);
  chassisController.moveDistance(-3_in); // move back to hit mid
                                         // flag from close up

  angleController.setTarget(350); // change angle to hit mid flag
  angleController.waitUntilSettled();

  runIntake(-100); // DOUBLECHECKING FOR POTENTIALLY JAMMED BALL
  pros::delay(200);
  runIntake(200);
  pros::delay(700);
  runIntake(0);

  puncher.moveVoltage(12000); // shoot
  pros::delay(800);
  puncher.moveVoltage(0);

  chassisController.moveDistance(3_in); // move forward slightly
  chassisController.setMaxVelocity(200);
  turnAngleVel(-9_deg, 100); // turn to face low flag

  profileController.removePath("A"); // free up system memory
                                     // by deleting old paths
  profileController.removePath("B1");
  profileController.removePath("B2");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{52_in, 0_in, 0_deg}}, "C1");

  profileController.setTarget("C1"); // Straight into low flag
  profileController.waitUntilSettled();

  profileController.setTarget("C1", true); // Reverse from low flag
  profileController.waitUntilSettled();

  turnAngleVel(40_deg, 100); // turn to face second cap

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{47_in, 0_in, 0_deg}}, "D1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "E");

  runIntake(-200); // reverse intake

  chassisController.setMaxVelocity(150); // slow drive

  profileController.setTarget("D1"); // Run into cap 2 and flip
  profileController.waitUntilSettled();

  profileController.setTarget("D1", true); // Reverse from cap 2
  profileController.waitUntilSettled();

  chassisController.setMaxVelocity(200); // return drive to full speed

  runIntake(0); // stop intake

  turnAngleVel(-33_deg, 100); // turn to be parallel with field perimeter

  profileController.setTarget("E", true); // Reverse to align with platforms
  profileController.waitUntilSettled();

  turnAngleVel(90_deg, 100); // face parking platform

  runIntake(200); // start intake to aid in climbing

  chassisController.moveDistance(75_in); // climb platform

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
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "B");
}

Timer outtakeTimer;

void executeRedNear1() {
  runIntake(200);
  profileController.setTarget("A", false);
  while(!hasBall());
  outtakeTimer.getDt();
  while(outtakeTimer.readDt() <= 20_ms) {
      diffLeft.moveVoltage(10000);
      diffRight.moveVoltage(-10000);
  }
  profileController.waitUntilSettled();
  runIntake(0);

  profileController.setTarget("A", true);
  profileController.waitUntilSettled();

  turnAngleVel(-90_deg, 100);

  runMacro();

  profileController.setTarget("B", false);
  profileController.waitUntilSettled();


}

//
//
//
//
//
//
//

void initRedFar1() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{43_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{15_in, 0_in, 0_deg}}, "A1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{80_in, 0_in, 0_deg}}, "B");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "B1");
}

void executeRedFar1() {

  angleController.setTarget(120);
  angleController.waitUntilSettled();

  puncher.moveVoltage(12000); // shoot
  pros::delay(1100);
  puncher.moveVoltage(0);

  turnAngleVel(59_deg, 100);
  runIntake(200); // start intaking

  profileController.setTarget("A");
  profileController.waitUntilSettled();

  profileController.setTarget("A1", true);
  profileController.waitUntilSettled();

  turnAngleVel(50_deg, 100);

  chassisController.setMaxVelocity(100);

  runIntake(-200);
  chassisController.setMaxVelocity(100);

  profileController.setTarget("B"); // Run into cap 2
  profileController.waitUntilSettled();

  profileController.setTarget("B1", true); // Reverse from cap 2
  profileController.waitUntilSettled();

  chassisController.setMaxVelocity(200);

  turnAngleVel(-140_deg, 100);

  runIntake(200);

  chassisController.moveDistance(45_in);

  runIntake(0);
}

//
//
//
// HELLO GReETINGS
//
//
//

void initBlueNear1() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{16_in, 0_in, 0_deg}}, "B1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "B2");
}

void executeBlueNear1() {
  profileController.setTarget("A", true); // move back slightly to hit
                                          // flag without angling
  profileController.waitUntilSettled();

  puncher.moveVoltage(12000); // shoot
  pros::delay(600);
  puncher.moveVoltage(0);

  profileController.setTarget("B1"); // move slightly forward to perp
                                     // align with first cap
  profileController.waitUntilSettled();

  turnAngleVel(-90_deg, 100); // face first cap

  runIntake(200); // start intaking

  profileController.setTarget("B2"); // run into first cap
  profileController.waitUntilSettled();

  profileController.setTarget("B2", true); // reverse from first cap
  profileController.waitUntilSettled();

  pros::delay(300);

  runIntake(0); // turn off intake

  turnAngleVel(90_deg, 100); // turn left to face column of flags
  chassisController.setMaxVelocity(50);
  chassisController.moveDistance(-3_in);

  angleController.setTarget(350);
  angleController.waitUntilSettled();

  runIntake(-100);
  pros::delay(200);
  runIntake(200);
  pros::delay(700);
  runIntake(0);

  puncher.moveVoltage(12000); // shoot
  pros::delay(800);
  puncher.moveVoltage(0);
  chassisController.moveDistance(3_in);
  chassisController.setMaxVelocity(200);
  turnAngleVel(8_deg, 100);

  profileController.removePath("A");
  profileController.removePath("B1");
  profileController.removePath("B2");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{50_in, 0_in, 0_deg}}, "C1");

  profileController.setTarget("C1"); // S-Curve into low flag
  profileController.waitUntilSettled();

  profileController.setTarget("C1", true); // S-Curve into low flag
  profileController.waitUntilSettled();

  turnAngleVel(-40_deg, 100);

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{47_in, 0_in, 0_deg}}, "D1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "E");

  runIntake(-200);

  chassisController.setMaxVelocity(150);

  profileController.setTarget("D1"); // Run into cap 2
  profileController.waitUntilSettled();

  profileController.setTarget("D1", true); // Reverse from cap 2
  profileController.waitUntilSettled();

  chassisController.setMaxVelocity(200);

  runIntake(0);

  turnAngleVel(33_deg, 100);

  profileController.setTarget("E", true); // Reverse to align with platforms
  profileController.waitUntilSettled();

  turnAngleVel(-90_deg, 100);

  runIntake(200);

  chassisController.moveDistance(75_in);

  runIntake(0);
}

//
//
//
//
//
//
//

void initBlueFar1() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{43_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{15_in, 0_in, 0_deg}}, "A1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{80_in, 0_in, 0_deg}}, "B");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "B1");
}

void executeBlueFar1() {

  angleController.setTarget(120);
  angleController.waitUntilSettled();

  puncher.moveVoltage(12000); // shoot
  pros::delay(1100);
  puncher.moveVoltage(0);

  turnAngleVel(-59_deg, 100);
  runIntake(200); // start intaking

  profileController.setTarget("A");
  profileController.waitUntilSettled();

  profileController.setTarget("A1", true);
  profileController.waitUntilSettled();

  turnAngleVel(-50_deg, 100);

  chassisController.setMaxVelocity(100);

  runIntake(-200);
  chassisController.setMaxVelocity(100);

  profileController.setTarget("B"); // Run into cap 2
  profileController.waitUntilSettled();

  profileController.setTarget("B1", true); // Reverse from cap 2
  profileController.waitUntilSettled();

  chassisController.setMaxVelocity(200);

  turnAngleVel(140_deg, 100);

  runIntake(200);

  chassisController.moveDistance(45_in);

  runIntake(0);
}
