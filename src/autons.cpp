#include "main.h"
using namespace pros;
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
  chassis.set_pid_constants(&chassis.headingPID, 8.9, 0, 20 , 0); //d 20
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.5365, 0, 3, 0); //0.7, 2.5 safety
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.665, 0, 5, 0); //d 5
  chassis.set_pid_constants(&chassis.turnPID, 3, 5, 30, 0);
  chassis.set_pid_constants(&chassis.swingPID, 3.92, 0, 45, 0);
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
  chassis.set_exit_condition(chassis.turn_exit, 10, 0.5, 50, 1.5, 10, 10);
  chassis.set_exit_condition(chassis.swing_exit, 10, 0.5, 50, 1.5, 10, 10);
  chassis.set_exit_condition(chassis.drive_exit, 10, 50, 50, 150, 10, 10);
}


void test(){
  intake = 127;
  kickstandExt.set_value(1);
  chassis.set_drive_pid(100, 125, false, false);
}

void SafeScore(){
  //3 ball back push, intake triball under bar, descore corner, push preload + two balls into goal
  //Setup: Same set up, roughly middle of tile, measure intake movement radius such that when it drops it will miss the bar, triball in corner of matchload zone, preload back center of bot
  intake = 127;
  pros::delay(500);
  chassis.set_drive_pid(3, 90, false, false);
  chassis.wait_drive();
  chassis.set_drive_pid(-34, 125, false, false);
  chassis.wait_drive();
  //Drop intake, drive forward to intake, drive backwards towards corner bar, stop just short
  chassis.set_turn_pid(-35, 100);
  chassis.wait_drive();
  backLeftWing.set_value(1);
  chassis.set_drive_pid(-18, 60, false, false);
  chassis.wait_drive();
  chassis.set_turn_pid(-95, 125);
  //pros::delay(300);
  backLeftWing.set_value(0);
  backRightWing.set_value(1);
  chassis.wait_drive();
  //Turn front of robot to -35 degrees, open back left wing, move back 18 and turn to -95 degrees to descore, immediatly shut back left wing, open back right wing
  chassis.set_turn_pid(-60,125);
  chassis.wait_drive();
  chassis.set_drive_pid(-22, 80, false, false);
  chassis.wait_drive();
  backLeftWing.set_value(0);
  chassis.set_drive_pid(12, 125, false, false);
  chassis.wait_drive();
  //Turn to -60 degrees, back into goal, move out of goal
  chassis.set_turn_pid(-260, 90);
  chassis.wait_drive();
  intake = -127;
  pros::delay(500);
  chassis.set_drive_pid(24, 125, false, false);
  chassis.wait_drive();
  chassis.set_drive_pid(-12, 125, false, false);
  chassis.wait_drive();
  chassis.set_turn_pid(-267, 125);
  backRightWing.set_value(1);
  chassis.set_drive_pid(12, 125, false, false);
  //Turn front of robot to face goal, outake, drive forward once and push, drive back, reangle to -267, open back right wing, forward push
}

void SafeDenial(){
//Descore into bar touch
//Setup: parallel to matchload bar, front towards side field wall, triball in corner of matchload zone, wing mount at back 1/3 of the triball, preload in the divot between the wing with corner pointing at alley
leftWing.set_value(1);
//Open left wing to launch preload down alley
pros::delay(600);
backRightWing.set_value(1);
chassis.set_turn_pid(-70, 125);
chassis.wait_drive();
backRightWing.set_value(0);
//Open back right wing and turn to -70 degrees to descore triball, close back right wing
chassis.set_turn_pid(-22, 125);
chassis.wait_drive();
chassis.set_drive_pid(40, 125, false, false);
chassis.wait_drive();
//Turn to -22 degrees, drive 40 into the alley
intake = 127;
pros::delay(500);
intake = 0;
//Drop intake, stop intake
}