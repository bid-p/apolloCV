#include "main.h"

autonRoutines autonRoutine = notSelected;

void executeProgSkills()
{
    odometry::init();
    odometry::resetAngle(90_deg);
    odometry::currX = 13.25_in;
    odometry::currY = 36_in;

    // Pause the macro task to prevent it from
    // taking control of the differential
    macroActTask->suspend();

    differential::currState = differential::intakeIn;

    path::Path *A1 = new path::Line(
        {odometry::currX, odometry::currY},
        {53.25_in, 36_in},
        200,
        200);
    drive::appc.runPath(A1);
    // Drive forward into the cap #1 and intake ball

    path::Path *A2 = new path::Line(
        {odometry::currX, odometry::currY},
        {17.75_in, 36_in},
        200,
        200);
    drive::appc.runPath(A2);

    drive::turn(0_deg);
    // Turn left

    // drive::profileController.generatePath(
    //     {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{84_in, 16.25_in, 0_deg}}, "B");

    // drive::profileController.setTarget("B");
    // drive::profileController.waitUntilSettled();
    // drive::profileController.removePath("B");

    path::Path *B = new path::Line(
        {odometry::currX, odometry::currY},
        {17.75_in, 84_in},
        200,
        200);
    drive::appc.runPath(B);
    // Drive robot to shooting position

    drive::turn(0_deg);
    // Correct for any angle inaccuracies

    differential::currState = differential::notRunning;
    //Stop the differential to avoid conflict with macro task

    macroActTask->resume();
    // Resume the macro task

    customShotCall(15, 110);
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
        {Point{odometry::currY, 13.25_in, -odometry::currAngle}, Point{132_in, odometry::currX, 0_deg}}, "B1");

    drive::profileController.setTarget("B1");
    drive::profileController.waitUntilSettled();
    // Perform s-curve to toggle the bottom flag

    pros::delay(200);

    odometry::resetAngle(0_deg);

    odometry::currY = 132_in; //resetting the y axis

    drive::profileController.generatePath(
        {Point{84_in, 17.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "B2");

    drive::profileController.setTarget("B2", true);
    pros::delay(1200);
    differential::currState = differential::intakeOutNY;
    drive::profileController.waitUntilSettled();

    removePaths("B1", "B2");

    drive::turn(90_deg);
    // Turn right

    path::Path *C1 = new path::Line(
        {odometry::currX, odometry::currY},
        {57.25_in, 84_in},
        200,
        200);

    differential::currState = differential::intakeIn;
    drive::appc.runPath(C1);
    // Drive forward into cap #2 and intake ball

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{14_in, 0_in, 0_deg}}, "C2");

    drive::profileController.setTarget("C2", true);
    drive::profileController.waitUntilSettled();

    removePaths("C2");

    drive::profileController.generatePath(
        {Point{108_in, odometry::currX, -odometry::currAngle}, Point{odometry::currY, 66.25_in, 90_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();
    // Perform another s-curve to position robot
    // in front of center column of flags

    drive::profileController.removePath("D");

    drive::turn(0_deg);
    // Turn to face flags

    macroActTask->resume();
    // Differential has already stopped so we may resume the macro task

    customShotCall(40, 40, true); // double check flag if you have two balls
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
        {Point{odometry::currY, 60.25_in, -odometry::currAngle}, Point{133_in, odometry::currX, 0_deg}}, "E");

    drive::profileController.setTarget("E");
    drive::profileController.waitUntilSettled();
    // Perform another s-curve to toggle bottom flag

    if (odometry::currAngle > 355_deg && odometry::currAngle < 5_deg)
    {
        odometry::resetAngle(0_deg);
    }
    if (odometry::currAngle > 355_deg && odometry::currAngle < 5_deg && odometry::currY > 130_in)
    {
        odometry::currY = 132_in; //resetting the y axis
    }

    drive::profileController.generatePath(
        {Point{107_in, 65.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "E1");

    drive::profileController.setTarget("E1", true);
    drive::profileController.waitUntilSettled();
    // Reverse to re-align with cap #3

    removePaths("E", "E1");

    drive::turn(90_deg);
    // Turn right
    // Turn to face cap #3

    differential::currState = differential::intakeOutNY;
    // Reverse intake

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{106_in, 109.25_in, 95_deg}}, "F");

    drive::profileController.setTarget("F");
    drive::profileController.waitUntilSettled();
    // Run into/flip cap

    differential::currState = differential::notRunning; //Intake off

    drive::turn(0_deg);
    // Turn to face low flag

    drive::profileController.generatePath(
        {Point{odometry::currY, 107.5_in, -odometry::currAngle}, Point{133_in, odometry::currX, 0_deg}}, "G");

    drive::profileController.setTarget("G");
    drive::profileController.waitUntilSettled();
    // Run into low flag

    removePaths("F", "G");

    if (odometry::currAngle > 355_deg && odometry::currAngle < 5_deg)
    {
        odometry::resetAngle(0_deg);
    }
    if (odometry::currAngle > 355_deg && odometry::currAngle < 5_deg && odometry::currY > 130_in)
    {
        odometry::currY = 132_in; //resetting the y axis
    }

    path::Path *H = new path::Line(
        {odometry::currX, odometry::currY},
        {104.25_in, 84_in},
        200,
        200);
    drive::appc.runPath(H);
    // Reverse to align cap #4

    drive::turn(270_deg);
    // turn to face second to last cap

    differential::currState = differential::intakeIn; // Run intake

    path::Path *I = new path::Line(
        {odometry::currX, odometry::currY},
        {90.25_in, 84_in},
        200,
        200);
    drive::appc.runPath(I);
    // Run into cap

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
        {Point{84_in, 140_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 270_deg}}, "L");

    drive::profileController.setTarget("L", true);
    drive::profileController.waitUntilSettled();
    // Reverse into fence + fencealign

    odometry::resetAngle(270_deg);

    if (odometry::currX > 130_in)
    {
        odometry::currX = 134.5_in; //resetting the x axis
    }
    // odometry::currX = 132_in; //resetting the x axis

    drive::profileController.generatePath(
        {Point{odometry::currY, 127.75_in, -odometry::currAngle}, Point{84_in, odometry::currX, 270_deg}}, "L1");

    drive::profileController.setTarget("L1"); // move forwards a little bit
    drive::profileController.waitUntilSettled();

    differential::currState = differential::notRunning;
    // Intake Off

    drive::turn(0_deg);

    // path::Path *M = new path::Line(
    //     {odometry::currX, odometry::currY},
    //     {132_in, 36_in},
    //     200,
    //     200);
    // drive::appc.runPath(M);

    drive::profileController.generatePath(
        {Point{36_in, 127.75_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "M");

    drive::profileController.setTarget("M", true);
    drive::profileController.waitUntilSettled();
    // Move backwards to align with cap #5

    drive::turn(270_deg);

    differential::currState = differential::intakeIn;
    // Run intake

    path::Path *N = new path::Line(
        {odometry::currX, odometry::currY},
        {91_in, 36_in},
        200,
        200);
    drive::appc.runPath(N);
    // Run into/flip cap

    path::Path *O = new path::Line(
        {odometry::currX, odometry::currY},
        {126_in, 34_in},
        200,
        200);
    drive::appc.runPath(O);
    // Reverse back to reality, oh there goes gravity

    differential::currState = differential::notRunning;
    // Intake off

    drive::turn(0_deg);
    // Turn to face flags

    macroActTask->resume();

    customShotCall(75, 140, true);
    // Shoot right column from far

    while (macro::currState != macro::none)
    {
        pros::delay(10);
    }
    // Wait for the shot to be complete

    macroActTask->suspend();

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{24_in, -10_in, 0_deg}}, "P");

    drive::profileController.setTarget("P");
    drive::profileController.waitUntilSettled();
    // S-Curve to align with platforms

    drive::turn(270_deg);
    // Turn to face platforms

    differential::currState = differential::intakeIn;

    drive::chassisController.moveDistance(70_in);
    // Park.

    drive::profileController.removePath("P");

    differential::currState = differential::notRunning;
}

