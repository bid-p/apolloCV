#include "main.h"

autonRoutines autonRoutine = notSelected;

void initProgSkills()
{
}

void executeProgSkills()
{
    odometry::init();
    odometry::resetAngle(90_deg);
    odometry::currX = 13.25_in;
    odometry::currY = 36_in;

    QLength tempLength;

    // Pause the macro task to prevent it from
    // taking control of the differential
    macroActTask->suspend();
    // macro::currState = macro::intakeIn;
    differential::currState = differential::intakeIn;

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{36_in, 52.25_in, 90_deg}}, "A1");

    drive::profileController.setTarget("A1");
    drive::profileController.waitUntilSettled();

    // Drive forward into the cap #1 and intake ball

    drive::profileController.generatePath(
        {Point{36_in, 17.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 90_deg}}, "A2");

    drive::profileController.setTarget("A2", true);
    drive::profileController.waitUntilSettled();
    //Reverse to starting tile

    removePaths("A1", "A2");

    // If robot is facing less than 180 degree away from the direction of the flags,
    // turn left else turn right to face the flags.
    if (odometry::currAngle.convert(degree) <= 180)
    {
        turnAngleVel(0_deg - odometry::currAngle, 100);
    }
    else if (odometry::currAngle.convert(degree) > 180)
    {
        turnAngleVel(360_deg - odometry::currAngle, 100);
    }
    // Turn left

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{84_in, 17.25_in, 0_deg}}, "B");

    drive::profileController.setTarget("B");
    drive::profileController.waitUntilSettled();
    drive::profileController.removePath("B");
    // Drive robot to shooting position

    differential::currState = differential::notRunning;
    //Stop the differential to avoid conflict with macro task

    macroActTask->resume();
    // Resume the macro task

    customShotCall(0, 120);
    // Performs double shot

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the two shots to complete

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    differential::currState = differential::intakeIn;

    drive::profileController.generatePath(
        {Point{odometry::currY, 13.25_in, -odometry::currAngle}, Point{130_in, odometry::currX, 0_deg}}, "B1");

    drive::profileController.setTarget("B1");
    drive::profileController.waitUntilSettled();
    // Perform s-curve to toggle the bottom flag

    pros::delay(200);

    tempLength = odometry::currX;

    odometry::resetAngle(0_deg);

    odometry::currY = 132_in; //resetting the y axis

    drive::profileController.generatePath(
        {Point{84_in, 17.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "B2");

    drive::profileController.setTarget("B2", true);
    drive::profileController.waitUntilSettled();

    removePaths("B1", "B2");

    // If robot's heading is towards the cap, turn right,
    // else turn counterclockwise to face the cap.
    if (odometry::currAngle.convert(degree) <= 90)
    {
        turnAngleVel(93_deg - odometry::currAngle, 100);
    }
    else if (odometry::currAngle.convert(degree) > 270)
    {
        turnAngleVel(93_deg + (360_deg - odometry::currAngle), 100);
    }
    // Turn right

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{84_in, 55.25_in, 92_deg}}, "C1");

    // macro::currState = macro::intakeIn;
    differential::currState = differential::intakeIn;

    drive::profileController.setTarget("C1");
    drive::profileController.waitUntilSettled();
    // Drive forward into cap #2 and intake ball

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{13_in, 0_in, 0_deg}}, "C2");

    drive::profileController.setTarget("C2", true);
    drive::profileController.waitUntilSettled();

    removePaths("C1", "C2");

    drive::profileController.generatePath(
        {Point{108_in, odometry::currX, -odometry::currAngle}, Point{odometry::currY, 66.25_in, 90_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();
    // Perform another s-curve to position robot
    // in front of center column of flags

    drive::profileController.removePath("D");

    if (odometry::currAngle.convert(degree) >= 0)
    {
        turnAngleVel(0_deg - odometry::currAngle, 100);
    }
    else if (odometry::currAngle.convert(degree) > 270)
    {
        turnAngleVel(360_deg - odometry::currAngle, 100);
    }
    // Turn to face flags

    macroActTask->resume();
    // Differential has already stopped so we may resume the macro task

    customShotCall(20, 20, true); // double check flag if you have two balls
    // Shoot middle flag

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the shot to be complete

    macroActTask->suspend();
    // Pause to return control to differential

    differential::currState = differential::intakeIn;

    drive::profileController.generatePath(
        {Point{odometry::currY, 60.25_in, -odometry::currAngle}, Point{132_in, odometry::currX, 0_deg}}, "E");

    drive::profileController.setTarget("E");

    drive::profileController.waitUntilSettled();
    // Perform another s-curve to toggle bottom flag

    tempLength = odometry::currX;
    // if (odometry::currAngle > 355_deg && odometry::currAngle < 5_deg)
    // {
    odometry::resetAngle(0_deg);
    // }
    odometry::currY = 132_in;     //resetting the y axis
    odometry::currX = tempLength; //resetting the x axis

    drive::profileController.generatePath(
        {Point{108_in, 65.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "E1");

    drive::profileController.setTarget("E1", true);
    drive::profileController.waitUntilSettled();
    // Reverse to re-align with cap #3

    removePaths("E", "E1");

    if (odometry::currAngle.convert(degree) <= 90)
    {
        turnAngleVel(93_deg - odometry::currAngle, 100);
    }
    else if (odometry::currAngle.convert(degree) > 270)
    {
        turnAngleVel(93_deg + (360_deg - odometry::currAngle), 100);
    }
    // Turn right
    // Turn to face cap #3

    differential::currState = differential::intakeOutNY;
    // Reverse intake

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{108_in, 108.25_in, -92_deg}}, "F");

    drive::profileController.setTarget("F");
    drive::profileController.waitUntilSettled();
    // Run into/flip cap

    differential::currState = differential::notRunning; //Intake off

    if (odometry::currAngle.convert(degree) >= 0)
    {
        turnAngleVel(0_deg - odometry::currAngle, 100);
    }
    else if (odometry::currAngle.convert(degree) > 270)
    {
        turnAngleVel(360_deg - odometry::currAngle, 100);
    }
    // Turn to face low flag

    drive::profileController.generatePath(
        {Point{odometry::currY, 106.25_in, -odometry::currAngle}, Point{133_in, odometry::currX, 0_deg}}, "G");

    drive::profileController.setTarget("G");
    drive::profileController.waitUntilSettled();
    // Run into low flag

    removePaths("F", "G");

    tempLength = odometry::currX;
    if (odometry::currAngle > 355_deg && odometry::currAngle < 5_deg)
    {
        odometry::resetAngle(0_deg);
    }
    odometry::currY = 132_in; //resetting the y axis
    // odometry::currX = tempLength; //resetting the x axis

    drive::profileController.generatePath(
        {Point{84_in, 104.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "H");

    drive::profileController.setTarget("H", true);
    drive::profileController.waitUntilSettled();
    // Reverse to align cap #4

    if (odometry::currAngle.convert(degree) <= 90)
    {
        turnAngleVel(-90_deg - odometry::currAngle, 100);
    }
    else if (odometry::currAngle.convert(degree) > 270)
    {
        turnAngleVel(270_deg - odometry::currAngle, 100);
    } // turn to face second to last cap

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
    // Reverse into fence + fencealign

    differential::currState = differential::notRunning;
    // Intake Off

    tempLength = odometry::currY;
    if (odometry::currAngle > 265_deg && odometry::currAngle < 275_deg)
    {
        odometry::resetAngle(270_deg);
    }
    odometry::currX = 132_in;     //resetting the x axis
    odometry::currY = tempLength; //resetting the y axis

    drive::profileController.generatePath(
        {Point{odometry::currY, 127.75_in, -odometry::currAngle}, Point{84_in, odometry::currX, 270_deg}}, "L1");

    drive::profileController.setTarget("L1"); // move forwards a little bit
    drive::profileController.waitUntilSettled();

    printf("case 6");

    removePaths("L", "L1");

    printf("case 7");

    if (odometry::currAngle.convert(degree) >= 270)
    {
        turnAngleVel(360_deg - odometry::currAngle, 100);
        printf("case 11");
    }
    if (odometry::currAngle.convert(degree) < 270)
    {
        turnAngleVel(90_deg + (270_deg - odometry::currAngle), 100);
        printf("case 12");
    } // turn to face flags to move into back field

    printf("case 8");

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{48_in, 0_in, 0_deg}}, "M");

    drive::profileController.setTarget("M", true);
    drive::profileController.waitUntilSettled();
    // Move forward to align with cap #5

    if (odometry::currAngle.convert(degree) <= 90)
    {
        turnAngleVel(-90_deg - odometry::currAngle, 100);
    }
    else if (odometry::currAngle.convert(degree) > 270)
    {
        turnAngleVel(270_deg - odometry::currAngle, 100);
    } // turn to face last cap

    removePaths("L", "M");

    differential::currState = differential::intakeIn;
    // Run intake

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{44_in, 0_in, 0_deg}}, "N");

    drive::profileController.setTarget("N");
    drive::profileController.waitUntilSettled();
    // Run into/flip cap

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{38_in, 22_in, 0_deg}}, "O");

    drive::profileController.setTarget("O", true);
    drive::profileController.waitUntilSettled();
    // Reverse back to reality, oh there goes gravity

    removePaths("N", "O");

    differential::currState = differential::notRunning;
    // Intake off

    turnAngleVel(360_deg - odometry::currAngle, 100);
    // Turn to face flags

    macroActTask->resume();

    customShotCall(43, 108, true);
    // Shoot right column from far

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the shot to be complete

    macroActTask->suspend();

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{44_in, -10_in, 0_deg}}, "P");

    drive::profileController.setTarget("P");
    drive::profileController.waitUntilSettled();
    // S-Curve to align with platforms

    if (odometry::currAngle.convert(degree) <= 90)
    {
        turnAngleVel(-90_deg - odometry::currAngle, 100);
    }
    else if (odometry::currAngle.convert(degree) > 270)
    {
        turnAngleVel(270_deg - odometry::currAngle, 100);
    }
    // Turn to face platforms

    differential::currState = differential::intakeIn;

    drive::chassisController.moveDistance(70_in);
    // Park.

    drive::profileController.removePath("P");

    differential::currState = differential::notRunning;
}

