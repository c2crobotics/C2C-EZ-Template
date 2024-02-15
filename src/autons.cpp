#include "main.h"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 120; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 115;
const int SWING_SPEED = 115;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 9, 0, 20, 0); //d 20
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.6, 0, 3, 0); //0.7, 2.5 safety
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.8, 0, 5, 0); //d 5
  chassis.set_pid_constants(&chassis.turnPID, 4, 5, 30, 0);
  chassis.set_pid_constants(&chassis.swingPID, 5, 0, 45, 0);
}

void lift_up_constants() {
  chassis.set_slew_min_power(70, 55);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 0, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0, 2, 7.5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0, 2, 7.5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 0, 0, 40, 0);
  chassis.set_pid_constants(&chassis.swingPID, 0, 0, 45, 0);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 10, 1, 50, 3, 10, 10);
  chassis.set_exit_condition(chassis.swing_exit, 10, 1, 50, 3, 10, 10);
  chassis.set_exit_condition(chassis.drive_exit, 10, 50, 50, 150, 10, 10);
}

void test() {
  intake = 60;
  pros::delay(500);
  intake = 10;
  chassis.set_drive_pid(-5, DRIVE_SPEED);
  chassis.wait_drive();
  intake = -127;
  pros::delay(200);
  intake = 0;
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
}

void backDrivePush() {
  chassis.set_drive_pid(-40, DRIVE_SPEED);
  chassis.wait_drive();
}

//6 ball goal side
void suicide_score() {
  chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  intake.set_brake_modes(MOTOR_BRAKE_HOLD);
  flywheel.set_brake_mode(MOTOR_BRAKE_COAST);

  chassis.set_angle(-11.31);

  intake = -13;
  chassis.set_drive_pid(48, DRIVE_SPEED);
  chassis.wait_drive();
  
  pros::delay(10);
  intake = 127;

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-77, TURN_SPEED);
  chassis.wait_drive();

  intake = -127;
  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();
  
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  intake = 0;

  leftWing.set_value(1);
  rightWing.set_value(1);
  intake = 127;
  chassis.set_drive_pid(36, DRIVE_SPEED);
  chassis.wait_drive();
  leftWing.set_value(0);
  rightWing.set_value(0);
  intake = 0;
  
  chassis.set_swing_pid(ez::LEFT_SWING, -93, SWING_SPEED);
  chassis.wait_drive();

  intake = -25;
  chassis.set_drive_pid(23, DRIVE_SPEED);
  chassis.wait_drive();
  intake = 0;

  chassis.set_swing_pid(ez::RIGHT_SWING, -60, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-52, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(15, TURN_SPEED);
  chassis.wait_drive();
  intake = 127;

  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();
  intake = 0;

  chassis.set_swing_pid(ez::RIGHT_SWING, 50, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(230, TURN_SPEED);
  chassis.wait_drive();

  intake = -18;
  chassis.set_drive_pid(38, DRIVE_SPEED);
  chassis.wait_drive();

  intake = 0;
  chassis.set_turn_pid(50, TURN_SPEED);
  chassis.wait_drive();

  intake = 40;
  chassis.set_drive_pid(38, DRIVE_SPEED);
  chassis.wait_drive();

  intake = 127;
  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED);
  chassis.wait_drive();
}

void moderate_score() {
  // chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  // lift.set_brake_modes(MOTOR_BRAKE_HOLD);
  // flywheel.set_brake_modes(MOTOR_BRAKE_COAST);

  // chassis.set_angle(-30);

  // flywheel = -100;

  // chassis.set_drive_pid(55, 127);
  // chassis.wait_drive();

  // chassis.set_swing_pid(ez::RIGHT_SWING, -90, SWING_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-30, DRIVE_SPEED);
  // chassis.wait_drive();

  // chassis.set_swing_pid(ez::RIGHT_SWING, -125, SWING_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(32, DRIVE_SPEED);
  // chassis.wait_drive();
}