/*-------------------------------------------------------------------*/

void executeRedNear1()
{
    odometry::currX = 13.25_in;
    odometry::currY = 84_in;
    odometry::resetAngle(90_deg);

    // Pause the macro task to prevent it from
    // taking control of the differential
    macroActTask->suspend();

    differential::currState = differential::intakeIn;

    path::Path *A1 = new path::Line(
        {odometry::currX, odometry::currY},
        {53.25_in, 84_in},
        200,
        200);
    drive::appc.runPath(A1);
    // Drive forward into the cap #1 and intake ball

    path::Path *A2 = new path::Line(
        {odometry::currX, odometry::currY},
        {17.25_in, 84_in},
        200,
        200);
    drive::appc.runPath(A2);
    //Reverse to starting tile

    drive::turn(0_deg);
    // Turn left

    differential::currState = differential::notRunning;
    //Stop the differential to avoid conflict with macro task

    macroActTask->resume();
    // Resume the macro task

    customShotCall(15, 100);
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
        {Point{odometry::currY, 11.25_in, -odometry::currAngle}, Point{132_in, odometry::currX, 0_deg}}, "B1");

    drive::profileController.setTarget("B1");
    drive::profileController.waitUntilSettled();
    // Perform s-curve to toggle the bottom flag

    if (odometry::currY > 130_in)
    {
        odometry::currY = 132_in; //resetting the y axis
    }
    if (odometry::currAngle > 355_deg && odometry::currAngle < 5_deg)
    {
        odometry::resetAngle(0_deg); // reset odometry angle
    }

    drive::profileController.generatePath(
        {Point{108_in, 17.25_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "B2");

    drive::profileController.setTarget("B2", true);
    drive::profileController.waitUntilSettled();
    // Perform s-curve in reverse to get to second cap

    removePaths("B1", "B2");

    if (puncher::puncherIsLoaded)
    {
        drive::turn(60_deg);
        // Turn right

        macroActTask->resume();
        // Resume the macro task

        customShotCall(25, 120, true);
        // Performs double shot at center column

        while (macro::currState != macro::none)
        {
            pros::delay(10);
        }
        // Wait for the macro to complete

        macroActTask->suspend();
        // Pause macro task to regain control of differential
    }
    else
    {
        drive::turn(90_deg);
    }

    differential::currState = differential::intakeOutNY;

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{108_in, 37.25_in, 90_deg}}, "C");
    // Flip second cap

    drive::profileController.setTarget("C");
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 200;
    differential::currState = differential::targetTransition; // Bring lift up

    drive::turn(230_deg, 150);
    // Turn right to face flag from behind

    drive::chassisController.setMaxVelocity(200);
    drive::chassisController.moveDistance(-30_in);
    drive::chassisController.setMaxVelocity(200);

    // Flip low flag

    removePaths("C");

    differential::currState = differential::notRunning;
    // Intake off

    path::Path *D = new path::Bezier(
        {path::Point{odometry::currX, odometry::currY},
         path::Point{30_in, 115_in},
         path::Point{50_in, 110_in},
         path::Point{50_in, 90_in}},
        200,
        200);
    drive::appc.runPath(D);

    drive::turn(180_deg, 200);

    differential::currState = differential::intakeIn;
    drive::chassisController.moveDistance(40_in);
    differential::currState = differential::notRunning;
    //park
}

