#include "main.h"

autonRoutines autonRoutine = notSelected;

void initProgSkills()
{
    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "A1");
    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{35_in, 0_in, 0_deg}}, "A2");
}

void executeProgSkills()
{
    // macro::currState = macro::intakeIn;

    drive::profileController.setTarget("A1");
    drive::profileController.waitUntilSettled();
    while (!differential::hasBall())
    {
        pros::delay(10);
    }
    differential::currState = differential::differentialStates::notRunning;

    drive::profileController.setTarget("A2", true);
    drive::profileController.waitUntilSettled();

    turnAngleVel(-90_deg, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{48_in, 0_in, 0_deg}}, "forward");

    drive::profileController.setTarget("forward");
    drive::profileController.waitUntilSettled();
    drive::profileController.removePath("forward");

    customShotCall(20, 120);

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }

    removePaths("A1", "A2");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{48_in, 8_in, 0_deg}}, "B");

    drive::profileController.setTarget("B");
    drive::profileController.waitUntilSettled();

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{50_in, -8_in, 0_deg}}, "B1");

    drive::profileController.setTarget("B1", true);
    drive::profileController.waitUntilSettled();

    removePaths("B", "B1");

    turnAngleVel(90_deg, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{42_in, 0_in, 0_deg}}, "C1");
    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{19_in, 0_in, 0_deg}}, "C2");

    // macro::currState = macro::intakeIn;

    drive::profileController.setTarget("C1");
    drive::profileController.waitUntilSettled();

    while (!differential::hasBall())
    {
        pros::delay(10);
    }
    differential::currState = differential::differentialStates::notRunning;

    drive::profileController.setTarget("C2", true);
    drive::profileController.waitUntilSettled();

    removePaths("C1", "C2");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{22_in, 24_in, 0_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();

    drive::profileController.removePath("D");

    turnAngleVel(-90_deg, 100);

    customShotCall(20, 120);

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{25_in, 6_in, 0_deg}}, "E");

    drive::profileController.setTarget("E");
    drive::profileController.waitUntilSettled();

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{25_in, -6_in, 0_deg}}, "E1");

    drive::profileController.setTarget("E1", true);
    drive::profileController.waitUntilSettled();

    removePaths("E", "E1");

    turnAngleVel(90_deg, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "F");

    drive::profileController.setTarget("F");
    // differential::currState = differential::differentialStates::intakeOut;

    // drive::profileController.waitUntilSettled();
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