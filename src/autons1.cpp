#include "main.h"

void redNearAuton1() {
  chassisController.setMaxVelocity(50);
  chassisController.moveDistance(-100);
  chassisController.waitUntilSettled();
  puncher.moveAbsolute(800, 100);
  pros::delay(1400);
  chassisController.setMaxVelocity(200);
  chassisController.moveDistance(300);
  chassisController.waitUntilSettled();
  chassisController.turnAngle(90_deg);
  chassisController.setMaxVelocity(200);
  chassisController.moveDistanceAsync(1100);
  diffLeft.moveVelocity(-200);
  diffRight.moveVelocity(200);
  chassisController.waitUntilSettled();
  chassisController.moveDistance(-1600);
  chassisController.setMaxVelocity(50);
  chassisController.moveDistance(125);
  chassisController.setMaxVelocity(200);
  chassisController.turnAngle(-80_deg);
  angleChanger.moveAbsolute(350, 200);
  pros::delay(300);
  diffLeft.moveVelocity(0);
  diffRight.moveVelocity(0);
  puncher.moveAbsolute(1400, 100);
  pros::delay(1000);
  chassisController.moveDistance(-800);
  /*chassisController.setMaxVelocity(100;
  chassisController.moveDistance(600);
  diffLeft.moveVelocity(0);
  diffRight.moveVelocity(0);
  pros::delay(300);
  puncher.moveAbsolute(1400,100);
  pros::delay(1000);
  chassisController.setMaxVelocity(200);
  chassisController.moveDistance(-1400);
  */
  chassisController.turnAngle(80_deg);
  chassisController.moveDistance(1150);
}

void redNearAuton2() {}

void redFarAuton1() {
  /*  angleChanger.moveAbsolute(115,200);
    puncher.moveAbsolute(800,100);
    pros::delay(200);
    chassisController.turnAngle(45_deg);
  */
  chassisController.moveDistanceAsync(1175);
  diffLeft.moveVelocity(-200);
  diffRight.moveVelocity(200);
  chassisController.waitUntilSettled();
  pros::delay(200);
  diffLeft.moveVelocity(0);
  diffRight.moveVelocity(0);
  chassisController.turnAngle(-90_deg);
  chassisController.moveDistance(900);
}

void redFarAuton2() {

  chassisController.moveDistanceAsync(1175);
  diffLeft.moveVoltage(-200);
  diffRight.moveVoltage(200);
  chassisController.waitUntilSettled();
  pros::delay(200);
  diffLeft.moveVoltage(0);
  diffRight.moveVoltage(0);
  chassisController.turnAngle(45_deg);
  chassisController.moveDistanceAsync(500);
  diffLeft.moveVelocity(175);
  diffRight.moveVelocity(-175);
  chassisController.waitUntilSettled();
  chassisController.moveDistance(-500);
  chassisController.turnAngle(-120_deg);
  chassisController.moveDistance(900);
}

void ProgSkills() {}
