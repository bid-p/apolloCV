#include "main.h"

void initProgSkills() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "A");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{55_in, 0_in, 0_deg}}, "A1");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{22_in, 0_in, 0_deg}}, "B");
  profileController.generatePath(
          {Point{0_in, 0_in, 0_deg}, Point{30_in, 0_in, 0_deg}}, "B2");
}

Timer outtakeTimer;

void executeProgSkills() {
  runIntake(200);
  profileController.setTarget("A", false);
  while(!hasBall());
  outtakeTimer.getDt();
  while(outtakeTimer.readDt() <= 20_ms) {
      diffLeft.moveVoltage(12000);
      diffRight.moveVoltage(-12000);
  }
  profileController.waitUntilSettled();
  runIntake(0);

  profileController.setTarget("A", true);
  profileController.waitUntilSettled();

  turnAngleVel(-90_deg, 100);

  runNearMacro();

  pros::delay(700);

 turnAngleVel(-9_deg, 150);// turn to face low flag
 runIntake(200);

  profileController.setTarget("A1", false);
  profileController.waitUntilSettled();
  profileController.setTarget("B", true);
  profileController.waitUntilSettled();

  turnAngleVel(100_deg, 100);

  runIntake(-150);
    chassisController.setMaxVelocity(100); // slow drive

    profileController.setTarget("B2", false); // Run into cap 2 and flip
    profileController.waitUntilSettled();



    turnAngleVel(-33_deg, 100);

    puncher.moveVoltage(12000);
    pros::delay(800);
    puncher.moveVoltage(0);

    profileController.removePath("A");
    profileController.removePath("B");
    profileController.removePath("A1");
    profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{20_in, 0_in, 0_deg}}, "C");
    profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{60_in, 0_in, 0_deg}}, "D");

        pros::delay(1000);

      turnAngleVel(33_deg, 100);

      profileController.setTarget("C", true); // Reverse from cap 2
      profileController.waitUntilSettled();


      runIntake(0); // stop intake

      chassisController.setMaxVelocity(200); // return drive to full speed
      turnAngleVel(-91_deg, 100); // turn to be parallel with field perimeter

      profileController.setTarget("D", true); // Reverse to align with platforms
      profileController.waitUntilSettled();

      turnAngleVel(90_deg, 100); // face parking platform

      runIntake(200); // start intake to aid in climbing

      chassisController.moveDistance(70_in); // climb platform

      runIntake(0); // stop intake

}



void initRedNear1() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "A");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{60_in, 0_in, 0_deg}}, "A1");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{27_in, 0_in, 0_deg}}, "B");
  profileController.generatePath(
          {Point{0_in, 0_in, 0_deg}, Point{30_in, 0_in, 0_deg}}, "B2");
}



void executeRedNear1() {
  runIntake(200);
  profileController.setTarget("A", false);
  while(!hasBall());
  outtakeTimer.getDt();
  while(outtakeTimer.readDt() <= 20_ms) {
      diffLeft.moveVoltage(12000);
      diffRight.moveVoltage(-12000);
  }
  profileController.waitUntilSettled();
  runIntake(0);

  profileController.setTarget("A", true);
  profileController.waitUntilSettled();

  turnAngleVel(-90_deg, 100);

  runNearMacro();

  pros::delay(500);

 turnAngleVel(-9_deg, 150);// turn to face low flag
 runIntake(200);

  profileController.setTarget("A1", false);
  profileController.waitUntilSettled();
  profileController.setTarget("B", true);
  profileController.waitUntilSettled();

  turnAngleVel(100_deg, 100);

  runIntake(-150);
    chassisController.setMaxVelocity(100); // slow drive

    profileController.setTarget("B2", false); // Run into cap 2 and flip
    profileController.waitUntilSettled();

    chassisController.setMaxVelocity(200); // return drive to full speed

chassisController.setMaxVelocity(200);
    turnAngleVel(-33_deg, 100);

    puncher.moveVoltage(12000);
    pros::delay(800);
}

//
//
//
//
//
//
//
void initRedNear2(){
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "A");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{60_in, 0_in, 0_deg}}, "A1");

}


void executeRedNear2(){
  runIntake(200);
  profileController.setTarget("A", false);
  while(!hasBall());
  outtakeTimer.getDt();
  while(outtakeTimer.readDt() <= 20_ms) {
      diffLeft.moveVoltage(12000);
      diffRight.moveVoltage(-12000);
  }
  profileController.waitUntilSettled();
  runIntake(0);

  profileController.setTarget("A", true);
  profileController.waitUntilSettled();

  turnAngleVel(-90_deg, 100);

  runNearMacro();

  pros::delay(500);

 turnAngleVel(-9_deg, 150);// turn to face low flag

 profileController.setTarget("A1", false);
 profileController.waitUntilSettled();


profileController.removePath("A1");


 profileController.generatePath(
     {Point{0_in, 0_in, 0_deg}, Point{105_in, 0_in, 0_deg}}, "B");

 profileController.setTarget("B", true);
 profileController.waitUntilSettled();

 turnAngleVel(95_deg, 150);
 runIntake(200);
 chassisController.moveDistance(36_in);
}

