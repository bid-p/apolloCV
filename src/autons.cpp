#include "main.h"

autonRoutines autonRoutine = notSelected;

void initProgSkills()
{
    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{39_in, 0_in, 0_deg}}, "A1");
    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{35_in, 0_in, 0_deg}}, "A2");
}

void executeProgSkills()
{
    // Pause the macro task to prevent it from
    // taking control of the differential
    macroActTask.suspend();
    // macro::currState = macro::intakeIn;
    differential::currState = differential::intakeIn;

    drive::profileController.setTarget("A1");
    drive::profileController.waitUntilSettled();
    // Drive forward into the cap #1 and intake ball

    // while (!differential::hasBall())
    // {
    //     pros::delay(10);
    // }
    // differential::currState = differential::differentialStates::notRunning;

    drive::profileController.setTarget("A2", true);
    drive::profileController.waitUntilSettled();
    //Reverse to starting tile

    turnAngleVel(-90_deg, 100);
    // Turn left

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{50_in, 0_in, 0_deg}}, "forward");

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

    removePaths("A1", "A2");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{46_in, 8_in, 0_deg}}, "B");

    drive::profileController.setTarget("B");
    drive::profileController.waitUntilSettled();
    // Perform s-curve to toggle the bottom flag

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{47_in, -8_in, 0_deg}}, "B1");

    drive::profileController.setTarget("B1", true);
    drive::profileController.waitUntilSettled();

    removePaths("B", "B1");

    turnAngleVel(90_deg, 100);
    // Turn right

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{35_in, 0_in, 0_deg}}, "C1");
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
        {Point{0_in, 0_in, 0_deg}, Point{28_in, 6_in, 0_deg}}, "E");

    drive::profileController.setTarget("E");
    drive::profileController.waitUntilSettled();
    // Perform another s-curve to toggle bottom flag

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{25_in, -6_in, 0_deg}}, "E1");

    drive::profileController.setTarget("E1", true);
    drive::profileController.waitUntilSettled();
    // Reverse to re-align with cap #3

    removePaths("E", "E1");

    turnAngleVel(90_deg, 100);
    // Turn to face cap #3

    differential::currState = differential::intakeOutNY;
    // Reverse intake

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "F");

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
        {Point{0_in, 0_in, 0_deg}, Point{49_in, 0_in, 0_deg}}, "H");

    drive::profileController.setTarget("H", true);
    drive::profileController.waitUntilSettled();
    // Reverse to align cap #4

    turnAngleVel(-90_deg, 100); // Turn to face cap #4

    differential::currState = differential::intakeIn; // Run intake

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{18_in, 0_in, 0_deg}}, "I");

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
        {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "L");

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

    removePaths("L", "M");

    turnAngleVel(90_deg, 100);
    // Turn to face cap #5

    differential::currState = differential::intakeIn;
    // Run intake

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{46_in, 0_in, 0_deg}}, "N");

    drive::profileController.setTarget("N");
    drive::profileController.waitUntilSettled();
    // Run into/flip cap

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{28_in, 0_in, 0_deg}}, "O");

    drive::profileController.setTarget("O", true);
    drive::profileController.waitUntilSettled();
    // Reverse back to reality, oh there goes gravity

    removePaths("J", "K");

    differential::currState = differential::notRunning;
    // Intake off

    turnAngleVel(90_deg, 100);
    // Turn to face flags

    customShotCall(20, 120);
    // Shoot right column from far

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{24_in, -10_in, 0_deg}}, "P");

    drive::profileController.setTarget("P");
    drive::profileController.waitUntilSettled();
    // S-Curve to align with platforms

    turnAngleVel(-90_deg, 100);
    // Turn to face platforms

    drive::chassisController.moveDistance(65_in);
    // Park.
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