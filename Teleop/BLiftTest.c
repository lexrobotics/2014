#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          a,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          b,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,          c,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     liftMotor2,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     pickupMotor,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     liftMotor1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    gateServo,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    pickupServo1,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_6,    pickupServo2,         tServoContinuousRotation)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

 /*
	* TeleOpTemplate.c
	* 2 Bits and a Byte [Team 4029]
	*
	* Last edited by: Noah Moroze, 5/28
	* Notes: I modified TeleOpBotside.c to create this general TeleOp program, which will serve as a learning template/reference for our programmers.
	*
	* CONFIGURATION
	* - 1: Motor Controller 1 - Servo Controller 1
	* 	- Motor Controller 1:
	*		- M1: Right side drive wheels (with encoder)
	*		- M2: Left side drive wheels (with encoder)
	*	- Servo Controller 1:
	*		- S1: Arm shoulder (standard)
	*		- S2: Arm pivot (continuous)
	* - 2: <item plugged into port 2>
	* - 3: <item plugged into port 3>
	* - 4: <item plugged into port 4>
	*
	* CONTROLS
	* - Controller 1:
	*	- Left and Right Sticks up/down: drive (tank style)
	*	- Holding down 1 + top hat: precision drive
	* - Controller 2:
	*	- Buttons 1/3: Pivot arm left/right
	* 	- Buttons 2/4: Bend arm up/down
*/

#include "JoystickDriver.c"  //library with joystick control methods


task main() {
	//variables for motor power that we can modify before feeding to motors
	int powerRight = 0;
	int powerLeft = 0;

	writeDebugStreamLine("");
	writeDebugStreamLine("TELEOP");

	// Initialize robot actuators
	writeDebugStreamLine("Initialized");

	// Wait for start of tele-op phase.
	waitForStart();
	writeDebugStreamLine("Begin!");

	ClearTimer(T1);

	while(true) {
		getJoystickSettings(joystick); //grab snapshot of controller positions

		if(joy1Btn(5)) {
			motor[liftMotor1] = 100;
		}
		else if(joy1Btn(7)) {
			motor[liftMotor1] = -100;
		}
		else
			motor[liftMotor1] = 0;

		if(joy1Btn(8)) {
			motor[liftMotor2] = 100;
		}
		else if(joy1Btn(6)) {
			motor[liftMotor2] = -100;
		}
		else
			motor[liftMotor2] = 0;

		if (joy1Btn(3))
		{
			motor[pickupMotor] = 100;
		}

		else if (joy1Btn(1))
		{
			motor[pickupMotor] = -100;
		}
		else{
			motor[pickupMotor] = 0;
	}

		if (joystick.joy1_TopHat == 0) {  // forward
			servo[pickupServo1] = 0;
			servo[pickupServo2] = 255;
		}
		else if (joystick.joy1_TopHat == 4) { // backward
			servo[pickupServo1] = 255;
			servo[pickupServo2] = 0;
		}
		else {
			servo[pickupServo1] = 127;
			servo[pickupServo2] = 127;
		}

		if(joy1Btn(9)){
			servo[gateServo] += 1;
			wait1Msec(4);
		}
		else if(joy1Btn(10)){
			servo[gateServo] -= 1;
			wait1Msec(4);
		}


	}
}