void initRedFar1() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "A");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{10_in, 0_in, 0_deg}}, "A1");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{42_in, 0_in, 0_deg}}, "B");

}

void executeRedFar1() {
  runIntake(200);
  profileController.setTarget("A", false);
  while(!hasBall());
  outtakeTimer.getDt();
  while(outtakeTimer.readDt() <= 20_ms) {
      diffLeft.moveVoltage(12000);
      diffRight.moveVoltage(-12000);
  }
  profileController.waitUntilSettled();
  runIntake(0);

    turnAngleVel(-75_deg, 150);

    runFarMacro();

    turnAngleVel(-180_deg, 150);
    chassisController.setMaxVelocity(100); // slow drive
    runIntake(-150);

    profileController.setTarget("B", false); // Run into cap 2 and flip
    profileController.waitUntilSettled();

    profileController.setTarget("B", true); // Reverse from cap 2
    profileController.waitUntilSettled();

    chassisController.setMaxVelocity(200); // return drive to full speed

    runIntake(0); // stop intake

    turnAngleVel(90_deg, 100); // turn to be parallel with field perimeter
    runIntake(200);
    profileController.setTarget("A1", false); // Reverse to align with platforms
    profileController.waitUntilSettled();

    turnAngleVel(90_deg, 100); // face parking platform

    chassisController.moveDistance(30_in); // climb platform

    runIntake(0); // stop intake

}



void initBlueNear1() {
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "A");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{60_in, 0_in, 0_deg}}, "A1");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{25_in, 0_in, 0_deg}}, "B");
  profileController.generatePath(
          {Point{0_in, 0_in, 0_deg}, Point{30_in, 0_in, 0_deg}}, "B2");

}

void executeBlueNear1() {
  runIntake(200);
  profileController.setTarget("A", false);
  while(!hasBall());
  outtakeTimer.getDt();
  while(outtakeTimer.readDt() <= 20_ms) {
      diffLeft.moveVoltage(12000);
      diffRight.moveVoltage(-12000);
  }
  profileController.waitUntilSettled();
  runIntake(0);

  profileController.setTarget("A", true);
  profileController.waitUntilSettled();

  turnAngleVel(92_deg, 100);

  runNearMacro();

  pros::delay(500);

 turnAngleVel(7_deg, 150);// turn to face low flag
 runIntake(200);

  profileController.setTarget("A1", false);
  profileController.waitUntilSettled();
  profileController.setTarget("B", true);
  profileController.waitUntilSettled();

  turnAngleVel(-100_deg, 100);

  runIntake(-150);
    chassisController.setMaxVelocity(100); // slow drive

    profileController.setTarget("B2", false); // Run into cap 2 and flip
    profileController.waitUntilSettled();

    chassisController.setMaxVelocity(200); // return drive to full speed

chassisController.setMaxVelocity(200);
    turnAngleVel(33_deg, 100);

    puncher.moveVoltage(12000);
    pros::delay(800);

}

//
//
//
//
//
//
//
void initBlueNear2(){
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "A");
  profileController.generatePath(
      {Point{0_in, 0_in, 0_deg}, Point{60_in, 0_in, 0_deg}}, "A1");

}

void executeBlueNear2(){
  runIntake(200);
  profileController.setTarget("A", false);
  while(!hasBall());
  outtakeTimer.getDt();
  while(outtakeTimer.readDt() <= 20_ms) {
      diffLeft.moveVoltage(12000);
      diffRight.moveVoltage(-12000);
  }
  profileController.waitUntilSettled();
  runIntake(0);

  profileController.setTarget("A", true);
  profileController.waitUntilSettled();

  turnAngleVel(90_deg, 100);

  runNearMacro();

  pros::delay(500);

 turnAngleVel(9_deg, 150);// turn to face low flag

 profileController.setTarget("A1", false);
 profileController.waitUntilSettled();


profileController.removePath("A1");


 profileController.generatePath(
     {Point{0_in, 0_in, 0_deg}, Point{105_in, 0_in, 0_deg}}, "B");

 profileController.setTarget("B", true);
 profileController.waitUntilSettled();

 turnAngleVel(-95_deg, 150);
 runIntake(200);
 chassisController.moveDistance(36_in);
}

void initBlueFar1() {

}

void executeBlueFar1() {


}
