#include "main.h"

Controller controller;

const double joyDeadband = .08;

alliances alliance;

void initActTasks()
{
    // Constructs and starts tasks for subsystems
    driveActTask = new pros::Task(drive::act, NULL, TASK_PRIORITY_DEFAULT,
                                  TASK_STACK_DEPTH_DEFAULT, "Act Drive");

    puncherActTask = new pros::Task(puncher::act, NULL, TASK_PRIORITY_DEFAULT,
                                    TASK_STACK_DEPTH_DEFAULT, "Act Puncher");

    anglerActTask = new pros::Task(angler::act, NULL, TASK_PRIORITY_DEFAULT,
                                   TASK_STACK_DEPTH_DEFAULT, "Act Angler");

    differentialActTask = new pros::Task(differential::act, NULL, TASK_PRIORITY_DEFAULT,
                                         TASK_STACK_DEPTH_DEFAULT, "Act Diff");

    macroActTask = new pros::Task(macro::act, NULL, TASK_PRIORITY_DEFAULT,
                                  TASK_STACK_DEPTH_DEFAULT, "Act Macro");

    updateTask = new pros::Task(updateFunc, NULL, TASK_PRIORITY_DEFAULT,
                                TASK_STACK_DEPTH_DEFAULT, "Update");
}

void waitUntilSettled(okapi::AbstractMotor &motor, double iatTargetError = 50, double iatTargetDerivative = 5, QTime iatTargetTime = 250_ms)
{
    auto settledUtil = SettledUtilFactory::create(iatTargetError, iatTargetDerivative, iatTargetTime);

    while (!settledUtil.isSettled(motor.getTargetPosition() - motor.getPosition()))
    {
        pros::delay(10);
    }
}

void updateFunc(void *)
{
    while (true)
    {
        drive::update();
        macro::update();
        differential::update();
        puncher::update();
        angler::update();

        pros::delay(5);
    }
}

void states();

void autonStates();

bool looperoni = false;

void appcWUS()
{
    looperoni = true;
    while (!drive::appc.isSettled())
    {
        pros::delay(10);
    }
    // looperoni = false;
    drive::chassisController.stop();
}