#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;
extern pros::Motor_Group intake;
extern pros::ADIDigitalOut rightWing;
extern pros::ADIDigitalOut leftWing;
extern pros::ADIDigitalOut backLeftWing;
extern pros::ADIDigitalOut backRightWing;
extern pros::ADIDigitalOut kickstand;
extern pros::ADIDigitalOut climb;
extern pros::ADIDigitalOut kickstandExt;


/*
void auton_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void combining_movements();
void interfered_example();
*/

void test();
void SafeScore();
void SuicideDenial();
void SafeDenial();
void SuicideDenial();
void SuicideScore();

void suicide_constants();
void default_constants();
void lift_up_constants();