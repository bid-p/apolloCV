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
    differential::currState = differential::differentialStates::intakeIn;
    drive::profileController.setTarget("A1");
    while (!differential::hasBall)
    {
        pros::delay(10);
    }
    differential::currState = differential::differentialStates::notRunning;
    drive::profileController.waitUntilSettled();

    drive::profileController.setTarget("A2", true);
    drive::profileController.waitUntilSettled();

    turnAngleVel(-90_deg, 100);

    customShotCall(20, 120);

    while (macro::currState != macro::macroStates::none)
    {
        pros::delay(10);
    }

    removePaths("A1", "A2");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{45_in, 8_in, 0_deg}}, "B");

    drive::profileController.setTarget("B");
    drive::profileController.waitUntilSettled();

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{45_in, -8_in, 0_deg}}, "B1");

    drive::profileController.setTarget("B1", true);

    removePaths("B1", "B2");

    turnAngleVel(90_deg, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "C1");
    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{20_in, 0_in, 0_deg}}, "C2");

    differential::currState = differential::differentialStates::intakeIn;
    drive::profileController.setTarget("C1");
    while (!differential::hasBall)
    {
        pros::delay(10);
    }
    differential::currState = differential::differentialStates::notRunning;
    drive::profileController.waitUntilSettled();

    drive::profileController.setTarget("C2", true);
    drive::profileController.waitUntilSettled();

    removePaths("C1", "C2");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{34_in, 24_in, 0_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();

    turnAngleVel(-90_deg, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{20_in, 8_in, 0_deg}}, "E");

    drive::profileController.setTarget("E");
    drive::profileController.waitUntilSettled();

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{20_in, -8_in, 0_deg}}, "E1");

    drive::profileController.setTarget("E", true);
    drive::profileController.waitUntilSettled();

    turnAngleVel(90_deg, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "F");

    drive::profileController.setTarget("F");
    differential::currState = differential::differentialStates::intakeOut;

    drive::profileController.waitUntilSettled();
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