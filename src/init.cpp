#include "main.h"

Controller controller;

const double joyDeadband = .08;

alliances alliance;

// Constructs and starts acting tasks for subsystems
pros::Task driveActTask(drive::act, NULL, TASK_PRIORITY_DEFAULT,
                        TASK_STACK_DEPTH_DEFAULT, "Act Drive");

pros::Task puncherActTask(puncher::act, NULL, TASK_PRIORITY_DEFAULT,
                          TASK_STACK_DEPTH_DEFAULT, "Act Puncher");

pros::Task anglerActTask(angler::act, NULL, TASK_PRIORITY_DEFAULT,
                         TASK_STACK_DEPTH_DEFAULT, "Act Angler");

pros::Task differentialActTask(differential::act, NULL, TASK_PRIORITY_DEFAULT,
                               TASK_STACK_DEPTH_DEFAULT, "Act Diff");

pros::Task macroActTask(macro::act, NULL, TASK_PRIORITY_DEFAULT,
                        TASK_STACK_DEPTH_DEFAULT, "Act Macro");

pros::Task updateTask(updateFunc, NULL, TASK_PRIORITY_DEFAULT,
                      TASK_STACK_DEPTH_DEFAULT, "Update");

void waitUntilSettled(okapi::AbstractMotor &motor, double iatTargetError = 50, double iatTargetDerivative = 5, QTime iatTargetTime = 250_ms)
{
  auto settledUtil = SettledUtilFactory::create(iatTargetError, iatTargetDerivative, iatTargetTime);

  while (!settledUtil.isSettled(motor.getTargetPosition() - motor.getPosition()))
  {
    pros::delay(10);
  }
} // Custom waiting util that checks for when an integrated PID
// controller has settled

void updateFunc(void *)
{
  while (true)
  {
    drive::update();
    angler::update();
    puncher::update();
    differential::update();
    macro::update();

    pros::delay(5);
  }
} // Task used to update subsystem state machines

extern void states();

extern void autonStates();