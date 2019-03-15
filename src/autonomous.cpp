#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
    pros::Task odometryPrint(odometry::printPosition, nullptr, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Position Print --> Screen");

    drive::currState = drive::driveStates::yield;
    differential::currState = differential::differentialStates::yield;
    puncher::currState = puncher::puncherStates::yield;
    angler::currState = angler::anglerStates::yield;

    drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::brake);

    switch (autonRoutine) // Executes specific routine based on auton selector.
    {
    case notSelected:
        break;
    case progSkills:
        executeProgSkills();
        break;

    case redNear1:
        executeRedNear1();
        break;

    case redNear2:
        executeRedNear2();
        break;

    case redFar1:
        executeRedFar1();
        break;

    case redFar2:
        executeRedFar2();
        break;

    case blueNear1:
        executeBlueNear1();
        break;

    case blueNear2:
        executeBlueNear2();
        break;

    case blueFar1:
        executeBlueFar1();
        break;

    case blueFar2:
        executeBlueFar2();
        break;
    }

    // odometry::init();
    // odometry::resetAngle(90_deg);
    // odometry::currX = 0_in;
    // odometry::currY = 0_in;

    // pros::delay(500);

    // path::Bezier A1(
    //     {path::Point{0_in, 0_in},
    //      path::Point{60_in, 0_in},
    //      path::Point{0_in, 60_in},
    //      path::Point{60_in, 60_in}},
    //     1000,
    //     200);

    // // path::Line A1(
    // //     {0_in, 0_in},
    // //     {0_in, 50_in},
    // //     1000,
    // //     1000);

    // drive::appc.runPath(&A1);

    // pros::delay(1000); // NOTE I shortened the delay from 4k to 1k

    // path::Bezier A2(
    //     {path::Point{odometry::currX, odometry::currY},
    //      path::Point{0_in, odometry::currY},
    //      path::Point{odometry::currX, 0_in},
    //      path::Point{0_in, 0_in}},
    //     1000,
    //     200);

    // // path::Line A2(
    // //     {0_in, 50_in},
    // //     {0_in, 0_in},
    // //     1000,
    // //     1000);

    // drive::appc.runPath(&A2);

    // pros::delay(500);

    // drive::turn(0_deg);

    // // // Drive forward into the cap #1 and intake ball

    // executeProgSkills();
    // executeRedNear1();
    // executeRedFar1();
    // executeRedFar2();
    // executeBlueFar1();
    // executeBlueFar2();
    // executeBlueNear1();

    odometry::init();
    odometry::resetAngle(90_deg);
    odometry::currX = 13.25_in;
    odometry::currY = 36_in;

    pros::delay(500);

    path::Line A1(
        {odometry::currX, odometry::currY},
        {53.25_in, 36_in},
        1000,
        1000);
    drive::appc.runPath(&A1);
    // Drive forward into the cap #1 and intake ball

    path::Bezier A2(
        {path::Point{odometry::currX, odometry::currY},
         path::Point{40_in, 36_in},
         path::Point{20_in, 12.5_in},
         path::Point{50_in, 12.5_in}},
        1000,
        250);

    drive::appc.runPathAsync(&A2);

    pros::delay(500);

    differential::liftTarget = 10;
    differential::currState = differential::targetTransition;

    drive::appc.waitUntilSettled();

    differential::liftTarget = 500;
    differential::currState = differential::targetTransition;

    pros::delay(1000);

    path::Bezier A3(
        {path::Point{odometry::currX, odometry::currY},
         path::Point{20_in, 12.5_in},
         path::Point{48_in, 24_in},
         path::Point{10_in, 24_in}},
        1000,
        200);

    drive::appc.runPathAsync(&A3);

    pros::delay(1000);

    differential::liftTarget = 900;
    differential::currState = differential::targetTransition;

    // drive::turn(3600_deg, 100, false, false);
    // lv_obj_clean(lv_scr_act());
}