/*-------------------------------------------------------------------*/

void initRedNear1() {}

void executeRedNear1()
{
    odometry::currX = 13.25_in;
    odometry::currY = 84_in;
    odometry::resetAngle(90_deg);

    // Pause the macro task to prevent it from
    // taking control of the differential
    macroActTask->suspend();
    // macro::currState = macro::intakeIn;
    differential::currState = differential::intakeIn;

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{84_in, 52.25_in, 90_deg}}, "A1");
    printf("generated path 1");

    drive::profileController.setTarget("A1");
    drive::profileController.waitUntilSettled();
    // Run into/flip first cap

    drive::profileController.generatePath(
        {Point{84_in, 17.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 90_deg}}, "A2");

    drive::profileController.setTarget("A2", true);
    drive::profileController.waitUntilSettled();
    //Reverse to starting tile

    removePaths("A1", "A2");

    turnAngleVel(0_deg - odometry::currAngle, 100);
    // Turn left

    differential::currState = differential::notRunning;
    //Stop the differential to avoid conflict with macro task

    macroActTask->resume();
    // Resume the macro task

    customShotCall(0, 120);
    // Performs double shot

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the two shots to complete

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    differential::currState = differential::intakeIn;

    drive::profileController.generatePath(
        {Point{odometry::currY, 11.25_in, -odometry::currAngle}, Point{130_in, odometry::currX, 0_deg}}, "B1");

    drive::profileController.setTarget("B1");
    drive::profileController.waitUntilSettled();
    // Perform s-curve to toggle the bottom flag

    odometry::currY = 132_in;    //resetting the y axis
    odometry::resetAngle(0_deg); // reset odometry angle

    drive::profileController.generatePath(
        {Point{108_in, 17.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "B2");

    drive::profileController.setTarget("B2", true);
    drive::profileController.waitUntilSettled();
    // Perform s-curve in reverse to get to second cap

    removePaths("B1", "B2");

    turnAngleVel(60_deg - (odometry::currAngle - 360_deg), 100);
    // Turn right

    macroActTask->resume();
    // Resume the macro task

    customShotCall(15, 120, true);
    // Performs double shot at center column

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the macro to complete

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    differential::currState = differential::intakeOutNY;

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{108_in, 37.25_in, 90_deg}}, "C");
    // Flip second cap

    drive::profileController.setTarget("C");
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 200;
    differential::currState = differential::targetTransition; // Bring lift up

    turnAngleVel(226_deg - odometry::currAngle, 150);
    // Turn right to face flag from behind

    drive::chassisController.moveDistance(-30_in);
    // Flip low flag

    removePaths("C");

    differential::currState = differential::notRunning;
    // Intake off
}

