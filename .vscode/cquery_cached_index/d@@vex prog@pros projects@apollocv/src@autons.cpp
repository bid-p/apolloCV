#include "main.h"

autonRoutines autonRoutine = notSelected;

void initProgSkills()
{
    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{45_in, 0_in, 0_deg}}, "A1");
    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{38_in, 0_in, 0_deg}}, "A2");
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

    removePaths("A1", "A2");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{45_in, 4_in, 0_deg}}, "B");

    drive::profileController.setTarget("B");
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