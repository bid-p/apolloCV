#include "main.h"

using namespace okapi;

ControllerButton anglerNearHighBtn = controller[ControllerDigital::down];
ControllerButton anglerNearMidBtn = controller[ControllerDigital::up];
ControllerButton anglerFarMidBtn = controller[ControllerDigital::left];
ControllerButton anglerFarHighBtn = controller[ControllerDigital::right];

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
    if (anglerNearHighBtn.changedToPressed())
    {
        if (currState == '1')
        {
            currState = none;
        }
        else
        {
            currState = anglerNearHigh;
        }
    }
    if (anglerNearMidBtn.changedToPressed())
    {
        if (currState == '2')
        {
            currState = none;
        }
        else
        {
            currState = anglerNearMid;
        }
    }
    if (anglerFarMidBtn.changedToPressed())
    {
        if (currState == '3')
        {
            currState = none;
        }
        else
        {
            currState = anglerFarMid;
        }
    }
    if (anglerFarHighBtn.changedToPressed())
    {
        if (currState == '4')
        {
            currState = none;
        }
        else
        {
            currState = anglerFarHigh;
        }
    }
    if (singleShotBtn.changedToPressed())
    {
        if (currState == 's')
        {
            currState = none;
        }
        else
        {
            currState = singleShot;
            angler::vision.set_led(COLOR_CYAN);
            pros::delay(30);
        }
    }
    if (doubleShotNearBtn.changedToPressed())
    {
        if (currState == 'c')
        {
            currState = none;
        }
        else
        {
            customShotCall(0, 90);
            angler::vision.set_led(COLOR_CYAN);
            pros::delay(30);
        }
    }
    if (doubleShotFarBtn.changedToPressed())
    {
        if (currState == 'c')
        {
            currState = none;
        }
        else
        {
            customShotCall(40, 108);
            angler::vision.set_led(COLOR_CYAN);
            pros::delay(30);
        }
    }
    if (!shiftBtn.changedToPressed() && shiftBtn.isPressed() && gayButton.changedToPressed())
    {
        if (currState == 'p')
        {
            currState = none;
        }
        else
        {
            currState = scorePole;
            angler::vision.set_led(COLOR_CYAN);
            pros::delay(30);
        }
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
            drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::hold);

            angler::vision.set_led(COLOR_LIGHT_BLUE);

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

            angler::vision.set_led(COLOR_ANTIQUE_WHITE);

            macro::currState = none;
            break;
        case customShotDouble: // shoots two flags with the specified target encoder values for those flags; for autonomous
            drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::hold);

            angler::vision.set_led(COLOR_LIGHT_BLUE);

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

            angler::vision.set_led(COLOR_RED);

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

            angler::vision.set_led(COLOR_ANTIQUE_WHITE);
            macro::currState = none;
            break;
        case doubleShotNoWait:
            drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::hold);

            angler::vision.set_led(COLOR_LIGHT_BLUE);

            puncher::currState = puncher::cocking;
            // switches out of cocking when sensor value achieved

            angler::target = macroTarget1;
            angler::currState = angler::toTarget;
            // will switch out of toTarget automatically when target reached

            // should automatically stop when ball loads into puncher

            // while (!puncher::isLoaded())
            // {
            //   pros::delay(2);
            // } // waits for puncher to load

            if (!puncher::isLoaded())
            {
                differential::currState = differential::intakeIn;
                pros::delay(400);
            }

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
                angler::vision.set_led(COLOR_ANTIQUE_WHITE);
                break; // if puncher not loaded do not shoot again
            }
            angler::vision.set_led(COLOR_RED);

            differential::currState = differential::notRunning;

            waitUntilSettled(angler::angler, 5, 5, 20_ms); // waits until angler to stop

            puncher::currState = puncher::shooting;

            drive::chassisController.setBrakeMode(AbstractMotor::brakeMode::coast);

            angler::vision.set_led(COLOR_ANTIQUE_WHITE);

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