/*-------------------------------------------------------------------*/

void initRedNear2() {}
void executeRedNear2() {}

/*-------------------------------------------------------------------*/

void initRedFar1() {}
void executeRedFar1()
{
    odometry::currX = 13.25_in;
    odometry::currY = 32.5_in;
    odometry::resetAngle(90_deg);
    drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);
    macroActTask->suspend();

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{32.5_in, 55.25_in, 90_deg}}, "A1");

    drive::profileController.setTarget("A1");
    differential::currState = differential::intakeIn;
    drive::profileController.waitUntilSettled();

    turnAngleVel(-100_deg, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{6_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D", true);
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 200;
    differential::currState = differential::targetTransition;
    pros::delay(300);

    turnAngleVel(33_deg - (odometry::currAngle - 360_deg), 100);

    pros::delay(3000);

    macroActTask->resume();
    // Resume the macro task

    customShotCall(35, 95);
    // Performs double shot

    pros::delay(2000);
    // Wait for the two shots to complete

    differential::currState = differential::intakeIn;

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    turnAngleVel(310_deg - (odometry::currAngle + 360_deg), 100); // Turn to face cap #5

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{9.5_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();

    turnAngleVel(50_deg, 100); // Turn to face cap #5

    drive::chassisController.moveDistance(35_in);

    removePaths("D");
}

/*-------------------------------------------------------------------*/

void initRedFar2() {}
void executeRedFar2()
{
    odometry::currX = 13.25_in;
    odometry::currY = 32.5_in;
    odometry::resetAngle(90_deg);

    macroActTask->suspend();

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{32.5_in, 55.25_in, 90_deg}}, "A1");

    drive::profileController.setTarget("A1");
    differential::currState = differential::intakeIn;
    drive::profileController.waitUntilSettled();

    turnAngleVel(350_deg - (odometry::currAngle + 360_deg), 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{6_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D", true);
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 200;
    differential::currState = differential::targetTransition;
    pros::delay(300);

    turnAngleVel(7_deg - (odometry::currAngle - 360_deg), 100);

    pros::delay(3000);
    macroActTask->resume();
    // Resume the macro task

    customShotCall(43, 110);
    // Performs double shot

    pros::delay(2000);
    // Wait for the two shots to complete

    differential::currState = differential::intakeIn;

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    turnAngleVel(310_deg - (odometry::currAngle + 360_deg), 100); // Turn to face cap #5

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{9.5_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();

    turnAngleVel(50_deg, 100); // Turn to face cap #5

    drive::chassisController.moveDistance(35_in);

    removePaths("D");
}

/*-------------------------------------------------------------------*/

void initBlueNear1() {}
void executeBlueNear1()
{
    odometry::currX = 118.75_in;
    odometry::currY = 84_in;
    odometry::resetAngle(270_deg);

    // Pause the macro task to prevent it from
    // taking control of the differential
    macroActTask->suspend();
    // macro::currState = macro::intakeIn;
    differential::currState = differential::intakeIn;

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{84_in, 79.75_in, 270_deg}}, "A1");
    printf("generated path 1");

    drive::profileController.setTarget("A1");
    drive::profileController.waitUntilSettled();
    // Run into/flip first cap

    drive::profileController.generatePath(
        {Point{84_in, 114.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 270_deg}}, "A2");

    drive::profileController.setTarget("A2", true);
    drive::profileController.waitUntilSettled();
    //Reverse to starting tile

    removePaths("A1", "A2");

    turnAngleVel(360_deg - odometry::currAngle, 100);
    // Turn left

    differential::currState = differential::notRunning;
    //Stop the differential to avoid conflict with macro task

    macroActTask->resume();
    // Resume the macro task

    customShotCall(0, 120);
    // Performs double shot

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the two shots to complete

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    differential::currState = differential::intakeIn;

    drive::profileController.generatePath(
        {Point{odometry::currY, 120.75_in, -odometry::currAngle}, Point{130_in, odometry::currX, 0_deg}}, "B1");

    drive::profileController.setTarget("B1");
    drive::profileController.waitUntilSettled();
    // Perform s-curve to toggle the bottom flag

    odometry::currY = 132_in;    //resetting the y axis
    odometry::resetAngle(0_deg); // reset odometry angle

    drive::profileController.generatePath(
        {Point{108_in, 114.75_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "B2");

    drive::profileController.setTarget("B2", true);
    drive::profileController.waitUntilSettled();
    // Perform s-curve in reverse to get to second cap

    removePaths("B1", "B2");

    if (odometry::currAngle > 300_deg)
    {
        turnAngleVel(300_deg - odometry::currAngle, 100);
    }
    if (odometry::currAngle < 300_deg)
    {
        turnAngleVel(300_deg - (odometry::currAngle + 360_deg), 100);
    } // Turn left

    macroActTask->resume();
    // Resume the macro task

    customShotCall(15, 120, true);
    // Performs double shot at center column

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the macro to complete

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    differential::currState = differential::intakeOutNY;

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{108_in, 94.75_in, 270_deg}}, "C");
    // Flip second cap

    drive::profileController.setTarget("C");
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 200;
    differential::currState = differential::targetTransition; // Bring lift up

    turnAngleVel(134_deg - odometry::currAngle, 150);
    // Turn right to face flag from behind

    drive::chassisController.moveDistance(-30_in);
    // Flip low flag

    removePaths("C");

    differential::currState = differential::notRunning;
    // Intake off
}

/*-------------------------------------------------------------------*/

void initBlueNear2() {}
void executeBlueNear2() {}

/*-------------------------------------------------------------------*/

void initBlueFar1() {}
void executeBlueFar1()
{
    odometry::currX = 118.75_in;
    odometry::currY = 32.5_in;
    odometry::resetAngle(270_deg);

    drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);
    macroActTask->suspend();

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{32.5_in, 76.75_in, 270_deg}}, "A1");

    drive::profileController.setTarget("A1");
    differential::currState = differential::intakeIn;
    drive::profileController.waitUntilSettled();

    turnAngleVel(100_deg, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{6_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D", true);
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 200;
    differential::currState = differential::targetTransition;
    pros::delay(300);

    turnAngleVel(327_deg - (odometry::currAngle + 360_deg), 100);

    pros::delay(3000);

    macroActTask->resume();
    // Resume the macro task

    customShotCall(35, 95);
    // Performs double shot

    pros::delay(2000);
    // Wait for the two shots to complete

    differential::currState = differential::intakeIn;

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    turnAngleVel(odometry::currAngle - (50_deg + 360_deg), 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{9.5_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();

    turnAngleVel(-50_deg, 100); // Turn to face cap #5

    drive::chassisController.moveDistance(35_in);

    removePaths("D");
}

/*-------------------------------------------------------------------*/

void initBlueFar2() {}
void executeBlueFar2()
{
    odometry::currX = 118.75_in;
    odometry::currY = 32.5_in;
    odometry::resetAngle(270_deg);

    macroActTask->suspend();

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{32.5_in, 76.75_in, 270_deg}}, "A1");

    drive::profileController.setTarget("A1");
    differential::currState = differential::intakeIn;
    drive::profileController.waitUntilSettled();

    turnAngleVel(10_deg - (odometry::currAngle - 360_deg), 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{6_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D", true);
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 200;
    differential::currState = differential::targetTransition;
    pros::delay(300);

    turnAngleVel(7_deg - (odometry::currAngle + 360_deg), 100);

    pros::delay(3000);
    macroActTask->resume();
    // Resume the macro task

    customShotCall(43, 110);
    // Performs double shot

    pros::delay(2000);
    // Wait for the two shots to complete

    differential::currState = differential::intakeIn;

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    turnAngleVel(50_deg - odometry::currAngle, 100);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{9.5_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();

    turnAngleVel(-50_deg, 100); // Turn to face cap #5

    drive::chassisController.moveDistance(35_in);

    removePaths("D");
}