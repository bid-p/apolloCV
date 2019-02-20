#include "main.h"

using namespace okapi;

ControllerButton liftUpBtn = controller[ControllerDigital::A];
ControllerButton liftDownBtn = controller[ControllerDigital::Y];
ControllerButton intakeInBtn = controller[ControllerDigital::R1];
ControllerButton intakeOutBtn = controller[ControllerDigital::R2];

ControllerButton liftHoldBtn = controller[ControllerDigital::B];

namespace differential
{
differentialStates currState;

Motor diffLeft(DIFF_L, true, AbstractMotor::gearset::green);
Motor diffRight(DIFF_R, false, AbstractMotor::gearset::green);

Timer ballBrakeTimer;
pros::ADILineSensor line(SPORT_INTAKE);

Potentiometer liftPot(SPORT_LIFT);
AverageFilter<5> liftPotFilter;

int liftVal;

int liftTarget;

bool hasBall()
{
    if (line.get_value() < 2400)
    {
        return true;
    }
    return false;
}

void update()
{
    liftVal = liftPotFilter.filter(liftPot.get());

    // Automatic state checkers
    if (currState == intakeIn && !puncher::isLoaded() && hasBall())
    {
        currState = ballDecel;
    }
    if (currState == ballDecel && puncher::isLoaded())
    {
        currState = intakeIn;
    }
    if (currState == intakeIn && puncher::isLoaded() && hasBall())
    {
        currState = ballBrake;
        ballBrakeTimer.getDt();
    }
    if (currState == ballBrake && ballBrakeTimer.readDt() >= 22_ms)
    {
        currState = notRunning;
    }
    if (currState == targetTransition && (liftVal >= (liftTarget - 20) && liftVal <= (liftTarget + 20)))
    {
        currState = liftHold;
    }

    // User input handlers
    if (liftUpBtn.isPressed() && !liftDownBtn.isPressed())
    {
        currState = liftUp;
    }
    if (liftDownBtn.isPressed() && !liftUpBtn.isPressed())
    {
        currState = liftDown;
    }
    if (currState == notRunning && intakeInBtn.changedToPressed() && !intakeOutBtn.isPressed())
    {
        currState = intakeIn;
    }
    if (intakeOutBtn.isPressed() && !intakeInBtn.isPressed())
    {
        currState = intakeOut;
    }
    if (liftHoldBtn.changedToPressed() && !intakeInBtn.isPressed())
    {
        // Engage lift PID if B button is pressed.
        liftTarget = 250;
        currState = targetTransition;
    }
}

void act(void *)
{
    while (true)
    {
        switch (currState)
        {
        case notRunning:
            diffLeft.setBrakeMode(AbstractMotor::brakeMode::coast);
            diffRight.setBrakeMode(AbstractMotor::brakeMode::coast);
            diffLeft.moveVoltage(0);
            diffRight.moveVoltage(0);
            break;
        case liftUp:
            // Run motors in same direction.
            diffLeft.moveVelocity(-200);
            diffRight.moveVelocity(-200);
            currState = liftHold;
            break;
        case liftDown:
            diffLeft.moveVelocity(200);
            diffRight.moveVelocity(200);
            currState = notRunning;
            break;
        case intakeIn:
            diffLeft.moveVoltage(-12000);
            diffRight.moveVoltage(12000);
            break;
        case intakeOut:
            // Move motors at 83.3% power.
            diffLeft.moveVoltage(10000);
            diffRight.moveVoltage(-10000);
            currState = notRunning;
            break;
        case liftHold:
            // Engage PID for lift.
            diffLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
            diffRight.setBrakeMode(AbstractMotor::brakeMode::hold);
            diffLeft.moveVelocity(0);
            diffRight.moveVelocity(0);
            break;
        case ballBrake:
            // Outtake without yielding control to notRunning state.
            diffLeft.moveVoltage(10000);
            diffRight.moveVoltage(-10000);
            break;
        case ballDecel:
            // Run intake at 83.3% of normal speed to prevent ball
            // from flying out.
            diffLeft.moveVoltage(-5500);
            diffRight.moveVoltage(5500);
            break;
        case intakeOutNY:
            // Keep outtaking to flip caps. For use in auton.
            diffLeft.moveVoltage(10000);
            diffRight.moveVoltage(-10000);
            break;
        case targetTransition:
            if (liftVal <= liftTarget)
            {
                diffLeft.moveVoltage(-10000);
                diffRight.moveVoltage(-10000);
            }
            if (liftVal >= liftTarget)
            {
                diffLeft.moveVoltage(10000);
                diffRight.moveVoltage(10000);
            }
            break;
        case yield:
            break;
        }

        pros::delay(10);
    }
}

} // namespace differential

void runIntake(int speed)
{
    differential::diffLeft.moveVelocity(-1 * speed);
    differential::diffRight.moveVelocity(1 * speed);
}