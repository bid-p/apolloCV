#include "main.h"

autonRoutines autonRoutine = notSelected;

void initProgSkills()
{
}

void executeProgSkills()
{
    odometry::currX = 13.25_in;
    odometry::currY = 36_in;
    odometry::currAngle = 90_deg;

    // Pause the macro task to prevent it from
    // taking control of the differential
    macroActTask.suspend();
    // macro::currState = macro::intakeIn;
    differential::currState = differential::intakeIn;

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{36_in, 52.25_in, 90_deg}}, "A1");

    drive::profileController.setTarget("A1");
    drive::profileController.waitUntilSettled();

    // Drive forward into the cap #1 and intake ball

    // while (!differential::hasBall())
    // {
    //     pros::delay(10);
    // }
    // differential::currState = differential::differentialStates::notRunning;

    drive::profileController.generatePath(
        {Point{36_in, 17.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 90_deg}}, "A2");

    drive::profileController.setTarget("A2", true);
    drive::profileController.waitUntilSettled();
    //Reverse to starting tile

    removePaths("A1", "A2");

    turnAngleVel(0_deg - odometry::currAngle, 100);
    // Turn left

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{84_in, 17.25_in, 0_deg}}, "B");

    drive::profileController.setTarget("B");
    drive::profileController.waitUntilSettled();
    drive::profileController.removePath("B");
    // Drive robot to shooting position

    differential::currState = differential::notRunning;
    //Stop the differential to avoid conflict with macro task

    macroActTask.resume();
    // Resume the macro task

    customShotCall(0, 120);
    // Performs double shot

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the two shots to complete

    macroActTask.suspend();
    // Pause macro task to regain control of differential

    differential::currState = differential::intakeIn;

    drive::profileController.generatePath(
        {Point{odometry::currY, 11.25_in, -odometry::currAngle}, Point{130_in, odometry::currX, 0_deg}}, "B1");

    drive::profileController.setTarget("B1");
    drive::profileController.waitUntilSettled();
    // Perform s-curve to toggle the bottom flag

    pros::delay(200);

    odometry::currY = 132_in; //resetting the y axis
    // odometry::currAngle = 0_deg; //resetting the angle

    drive::profileController.generatePath(
        {Point{84_in, 17.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "B2");

    drive::profileController.setTarget("B2", true);
    drive::profileController.waitUntilSettled();

    removePaths("B1", "B2");

    turnAngleVel(90_deg - odometry::currAngle, 100);
    // Turn right

    // drive::profileController.generatePath(
    //     {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{84_in, 53.25_in, 90_deg}}, "C1");

    drive::profileController.generatePath(
        {Point{84_in, odometry::currX, 90_deg}, Point{84_in, 52.25_in, 90_deg}}, "C1");

    // macro::currState = macro::intakeIn;
    differential::currState = differential::intakeIn;

    drive::profileController.setTarget("C1");
    drive::profileController.waitUntilSettled();
    // Drive forward into cap #2 and intake ball

    // while (!differential::hasBall())
    // {
    //     pros::delay(10);
    // }
    // differential::currState = differential::differentialStates::notRunning;

    // pros::delay(2000);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{13_in, 0_in, 0_deg}}, "C2");

    drive::profileController.setTarget("C2", true);
    drive::profileController.waitUntilSettled();

    removePaths("C1", "C2");

    drive::profileController.generatePath(
        {Point{108_in, odometry::currX, -odometry::currAngle}, Point{odometry::currY, 64.25_in, 90_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();
    // Perform another s-curve to position robot
    // in front of center column of flags

    drive::profileController.removePath("D");

    turnAngleVel(0_deg - odometry::currAngle, 100);
    // Turn to face flags

    macroActTask.resume();
    // Differential has already stopped so we may resume the macro task

    customShotCall(20, 20, true); // double check flag if you have two balls
    // Shoot middle flag

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the shot to be complete

    macroActTask.suspend();
    // Pause to return control to differential

    drive::profileController.generatePath(
        {Point{odometry::currY, 58.25_in, -odometry::currAngle}, Point{132_in, odometry::currX, 0_deg}}, "E");

    drive::profileController.setTarget("E");

    differential::currState = differential::intakeIn;

    drive::profileController.waitUntilSettled();
    // Perform another s-curve to toggle bottom flag

    odometry::currY = 132_in;    //resetting the y axis
    odometry::currAngle = 0_deg; //resetting the angle

    drive::profileController.generatePath(
        {Point{108_in, 65.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "E1");

    drive::profileController.setTarget("E1", true);
    drive::profileController.waitUntilSettled();
    // Reverse to re-align with cap #3

    removePaths("E", "E1");

    turnAngleVel(90_deg - odometry::currAngle, 100);
    // Turn to face cap #3

    differential::currState = differential::intakeOutNY;
    // Reverse intake

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{108_in, 105.25_in, 90_deg}}, "F");

    drive::profileController.setTarget("F");
    drive::profileController.waitUntilSettled();
    // Run into/flip cap

    differential::currState = differential::notRunning; //Intake off

    turnAngleVel(0_deg - odometry::currAngle, 100);
    // Turn to face low flag

    drive::profileController.generatePath(
        {Point{odometry::currY, 104.25_in, -odometry::currAngle}, Point{132_in, odometry::currX, 0_deg}}, "G");

    drive::profileController.setTarget("G");
    drive::profileController.waitUntilSettled();
    // Run into low flag

    removePaths("F", "G");

    odometry::currY = 132_in;
    odometry::currAngle = 0_deg;

    drive::profileController.generatePath(
        {Point{84_in, 104.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "H");

    drive::profileController.setTarget("H", true);
    drive::profileController.waitUntilSettled();
    // Reverse to align cap #4

    if (odometry::currAngle.convert(degree) <= 90)
    {
        turnAngleVel(-90_deg - odometry::currAngle, 100); // Turn to face cap #4
    }
    if (odometry::currAngle.convert(degree) > 90)
    {
        turnAngleVel(-90_deg - (odometry::currAngle - 360_deg), 100); // Turn to face cap #4
    }

    differential::currState = differential::intakeIn; // Run intake

    drive::profileController.generatePath(
        {Point{odometry::currY, 88.25_in, -odometry::currAngle}, Point{84_in, odometry::currX, 270_deg}}, "I");

    drive::profileController.setTarget("I");
    drive::profileController.waitUntilSettled();
    // Run into cap

    removePaths("H", "I");

    drive::profileController.generatePath(
        {Point{84_in, 93.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 270_deg}}, "J");

    drive::profileController.setTarget("J", true);
    drive::profileController.waitUntilSettled();
    // Reverse a little

    drive::profileController.generatePath(
        {Point{odometry::currY, 89.25_in, -odometry::currAngle}, Point{84_in, odometry::currX, 270_deg}}, "K");

    differential::currState = differential::intakeOutNY;
    // Reverse intake to flip cap #4

    drive::profileController.setTarget("K");
    drive::profileController.waitUntilSettled();
    // Run into/flip cap #4

    removePaths("J", "K");

    drive::profileController.generatePath(
        {Point{84_in, 133_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 270_deg}}, "L");

    drive::profileController.setTarget("L", true);
    drive::profileController.waitUntilSettled();
    // Reverse

    printf("case 1");

    differential::currState = differential::notRunning;
    // Intake Off

    printf("case 2");

    odometry::currX = 132_in;
    odometry::currAngle = 270_deg;

    printf("case 3");

    drive::profileController.generatePath(
        {Point{odometry::currY, 136.25_in, -odometry::currAngle}, Point{84_in, odometry::currX, 270_deg}}, "L1");

    printf("case 4");

    drive::profileController.setTarget("L1");

    printf("case 5");

    drive::profileController.waitUntilSettled();

    printf("case 6");

    removePaths("L", "L1");

    printf("case 7");

    turnAngleVel(0_deg - (odometry::currAngle - 360_deg), 100); // Turn to face parallel to platform

    printf("case 8");

    drive::profileController.generatePath(
        {Point{36_in, 131.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "M");

    // drive::profileController.generatePath(
    //     {Point{0_in, 0_in, odometry::currAngle}, Point{0_in, 48_in, 0_deg}}, "M");

    printf("case 9");

    drive::profileController.setTarget("M", true);
    // Move forward to align with cap #5

    printf("case 10");

    if (odometry::currAngle.convert(degree) <= 90)
    {
        turnAngleVel(-90_deg - odometry::currAngle, 100); // Turn to face cap #5
        printf("case 11");
    }
    if (odometry::currAngle.convert(degree) > 90)
    {
        turnAngleVel(-90_deg - (odometry::currAngle - 360_deg), 100); // Turn to face cap #5
        printf("case 12");
    }

    drive::profileController.removePath("M");

    differential::currState = differential::intakeIn;
    // Run intake

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{42_in, 0_in, 0_deg}}, "N");

    drive::profileController.setTarget("N");
    drive::profileController.waitUntilSettled();
    // Run into/flip cap

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{35.5_in, 22_in, 0_deg}}, "O");

    drive::profileController.setTarget("O", true);
    drive::profileController.waitUntilSettled();
    // Reverse back to reality, oh there goes gravity

    removePaths("N", "O");

    differential::currState = differential::notRunning;
    // Intake off

    turnAngleVel(92_deg, 100);
    // Turn to face flags

    macroActTask.resume();

    customShotCall(60, 120);
    // Shoot right column from far

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the shot to be complete

    macroActTask.suspend();

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{44_in, -10_in, 0_deg}}, "P");

    drive::profileController.setTarget("P");
    drive::profileController.waitUntilSettled();
    // S-Curve to align with platforms

    drive::profileController.removePath("P");

    turnAngleVel(-90_deg, 100);
    // Turn to face platforms

    differential::currState = differential::intakeIn;

    drive::chassisController.moveDistance(70_in);
    // Park

    differential::currState = differential::notRunning;
}

/*-------------------------------------------------------------------*/

void initRedNear1() {}
void executeRedNear1() {}

void initRedNear2() {}
void executeRedNear2() {}

void initRedFar1() {}
void executeRedFar1() {}

void initRedFar2() {}
void executeRedFar2() {}

void initBlueNear1() {}
void executeBlueNear1() {}

void initBlueNear2() {}
void executeBlueNear2() {}

void initBlueFar1() {}
void executeBlueFar1() {}

void initBlueFar2() {}
void executeBlueFar2() {}