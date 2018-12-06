#pragma once
#include "okapi/api.hpp"

extern okapi::Motor puncher;
extern okapi::Motor angleChanger;
extern okapi::AsyncPosIntegratedController angleController;
extern double angleTarget;
extern char getPuncherState();
extern char getAngleState();
extern void updatePuncher();
extern void puncherAct();
extern void abortPuncher();
