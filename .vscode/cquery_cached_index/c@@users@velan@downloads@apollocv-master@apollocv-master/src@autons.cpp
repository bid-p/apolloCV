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

  turnAngleVel(-86_deg, 100); // turn left to face column of flags
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
  pros::delay(1400);
  puncher.moveVoltage(0);
chassisController.moveDistance(3_in);
chassisController.setMaxVelocity(200);
  turnAngleVel(-9_deg, 100);

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
      {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "D1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "E");

  runIntake(-200);
  chassisController.setMaxVelocity(100);

  profileController.setTarget("D1"); // Run into cap 2
  profileController.waitUntilSettled();

  profileController.setTarget("D1", true); // Reverse from cap 2
  profileController.waitUntilSettled();

  chassisController.setMaxVelocity(200);

  runIntake(0);

  turnAngleVel(-28_deg, 100);

  profileController.setTarget("E", true); // Reverse to align with platforms
  profileController.waitUntilSettled();

  turnAngleVel(88_deg, 100);

  chassisController.moveDistance(75_in);
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
      {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{16_in, 0_in, 0_deg}}, "B1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "B2");



}

void executeRedNear1() {
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

  turnAngleVel(-86_deg, 100); // turn left to face column of flags
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
  pros::delay(1400);
  puncher.moveVoltage(0);
chassisController.moveDistance(3_in);
chassisController.setMaxVelocity(200);
  turnAngleVel(-9_deg, 100);

  profileController.removePath("A");
  profileController.removePath("B1");
  profileController.removePath("B2");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "C1");

  profileController.setTarget("C1"); // S-Curve into low flag
  profileController.waitUntilSettled();
//
//
//
//
//
//
//
//
}
void initRedNear2() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{16_in, 0_in, 0_deg}}, "B1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "B2");


}

void executeRedNear2() {
  profileController.setTarget("A", true); // move back slightly to hit
                                          // flag without angling
  profileController.waitUntilSettled();

  puncher.moveVoltage(12000); // shoot
  pros::delay(1000);
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

  turnAngleVel(-86_deg, 100); // turn left to face column of flags
chassisController.setMaxVelocity(50);
chassisController.moveDistance(-3_in);

  angleController.setTarget(350);
  angleController.waitUntilSettled();
  puncher.moveVoltage(12000); // shoot
  pros::delay(1300);
  puncher.moveVoltage(0);
chassisController.setMaxVelocity(200);
profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{22_in, 0_in, 0_deg}}, "E");

      profileController.setTarget("E", true); // Reverse to align with platforms
      profileController.waitUntilSettled();

      turnAngleVel(92_deg, 150);

      chassisController.moveDistance(40_in);

}

void initRedFar1() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{15_in, 0_in, 0_deg}}, "A1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{57_in, 0_in, 0_deg}}, "B");
      profileController.generatePath(
          {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "B1");


}

void executeRedFar1() {
  puncher.moveVoltage(12000); // shoot
  pros::delay(1100);
  puncher.moveVoltage(0);
  turnAngleVel(55_deg, 100);
  runIntake(200); // start intaking

  profileController.setTarget("A"); // Reverse to align with platforms
  profileController.waitUntilSettled();

  profileController.setTarget("A1", true);
  profileController.waitUntilSettled();

  turnAngleVel(55_deg, 100);

  chassisController.setMaxVelocity(100);

  runIntake(-200);
  chassisController.setMaxVelocity(100);

  profileController.setTarget("B"); // Run into cap 2
  profileController.waitUntilSettled();

  profileController.setTarget("B", true); // Reverse from cap 2
  profileController.waitUntilSettled();

  chassisController.setMaxVelocity(200);

  turnAngleVel(-45_deg, 100);
  profileController.setTarget("B1");
  profileController.waitUntilSettled();

  turnAngleVel(-90_deg, 100);
  runIntake(200);
  chassisController.moveDistance(33_in);

  runIntake(0);

}

void initRedFar2() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "A");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{15_in, 0_in, 0_deg}}, "A1");

  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{57_in, 0_in, 0_deg}}, "B");
      profileController.generatePath(
          {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "B1");


}
void executeRedFar2(){
puncher.moveVoltage(12000); // shoot
pros::delay(1100);
puncher.moveVoltage(0);
turnAngleVel(55_deg, 100);
runIntake(200); // start intaking

profileController.setTarget("A"); // Reverse to align with platforms
profileController.waitUntilSettled();

profileController.setTarget("A1", true);
profileController.waitUntilSettled();

turnAngleVel(55_deg, 100);

chassisController.setMaxVelocity(100);

runIntake(-200);
chassisController.setMaxVelocity(100);

profileController.setTarget("B"); // Run into cap 2
profileController.waitUntilSettled();

profileController.setTarget("B", true); // Reverse from cap 2
profileController.waitUntilSettled();

chassisController.setMaxVelocity(200);
}