void safe_score(){
  chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  intake.set_brake_modes(MOTOR_BRAKE_HOLD);
  flywheel.set_brake_mode(MOTOR_BRAKE_COAST);

  intake = -127;
  chassis.set_drive_pid(4, 50);
  chassis.wait_drive();
  intake = 0;
  chassis.set_drive_pid(-38, 70);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, -45, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(-14, 70);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, -90, 80);
  chassis.wait_drive();
  chassis.set_drive_pid(-36, 125);
  chassis.wait_drive();
  intake = 70;
  pros::delay(300);
  intake = 5;
  chassis.set_drive_pid(-7, DRIVE_SPEED);
  chassis.wait_drive();
  intake = -127;
  pros::delay(200);
  intake = 0;
  chassis.set_turn_pid(-20, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(56, DRIVE_SPEED);
  pros::delay(300);
  intake = 127;
  pros::delay(500);
  intake = -127;
  chassis.wait_drive();
  chassis.set_turn_pid(150, TURN_SPEED);
  pros::delay(100);
  intake = 127;
  chassis.wait_drive();
  chassis.set_turn_pid(55, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(15, DRIVE_SPEED);
  chassis.wait_drive();
  intake = -127;
  chassis.set_swing_pid(ez::RIGHT_SWING, 30, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  leftWing.set_value(1);
  rightWing.set_value(1);
  intake = 127;
  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-20, DRIVE_SPEED);
  chassis.wait_drive();
}

void safe_denial() {
  chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  intake.set_brake_modes(MOTOR_BRAKE_HOLD);
  flywheel.set_brake_mode(MOTOR_BRAKE_COAST);

  intake = -127;
  pros::delay(1000);
  intake = 0;

  chassis.set_swing_pid(ez::RIGHT_SWING, -135, 40);
  chassis.wait_drive();

  chassis.set_drive_pid(5, 20);
  chassis.wait_drive();

  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -270, 80);
  chassis.wait_drive();

  intake = 80;
  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_drive();
  intake = -20;

  // chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  // lift.set_brake_modes(MOTOR_BRAKE_HOLD);
  // flywheel.set_brake_modes(MOTOR_BRAKE_COAST);

  // chassis.set_angle(45);

  // chassis.set_drive_pid(-6, 50);
  // chassis.wait_drive();

  // rightWing.set_value(1);
  // pros::delay(300);
  // rightWing.set_value(0);
  
  // chassis.set_drive_pid(-4, 50);
  // chassis.wait_drive();

  // chassis.set_swing_pid(ez::RIGHT_SWING, 90, SWING_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-12, 127);
  // chassis.wait_drive();

  // flywheel = -90;

  // chassis.set_swing_pid(ez::RIGHT_SWING, -70, SWING_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(42, DRIVE_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-10, DRIVE_SPEED);
  // chassis.wait_drive();

  // chassis.set_swing_pid(ez::LEFT_SWING, 135, SWING_SPEED);
  // chassis.wait_drive();
}

void moderate_denial() {
  // chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  // lift.set_brake_modes(MOTOR_BRAKE_HOLD);
  // flywheel.set_brake_modes(MOTOR_BRAKE_COAST);

  // flywheel = -127;
  // chassis.set_drive_pid(48, 127);
  // chassis.wait_drive();
  
  // chassis.set_drive_pid(-27, DRIVE_SPEED);
  // chassis.wait_drive();

  // flywheel = 127;
  
  // chassis.set_drive_pid(-27, DRIVE_SPEED);
  // chassis.wait_drive();

  // flywheel = 0;

  // chassis.set_turn_pid(-97, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(10, DRIVE_SPEED);
  // chassis.wait_drive();

  // chassis.set_swing_pid(ez::LEFT_SWING, -52, SWING_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(14, DRIVE_SPEED);
  // chassis.wait_drive();

  // chassis.set_swing_pid(ez::LEFT_SWING, -8, SWING_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(5, DRIVE_SPEED);
  // chassis.wait_drive();

  // chassis.set_turn_pid(172, TURN_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(-7, DRIVE_SPEED);
}

void suicide_denial() {
  chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  intake.set_brake_modes(MOTOR_BRAKE_HOLD);
  flywheel.set_brake_mode(MOTOR_BRAKE_COAST);

  chassis.set_angle(11.31);

  intake = -13;
  leftWing.set_value(1);
  chassis.set_drive_pid(48, DRIVE_SPEED);
  pros::delay(160);
  leftWing.set_value(0);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 90, SWING_SPEED);
  chassis.wait_drive();

  leftWing.set_value(1);
  chassis.set_drive_pid(25, DRIVE_SPEED);
  chassis.wait_drive();

  flywheel = -127;
}

void skills() {
  chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
  intake.set_brake_modes(MOTOR_BRAKE_HOLD);
  flywheel.set_brake_mode(MOTOR_BRAKE_COAST);

  intake = -30;
  flywheel = 100;
  pros::delay(500);
  intake = 0;
  chassis.set_swing_pid(ez::LEFT_SWING, -25, 50);
  chassis.wait_drive();
  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(30000);
  /*chassis.set_drive_pid(-2, 40);
  chassis.wait_drive();
  chassis.set_drive_pid(2, DRIVE_SPEED);
  chassis.wait_drive();
  flywheel = 0;
  chassis.set_swing_pid(10, 50);
  chassis.wait_drive();
  chassis.set_drive_pid(3, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 0, 50);
  chassis.wait_drive();
  chassis.set_drive_pid(18, 40);
  chassis.wait_drive();
  */
  chassis.set_swing_pid(ez::LEFT_SWING, 20,80);
  flywheel = 0;
  chassis.wait_drive();
  chassis.set_drive_pid(14, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 0,50);
  chassis.wait_drive();
  chassis.set_drive_pid(62, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, -90, 120);
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, -135, 120);
  chassis.wait_drive();
  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();
  intake = 100;
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  leftWing.set_value(1);
  rightWing.set_value(1);
  chassis.wait_drive();
  chassis.set_drive_pid(33, DRIVE_SPEED);
  chassis.wait_drive();
  leftWing.set_value(0);
  rightWing.set_value(0);
  chassis.wait_drive();
  chassis.set_drive_pid(-24, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  /*
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(70, TURN_SPEED);
  leftWing.set_value(1);
  rightWing.set_value(1);
  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-20, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-24, DRIVE_SPEED);
}