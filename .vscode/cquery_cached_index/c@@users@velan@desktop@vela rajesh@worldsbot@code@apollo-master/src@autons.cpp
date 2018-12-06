#include "main.h"

  void redNearAuton1(){
    drive.setMaxVelocity(50);
    drive.moveDistance(-100);
    drive.waitUntilSettled();
    puncher.moveAbsolute(800,100);
    pros::delay(1400);
    drive.setMaxVelocity(200);
    drive.moveDistance(300);
    drive.waitUntilSettled();
    drive.turnAngle(90_deg);
    drive.setMaxVelocity(200);
    drive.moveDistanceAsync(1100);
    diffLeft.moveVelocity(-200);
    diffRight.moveVelocity(200);
    drive.waitUntilSettled();
    drive.moveDistance(-1600);
    drive.setMaxVelocity(50);
    drive.moveDistance(125);
    drive.setMaxVelocity(200);
    drive.turnAngle(-80_deg);
    angleChanger.moveAbsolute(350 ,200);
    pros::delay(300);
    diffLeft.moveVelocity(0);
    diffRight.moveVelocity(0);
    puncher.moveAbsolute(1400,100);
    pros::delay(1000);
    drive.moveDistance(-800);
    /*drive.setMaxVelocity(100;
    drive.moveDistance(600);
    diffLeft.moveVelocity(0);
    diffRight.moveVelocity(0);
    pros::delay(300);
    puncher.moveAbsolute(1400,100);
    pros::delay(1000);
    drive.setMaxVelocity(200);
    drive.moveDistance(-1400);
    */
    drive.turnAngle(80_deg);
    drive.moveDistance(1150);
  }

  void redNearAuton2(){
    puncher.moveAbsolute(800,100);
    drive.turnAngle(90_deg);
    drive.moveDistanceAsync(1000);
    diffLeft.moveVelocity(-200);
    diffRight.moveVelocity(200);
    drive.waitUntilSettled();
    pros::delay(200);
    drive.moveDistance(-1250);
    pros::delay(200);
    drive.moveDistanceAsync(200);
    drive.turnAngle(-90_deg);
    drive.moveDistance(200);
    drive.waitUntilSettled();
    puncher.moveAbsolute(800,100);
    pros::delay(300);
    drive.turnAngle(-30_deg);
    drive.moveDistance(400);
    drive.moveDistance(-600);
    drive.turnAngle(90_deg);
    pros::delay(200);
    drive.moveDistanceAsync(700);
    diffLeft.moveVoltage(9000);
    diffRight.moveVoltage(-9000);
    drive.waitUntilSettled();
    drive.turnAngle(-30_deg);
    drive.moveDistance(500);
    drive.waitUntilSettled();
  }

    void redFarAuton1(){
  /*  angleChanger.moveAbsolute(115,200);
    puncher.moveAbsolute(800,100);
    pros::delay(200);
    drive.turnAngle(45_deg);
  */  drive.moveDistanceAsync(1175);
    diffLeft.moveVelocity(-200);
    diffRight.moveVelocity(200);
    drive.waitUntilSettled();
    pros::delay(200);
    diffLeft.moveVelocity(0);
    diffRight.moveVelocity(0);
    drive.turnAngle(-90_deg);
    drive.moveDistance(900);
  }

  void redFarAuton2(){

    drive.moveDistanceAsync(1175);
    diffLeft.moveVoltage(-200);
    diffRight.moveVoltage(200);
    drive.waitUntilSettled();
    pros::delay(200);
    diffLeft.moveVoltage(0);
    diffRight.moveVoltage(0);
    drive.turnAngle(45_deg);
    drive.moveDistanceAsync(500);
    diffLeft.moveVelocity(175);
    diffRight.moveVelocity(-175);
    drive.waitUntilSettled();
    drive.moveDistance(-500);
    drive.turnAngle(-120_deg);
    drive.moveDistance(900);
  }

  void ProgSkills(){

  }
