#include "main.h"

// controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// drive motors
pros::Motor lF(-20, pros::E_MOTOR_GEARSET_06); // left front motor. port 11, reversed
pros::Motor lT(9, pros::E_MOTOR_GEARSET_06); // left top motor. port 12
pros::Motor lB(-10, pros::E_MOTOR_GEARSET_06); // left bottom motor. port 13, reversed
pros::Motor rF(11, pros::E_MOTOR_GEARSET_06); // right front motor. port 1
pros::Motor rT(-2, pros::E_MOTOR_GEARSET_06); // right top motor. port 2, reversed
pros::Motor rB(1, pros::E_MOTOR_GEARSET_06); // right bottom motor. port 3

// flywheel motor
pros::Motor flywheel(-21, pros::E_MOTOR_GEARSET_06); // flywheel motor. port 17

// intake motors
pros::Motor intakeL(19, pros::E_MOTOR_GEARSET_18);
pros::Motor intakeR(-12, pros::E_MOTOR_GEARSET_18);

// motor groups
pros::MotorGroup leftDrive({lF, lT, lB}); // left motor group
pros::MotorGroup rightDrive({rF, rT, rB}); // right motor group

pros::MotorGroup intake({intakeL, intakeR});

// Inertial Sensor on port 11
pros::Imu imu(3);

pros::ADIDigitalOut rightWing('B');
pros::ADIDigitalOut leftWing('A');

// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-20, 9, -10}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{11, -2, 1}

  // IMU Port
  ,3

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,2.75

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.333


  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  intakeL.set_voltage_limit(5500);
  intakeR.set_voltage_limit(5500);

  intakeL.set_zero_position(pros::c::motor_get_position(20));

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  //lift_up_constants();
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("skills auton, shooting only", skills),
    //Auton("Example Turn\n\nTurn 3 times.", turn_example),
    /*
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
    */
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



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
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

/*
 * 0 // Hold for movement
 * 1 // Toggle on forwards
 * -1 // Toggle on reverse
*/

int flyToggle = 0;
double fPrevTime = -40000;
double fTime = 0;

int intakeToggle = 0;
double iPrevTime = -40000;
double iTime = 0;
/**
 * Runs in driver control
 */
void opcontrol() {
    chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
    flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    intakeL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    intakeR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    double ivanSens = 0.6;
    double vincentSens = 0.7;
    double devSens = 0.75;

    double driverSens = devSens;

    // controller
    // loop to continuously update motors
    while (true) {
        //pros::lcd::print(3, "Motor: %f", pros::c::motor_get_position(20));

        // get joystick positions
        chassis.arcade_standard(ez::SPLIT); // Standard split arcade

        //Macro Code//////////////////////////////////////////////////////////////
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
            fPrevTime = fTime;
            fTime = pros::millis();
            if(fTime - fPrevTime < 400){
                flyToggle = 1;
            }
            else{
                flyToggle = 0;
            }
        }  
        if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
            iPrevTime = iTime;
            iTime = pros::millis();
            if(iTime - iPrevTime < 400){
                intakeToggle = 1;
            }
            else{
                intakeToggle = 0;
            }
        }
///////////////////////////////////////////////////////////////////////////////////

        if(flyToggle == 0) {
            if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
                flywheel = -120;
            }
            else {
                flywheel = 0;
            }
        }
        else if(flyToggle == 1) {
            flywheel = 110;
        }
        else {
            return;
        }

        if(intakeToggle == 0) {
            if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
                if(pros::c::motor_get_position(19) < 350 && pros::c::motor_get_position(19) > 250){
                  intake = 10;
                  intake.set_brake_modes(MOTOR_BRAKE_HOLD);
                }
                else {
                  intake = 120;
                }
            }
            else {
              if(pros::c::motor_get_position(19) < 100) {
                intake.set_brake_modes(MOTOR_BRAKE_BRAKE);
                intake = 0;
                intake.set_brake_modes(MOTOR_BRAKE_COAST);
              }
              else {
                intake = -pros::c::motor_get_position(19)/7;
              }
            }
        }
        else if(intakeToggle == 1) {
            if(pros::c::motor_get_position(19) > 550) {
              intake = 20;
            }
            else if(pros::c::motor_get_position(19) > 650) {
              intake = 0;
              intake.set_brake_modes(MOTOR_BRAKE_HOLD);
            }
            else {
              intake = 120;
            }
        }
        else {
            return;
        }

    //WINGS
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
      leftWing.set_value(1);
    }
    else{
      leftWing.set_value(0);
    }
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
      rightWing.set_value(1);
    }
    else{
      rightWing.set_value(0);
    }

        // delay to save resources
        pros::delay(ez::util::DELAY_TIME);
    }
}