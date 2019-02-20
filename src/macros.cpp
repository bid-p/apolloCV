#include "main.h"

using namespace okapi;

ControllerButton angleCloseHigh = controller[ControllerDigital::down];
ControllerButton angleCloseMidBtn = controller[ControllerDigital::up];
ControllerButton angleFarMidBtn = controller[ControllerDigital::left];
ControllerButton angleFarHighBtn = controller[ControllerDigital::right];

ControllerButton singleShotBtn = controller[ControllerDigital::L1];
ControllerButton doubleShotNearBtn = controller[ControllerDigital::L2];
ControllerButton doubleShotFarBtn = controller[ControllerDigital::X];

ControllerButton gayButton = controller[ControllerDigital::B];
ControllerButton shiftBtn = controller[ControllerDigital::R1];

int macroTarget1; // target encoder values for angler to shoot first flag in macro
int macroTarget2; // target encoder value for angler to shoot second flag in macro

namespace macro
{

macroStates currState = none;

void update()
{
    if (angleCloseHigh.changedToPressed())
    {
        currState = anglerNearHigh;
    }
    if (angleCloseMidBtn.changedToPressed())
    {
        currState = anglerNearMid;
    }
    if (angleFarMidBtn.changedToPressed())
    {
        currState = anglerFarMid;
    }
    if (angleFarHighBtn.changedToPressed())
    {
        currState = anglerFarHigh;
    }
    if (singleShotBtn.changedToPressed())
    {
        currState = singleShot;
    }
    if (doubleShotNearBtn.changedToPressed())
    {
        customShotCall(0, 90);
    }
    if (doubleShotFarBtn.changedToPressed())
    {
        customShotCall(35, 90);
    }
    if (!shiftBtn.changedToPressed() && shiftBtn.isPressed() && gayButton.changedToPressed())
    {
        currState = scorePole;
    }
    // printf("Macro State: %c\n", currState);
}

void act(void *)
{
    while (true)
    {
        switch (currState)
        {
        case none: // macro is not activated
            break;
        case singleShot: // shoots a single flag with a single given target encoder value for that flag; for autonomous
            drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::brake);

            puncher::currState = puncher::cocking;
            // switches out of cocking when sensor value achieved

            // differential::currState = differential::intakeIn;
            // while (!puncher::isLoaded())
            // {
            //   pros::delay(2);
            // } // waits for puncher to load
            // differential::currState = differential::notRunning;

            // waitUntilSettled(angler::angler, 2, 5, 10_ms); // waits until angler to stop
            printf("Ang. PreShot: %i\n", (int)angler::angler.getPosition());
            puncher::currState = puncher::shooting;

            drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);

            macro::currState = none;
            break;
        case customShotDouble: // shoots two flags with the specified target encoder values for those flags; for autonomous
            drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::brake);

            puncher::currState = puncher::cocking;
            // switches out of cocking when sensor value achieved

            angler::target = macroTarget1;
            angler::currState = angler::toTarget;
            // will switch out of toTarget automatically when target reached

            // should automatically stop when ball loads into puncher

            differential::currState = differential::intakeIn;
            while (!puncher::isLoaded())
            {
                pros::delay(2);
            } // waits for puncher to load
            differential::currState = differential::notRunning;

            waitUntilSettled(angler::angler, 5, 5, 20_ms); // waits until angler to stop

            printf("Ang. PreShot 1: %i\n", (int)angler::angler.getPosition());
            puncher::currState = puncher::shooting;

            while (puncher::currState != puncher::cocking)
            {
                pros::delay(2);
            }

            angler::target = macroTarget2;
            angler::currState = angler::toTarget;

            differential::currState = differential::intakeIn;
            while (!puncher::isLoaded())
            {
                pros::delay(2);
            } // waits for puncher to load
            differential::currState = differential::notRunning;

            waitUntilSettled(angler::angler, 5, 5, 20_ms); // waits until angler to stop

            printf("Ang. PreShot 2: %i\n", (int)angler::angler.getPosition());
            puncher::currState = puncher::shooting;

            drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);

            macro::currState = none;
            break;
        case doubleShotNoWait:
            drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::brake);

            puncher::currState = puncher::cocking;
            // switches out of cocking when sensor value achieved

            angler::target = macroTarget1;
            angler::currState = angler::toTarget;
            // will switch out of toTarget automatically when target reached

            // should automatically stop when ball loads into puncher

            differential::currState = differential::intakeIn;
            // while (!puncher::isLoaded())
            // {
            //   pros::delay(2);
            // } // waits for puncher to load

            pros::delay(100);
            if (!puncher::isLoaded())
            {
                drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);
                macro::currState = none;
                break; // if puncher not loaded do not shoot again
            }

            differential::currState = differential::notRunning;

            waitUntilSettled(angler::angler, 5, 5, 20_ms); // waits until angler to stop

            puncher::currState = puncher::shooting;

            while (puncher::currState != puncher::cocking)
            {
                pros::delay(2);
            }

            angler::target = macroTarget2;
            angler::currState = angler::toTarget;

            differential::currState = differential::intakeIn;
            pros::delay(1000); // doesn't wait for ball to be loaded, because it may or may not be there
            if (!puncher::isLoaded())
            {
                drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);
                macro::currState = none;
                break; // if puncher not loaded do not shoot again
            }
            differential::currState = differential::notRunning;

            waitUntilSettled(angler::angler, 5, 5, 20_ms); // waits until angler to stop

            puncher::currState = puncher::shooting;

            drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);

            macro::currState = none;
            break;
        case anglerNearHigh: // changes the angler to target the high flag from the close tile
            angler::target = 0;
            angler::currState = angler::toTarget;
            macro::currState = none;
            break;
        case anglerNearMid: // changes the angler to target the high flag from the middle tile
            angler::target = 90;
            angler::currState = angler::toTarget;
            macro::currState = none;
            break;
        case anglerFarMid: // changes the angler to target the middle flag from the far tile
            angler::target = 88;
            angler::currState = angler::toTarget;
            macro::currState = none;
            break;
        case anglerFarHigh: // Changes the angler to target the high flag from the far title
            angler::target = 35;
            angler::currState = angler::toTarget;
            macro::currState = none;
            break;
        case scorePole:
            drive::currState = drive::yield;
            drive::chassisController.setMaxVelocity(100);
            drive::chassisController.moveDistance(-7.5_in);
            differential::liftTarget = 3000;
            drive::chassisController.waitUntilSettled();
            drive::chassisController.setMaxVelocity(200);
            differential::currState = differential::targetTransition;
            currState = none;
            break;
        }
        pros::delay(10);
    }
}

} // namespace macro

// Double shot
void customShotCall(int target1, int target2, bool noWait)
{
    macroTarget1 = target1;
    macroTarget2 = target2;

    if (noWait)
    {
        macro::currState = macro::macroStates::doubleShotNoWait;
    }
    else
    {
        macro::currState = macro::macroStates::customShotDouble;
    }
}

// Single shot
void customShotCall(int target1)
{
    macroTarget1 = target1;

    macro::currState = macro::macroStates::singleShot;
}