/*-------------------------------------------------------------------*/

void executeRedNear2() {}

/*-------------------------------------------------------------------*/

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

    drive::turn(350_deg);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{6_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D", true);
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 200;
    differential::currState = differential::targetTransition;
    pros::delay(300);

    drive::turn(33_deg);

    pros::delay(3000);

    macroActTask->resume();
    // Resume the macro task

    customShotCall(70, 140);
    // Performs double shot

    pros::delay(2000);
    // Wait for the two shots to complete

    differential::currState = differential::intakeIn;

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    drive::turn(310_deg);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{9.5_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();

    drive::turn(0_deg);

    drive::chassisController.moveDistance(40_in);

    removePaths("D");
}

/*-------------------------------------------------------------------*/

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

    drive::turn(350_deg);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{6_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D", true);
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 200;
    differential::currState = differential::targetTransition;
    pros::delay(300);

    drive::turn(6_deg);

    pros::delay(3000);
    macroActTask->resume();
    // Resume the macro task

    customShotCall(75, 140);
    // Performs double shot

    pros::delay(2000);
    // Wait for the two shots to complete

    differential::currState = differential::intakeIn;

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    drive::turn(310_deg); // Turn to face cap #5

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{9.5_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();

    drive::turn(0_deg); // Turn to face cap #5

    drive::chassisController.moveDistance(40_in);

    removePaths("D");
}

/*-------------------------------------------------------------------*/

void executeBlueNear1()
{
    odometry::currX = 130.75_in;
    odometry::currY = 84_in;
    odometry::resetAngle(270_deg);

    // Pause the macro task to prevent it from
    // taking control of the differential
    macroActTask->suspend();

    differential::currState = differential::intakeIn;

    path::Path *A1 = new path::Line(
        {odometry::currX, odometry::currY},
        {90.75_in, 84_in},
        200,
        200);
    drive::appc.runPath(A1);
    // Drive forward into the cap #1 and intake ball

    path::Path *A2 = new path::Line(
        {odometry::currX, odometry::currY},
        {127.75_in, 84_in},
        200,
        200);
    drive::appc.runPath(A2);
    //Reverse to starting tile

    drive::turn(0_deg);
    // Turn left

    differential::currState = differential::notRunning;
    //Stop the differential to avoid conflict with macro task

    macroActTask->resume();
    // Resume the macro task

    customShotCall(15, 100);
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
        {Point{odometry::currY, 132.75_in, -odometry::currAngle}, Point{132_in, odometry::currX, 0_deg}}, "B1");

    drive::profileController.setTarget("B1");
    drive::profileController.waitUntilSettled();
    // Perform s-curve to toggle the bottom flag

    if (odometry::currY > 130_in)
    {
        odometry::currY = 132_in; //resetting the y axis
    }
    if (odometry::currAngle > 355_deg && odometry::currAngle < 5_deg)
    {
        odometry::resetAngle(0_deg); // reset odometry angle
    }

    drive::profileController.generatePath(
        {Point{108_in, 126.75_in, odometry::currAngle}, Point{odometry::currY, odometry::currX, 0_deg}}, "B2");

    drive::profileController.setTarget("B2", true);
    drive::profileController.waitUntilSettled();
    // Perform s-curve in reverse to get to second cap

    removePaths("B1", "B2");

    if (puncher::puncherIsLoaded)
    {
        drive::turn(300_deg);
        // Turn right

        macroActTask->resume();
        // Resume the macro task

        customShotCall(25, 120, true);
        // Performs double shot at center column

        while (macro::currState != macro::none)
        {
            pros::delay(10);
        }
        // Wait for the macro to complete

        macroActTask->suspend();
        // Pause macro task to regain control of differential
    }
    else
    {
        drive::turn(270_deg);
    }

    differential::currState = differential::intakeOutNY;

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{108_in, 106.75_in, 270_deg}}, "C");
    // Flip second cap

    drive::profileController.setTarget("C");
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 250;
    differential::currState = differential::targetTransition; // Bring lift up

    drive::turn(130_deg, 150);
    // Turn right to face flag from behind

    drive::chassisController.setMaxVelocity(200);
    drive::chassisController.moveDistance(-30_in);
    drive::chassisController.setMaxVelocity(200);

    // Flip low flag

    removePaths("C");

    differential::currState = differential::notRunning;
    // Intake off

    path::Path *D = new path::Bezier(
        {path::Point{odometry::currX, odometry::currY},
         path::Point{114_in, 115_in},
         path::Point{94_in, 110_in},
         path::Point{94_in, 90_in}},
        200,
        200);
    drive::appc.runPath(D);

    drive::turn(180_deg, 200);

    differential::currState = differential::intakeIn;
    drive::chassisController.moveDistance(40_in);
    differential::currState = differential::notRunning;
    //park
}

