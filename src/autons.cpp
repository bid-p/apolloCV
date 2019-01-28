#include "main.h"

autonRoutines autonRoutine = notSelected;

void initProgSkills()
{
}

void executeProgSkills()
{
    odometry::currX = 24_in;
    odometry::currY = 36_in;
    odometry::currAngle = 90_deg;

    // Pause the macro task to prevent it from
    // taking control of the differential
    macroActTask.suspend();
    // macro::currState = macro::intakeIn;
    differential::currState = differential::intakeIn;

    drive::profileController.generatePath(
        {Point{odometry::currX, odometry::currY, odometry::currAngle}, Point{63_in, 36_in, 90_deg}}, "A1");

    drive::profileController.setTarget("A1");
    drive::profileController.waitUntilSettled();
    // Drive forward into the cap #1 and intake ball

    // while (!differential::hasBall())
    // {
    //     pros::delay(10);
    // }
    // differential::currState = differential::differentialStates::notRunning;

    drive::profileController.generatePath(
        {Point{20_in, 36_in, 90_deg}, Point{odometry::currX, odometry::currY, odometry::currAngle}}, "A2");

    drive::profileController.setTarget("A2", true);
    drive::profileController.waitUntilSettled();
    //Reverse to starting tile

    removePaths("A1", "A2");

    turnAngleVel(0_deg - odometry::currAngle, 100);
    // Turn left

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, odometry::currAngle}, Point{88_in, 20_in, 0_deg}}, "forward");

    drive::profileController.setTarget("forward");
    drive::profileController.waitUntilSettled();
    drive::profileController.removePath("forward");
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

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, odometry::currAngle}, Point{132_in, 13_in, 0_deg}}, "B");

    drive::profileController.setTarget("B");
    drive::profileController.waitUntilSettled();
    // Perform s-curve to toggle the bottom flag

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, odometry::currAngle}, Point{86_in, 20_in, 0_deg}}, "B1");

    drive::profileController.setTarget("B1", true);
    drive::profileController.waitUntilSettled();

    removePaths("B", "B1");

    turnAngleVel(90_deg - currAngle, 100);
    // Turn right

    drive::profileController.generatePath(
        {Point{odometry::currX, odometry::currX, odometry::currAngle}, Point{35_in, 0_in, 90_deg}}, "C1");
    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{12_in, 0_in, 0_deg}}, "C2");

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

    drive::profileController.setTarget("C2", true);
    drive::profileController.waitUntilSettled();

    removePaths("C1", "C2");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{22_in, 24_in, 0_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();
    // Perform another s-curve to position robot
    // in front of center column of flags

    drive::profileController.removePath("D");

    turnAngleVel(-90_deg, 100);
    // Turn to face flags

    macroActTask.resume();
    // Differential has already stopped so we may resume the macro task

    customShotCall(20);
    // Shoot middle flag

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the shot to be complete

    macroActTask.suspend();
    // Pause to return control to differential

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{27_in, 6_in, 0_deg}}, "E");

    drive::profileController.setTarget("E");
    drive::profileController.waitUntilSettled();
    // Perform another s-curve to toggle bottom flag

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{26_in, -6_in, 0_deg}}, "E1");

    drive::profileController.setTarget("E1", true);
    drive::profileController.waitUntilSettled();
    // Reverse to re-align with cap #3

    removePaths("E", "E1");

    turnAngleVel(90_deg, 100);
    // Turn to face cap #3

    differential::currState = differential::intakeOutNY;
    // Reverse intake

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{41_in, 0_in, 0_deg}}, "F");

    drive::profileController.setTarget("F");
    drive::profileController.waitUntilSettled();
    // Run into/flip cap

    differential::currState = differential::notRunning; //Intake off

    turnAngleVel(-90_deg, 100);
    // Turn to face low flag

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{24_in, 0_in, 0_deg}}, "G");

    drive::profileController.setTarget("G");
    drive::profileController.waitUntilSettled();
    // Run into low flag

    removePaths("F", "G");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{48_in, 0_in, 0_deg}}, "H");

    drive::profileController.setTarget("H", true);
    drive::profileController.waitUntilSettled();
    // Reverse to align cap #4

    turnAngleVel(-90_deg, 100); // Turn to face cap #4

    differential::currState = differential::intakeIn; // Run intake

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{19_in, 0_in, 0_deg}}, "I");

    drive::profileController.setTarget("I");
    drive::profileController.waitUntilSettled();
    // Run into cap

    removePaths("H", "I");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{5_in, 0_in, 0_deg}}, "J");

    drive::profileController.setTarget("J", true);
    drive::profileController.waitUntilSettled();
    // Reverse a little

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{6_in, 0_in, 0_deg}}, "K");

    differential::currState = differential::intakeOutNY;
    // Reverse intake to flip cap #4

    drive::profileController.setTarget("K");
    drive::profileController.waitUntilSettled();
    // Run into/flip cap #4

    removePaths("J", "K");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{42_in, 0_in, 0_deg}}, "L");

    drive::profileController.setTarget("L", true);
    drive::profileController.waitUntilSettled();
    // Reverse

    differential::currState = differential::notRunning;
    // Intake Off

    turnAngleVel(-90_deg, 100); // Turn to face parallel to platform

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{48_in, 0_in, 0_deg}}, "M");

    drive::profileController.setTarget("M");
    drive::profileController.waitUntilSettled();
    // Move forward to align with cap #5

    turnAngleVel(90_deg, 100);
    // Turn to face cap #5

    removePaths("L", "M");

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

    drive::chassisController.moveDistance(65_in);
    // Park.

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