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
    macroActTask.suspend();
    // macro::currState = macro::intakeIn;
    differential::currState = differential::intakeIn;

    drive::profileController.setTarget("A1");
    drive::profileController.waitUntilSettled();
    // while (!differential::hasBall())
    // {
    //     pros::delay(10);
    // }
    // differential::currState = differential::differentialStates::notRunning;

    drive::profileController.setTarget("A2", true);
    drive::profileController.waitUntilSettled();

    turnAngleVel(-90_deg, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{50_in, 0_in, 0_deg}}, "forward");

    drive::profileController.setTarget("forward");
    drive::profileController.waitUntilSettled();

    printf("checkpoint 69");

    drive::profileController.removePath("forward");

    printf("checkpoint 1");

    differential::currState = differential::notRunning;

    printf("checkpoint 2");

    macroActTask.resume();

    printf("checkpoint 3");

    customShotCall(0, 120);

    printf("checkpoint 4");

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }

    macroActTask.suspend();

    removePaths("A1", "A2");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{46_in, 8_in, 0_deg}}, "B");

    drive::profileController.setTarget("B");
    drive::profileController.waitUntilSettled();

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{47_in, -8_in, 0_deg}}, "B1");

    drive::profileController.setTarget("B1", true);
    drive::profileController.waitUntilSettled();

    removePaths("B", "B1");

    turnAngleVel(90_deg, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{38_in, 0_in, 0_deg}}, "C1");
    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{15_in, 0_in, 0_deg}}, "C2");

    // macro::currState = macro::intakeIn;
    differential::currState = differential::intakeIn;


    drive::profileController.setTarget("C1");
    drive::profileController.waitUntilSettled();

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

    drive::profileController.removePath("D");

    turnAngleVel(-90_deg, 100);

    macroActTask.resume();

    customShotCall(20);

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }

    macroActTask.suspend();

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{28_in, 6_in, 0_deg}}, "E");

    drive::profileController.setTarget("E");
    drive::profileController.waitUntilSettled();

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{25_in, -6_in, 0_deg}}, "E1");

    drive::profileController.setTarget("E1", true);
    drive::profileController.waitUntilSettled();

    removePaths("E", "E1");

    turnAngleVel(90_deg, 100);

    differential::currState = differential::intakeOutNY;

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{40_in, 0_in, 0_deg}}, "F");

    drive::profileController.setTarget("F");
    drive::profileController.waitUntilSettled();

    differential::currState = differential::notRunning;

    turnAngleVel(-90_deg, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{24_in, 0_in, 0_deg}}, "G");

    drive::profileController.setTarget("G");
    drive::profileController.waitUntilSettled();

    removePaths("F", "G");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{48_in, 0_in, 0_deg}}, "H");

    drive::profileController.setTarget("H", true);
    drive::profileController.waitUntilSettled();

    turnAngleVel(-90_deg, 100);
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