/*-------------------------------------------------------------------*/

void executeBlueNear2() {}

/*-------------------------------------------------------------------*/

void executeBlueFar1()
{
    odometry::currX = 130.75_in;
    odometry::currY = 32.5_in;
    odometry::resetAngle(270_deg);
    drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);
    macroActTask->suspend();

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{32.5_in, 88.75_in, 270_deg}}, "A1");

    drive::profileController.setTarget("A1");
    differential::currState = differential::intakeIn;
    drive::profileController.waitUntilSettled();

    drive::turn(10_deg);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{6_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D", true);
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 200;
    differential::currState = differential::targetTransition;
    pros::delay(300);

    drive::turn(332_deg);

    pros::delay(3000);

    macroActTask->resume();
    // Resume the macro task

    customShotCall(70, 140);
    // Performs double shot

    pros::delay(2000);
    // Wait for the two shots to complete

    differential::currState = differential::intakeIn;

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    drive::turn(50_deg);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{9.5_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();

    drive::turn(0_deg);

    drive::chassisController.moveDistance(40_in);

    removePaths("D");
}

/*-------------------------------------------------------------------*/

void executeBlueFar2()
{
    odometry::currX = 130.75_in;
    odometry::currY = 32.5_in;
    odometry::resetAngle(270_deg);

    macroActTask->suspend();

    drive::profileController.generatePath(
        {Point{odometry::currY, odometry::currX, -odometry::currAngle}, Point{32.5_in, 88.75_in, 270_deg}}, "A1");

    drive::profileController.setTarget("A1");
    differential::currState = differential::intakeIn;
    drive::profileController.waitUntilSettled();

    drive::turn(10_deg);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{6_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D", true);
    drive::profileController.waitUntilSettled();

    differential::liftTarget = 200;
    differential::currState = differential::targetTransition;
    pros::delay(300);

    drive::turn(357_deg);

    pros::delay(3000);
    macroActTask->resume();
    // Resume the macro task

    customShotCall(75, 140);
    // Performs double shot

    pros::delay(2000);
    // Wait for the two shots to complete

    differential::currState = differential::intakeIn;

    macroActTask->suspend();
    // Pause macro task to regain control of differential

    drive::turn(50_deg);

    drive::profileController.generatePath(
        {Point{0_in, 0_in, 0_deg}, Point{9.5_in, 0_in, 0_deg}}, "D");

    drive::profileController.setTarget("D");
    drive::profileController.waitUntilSettled();

    drive::turn(0_deg);

    drive::chassisController.moveDistance(40_in);

    removePaths("D");
}