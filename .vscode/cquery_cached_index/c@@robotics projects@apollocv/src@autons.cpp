#include "main.h"

void initProgSkills() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{16_in, 0_in, 0_deg}}, "B1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{32_in, 0_in, 0_deg}}, "B2");

  // profileController.generatePath(
  //     {Point{0_in, 0_in, 0_deg}, Point{43_in, -3_in, 0_deg}}, "C1");//s curve
  //     stuff

  // profileController.generatePath(
  //     {Point{0_in, 0_in, 0_deg}, Point{42_in, 0_in, 0_deg}}, "C1");
  // UNCOMMENT

  // profileController.generatePath(
  //     {Point{0_in, 0_in, 0_deg}, Point{41_in, 0_in, 0_deg}}, "C2");
  //
  // profileController.generatePath(
  //     {Point{0_in, 0_in, 0_deg}, Point{20_in, 0_in, 0_deg}}, "D1");
  //
  // profileController.generatePath(
  //     {Point{0_in, 0_in, 0_deg}, Point{15_in, 0_in, 0_deg}}, "D2");
  //
  // profileController.generatePath(
  //     {Point{0_in, 0_in, 0_deg}, Point{29_in, 0_in, 0_deg}}, "E");
}

void executeProgSkills() {
  profileController.setTarget("A", true); // move back slightly to hit
                                          // flag without angling
  profileController.waitUntilSettled();

  puncher.moveVoltage(12000); // shoot
  pros::delay(1100);
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

  turnAngleVel(-90_deg, 100); // turn left to face column of flags

  angleController.setTarget(350);
  angleController.waitUntilSettled();

  runIntake(-100);
  pros::delay(100);
  runIntake(200);
  pros::delay(700);
  runIntake(0);

  puncher.moveVoltage(12000); // shoot
  pros::delay(1400);
  puncher.moveVoltage(0);

  turnAngleVel(-3_deg, 100);

  profileController.removePath("A");
  profileController.removePath("B1");
  profileController.removePath("B2");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "C1");

  profileController.setTarget("C1"); // S-Curve into low flag
  profileController.waitUntilSettled();

  profileController.setTarget("C1", true); // S-Curve into low flag
  profileController.waitUntilSettled();

  turnAngleVel(35_deg, 100);

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{24_in, 0_in, 0_deg}}, "D1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{24_in, 0_in, 0_deg}}, "E");

  runIntake(-150);

  profileController.setTarget("D1"); // Run into cap 2
  profileController.waitUntilSettled();

  profileController.setTarget("D1", true); // Reverse from cap 2
  profileController.waitUntilSettled();

  runIntake(0);

  turnAngleVel(-28_deg, 100);

  profileController.setTarget("E", true); // Reverse to align with platforms
  profileController.waitUntilSettled();

  turnAngleVel(90_deg, 100);

  chassisController.moveDistance(70_in);
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
      {Point{0_in, 0_in, 0_deg}, Point{2_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{7_in, 0_in, 0_deg}}, "B1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{33_in, 0_in, 0_deg}}, "B2");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{43_in, -3_in, 0_deg}}, "C1");

  // profileController.generatePath(
  //     {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "C2");
  //
  // profileController.generatePath(
  //     {Point{0_in, 0_in, 0_deg}, Point{50_in, 0_in, 0_deg}}, "D1");
  //
  // profileController.generatePath(
  //     {Point{0_in, 0_in, 0_deg}, Point{10_in, 0_in, 0_deg}}, "D2");
  //
  // profileController.generatePath(
  //     {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "E");
}

void executeRedNear1() {
  profileController.setTarget("A"); // move back slightly to hit
                                    // flag without angling
  profileController.waitUntilSettled();

  puncher.moveAbsolute(800, 100); // shoot
  pros::delay(1400);
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

  runIntake(0); // turn off intake

  turnAngleVel(-90_deg, 100); // turn left to face column of flags

  angleController.setTarget(0);
  angleController.waitUntilSettled();

  puncher.moveAbsolute(800, 100); // shoot
  pros::delay(1400);
  puncher.moveVoltage(0);

  profileController.setTarget("C1"); // S-Curve into low flag
  profileController.waitUntilSettled();

  //

  profileController.removePath("A");
  profileController.removePath("B1");
  profileController.removePath("B2");
  profileController.removePath("C1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "C2");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{50_in, 0_in, 0_deg}}, "D1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{10_in, 0_in, 0_deg}}, "D2");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "E");

  profileController.setTarget("C2", true); // reverse from flag
  profileController.waitUntilSettled();

  turnAngleVel(75_deg, 100);

  profileController.setTarget("D1"); // straight into second low flag
  profileController.waitUntilSettled();

  profileController.setTarget("C2", true); // reverse from second low flag
  profileController.waitUntilSettled();

  turnAngleVel(150_deg, 200);

  runIntake(-150); // reverse intake

  profileController.setTarget("E");
}

//
//
//
//
//
//
//
//

void initRedNear2() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{2_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{7_in, 0_in, 0_deg}}, "B1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{33_in, 0_in, 0_deg}}, "B2");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{43_in, -3_in, 0_deg}}, "C1");
  //
  // profileController.generatePath(
  //     {Point{0_in, 0_in, 0_deg}, Point{67_in, 0_in, 0_deg}}, "C2");
}

void executeRedNear2() {
  profileController.setTarget("A"); // move back slightly to hit
                                    // flag without angling
  profileController.waitUntilSettled();

  puncher.moveAbsolute(800, 100); // shoot
  pros::delay(1400);
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

  runIntake(0); // turn off intake

  turnAngleVel(-90_deg, 100); // turn left to face column of flags

  angleController.setTarget(0);
  angleController.waitUntilSettled();

  puncher.moveAbsolute(800, 100); // shoot
  pros::delay(1400);
  puncher.moveVoltage(0);

  profileController.setTarget("C1"); // S-Curve into low flag
  profileController.waitUntilSettled();

  //

  profileController.removePath("A");
  profileController.removePath("B1");
  profileController.removePath("B2");
  profileController.removePath("C1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{67_in, 0_in, 0_deg}}, "C2");

  profileController.setTarget("C2", true); // reverse from low flag
  profileController.waitUntilSettled();

  turnAngleVel(90_deg, 100);

  chassisController.moveDistance(40_in);
  chassisController.waitUntilSettled();
}

void initRedFar1() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{24_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{20_in, 0_in, 0_deg}}, "B");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{3_in, 0_in, 0_deg}}, "C");
}

void executeRedFar1() {
  profileController.setTarget("A");
  profileController.waitUntilSettled();

  turnAngleVel(-50_deg, 100); // turn left to face opposing row of flags

  angleController.setTarget(0);
  angleController.waitUntilSettled();

  puncher.moveAbsolute(800, 100); // shoot
  pros::delay(1400);
  puncher.moveVoltage(0);

  turnAngleVel(50_deg, 100);

  profileController.setTarget("B");
  profileController.waitUntilSettled();

  runIntake(200);

  profileController.setTarget("C", true);
  profileController.waitUntilSettled();

  runIntake(0);

  turnAngleVel(-90_deg, 100);

  chassisController.moveDistance(30_in);
  chassisController.waitUntilSettled();
}
