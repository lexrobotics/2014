<<<<<<< HEAD
<<<<<<< HEAD
#pragma config(Hubs,  S1, HTServo,  HTMotor,  none,     none)
=======
#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
>>>>>>> 40cd4a40bc51df061e017ad3afac774ffbc458c8
=======
#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
>>>>>>> 40cd4a40bc51df061e017ad3afac774ffbc458c8
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          a,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          b,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,          c,             tmotorNXT, openLoop, encoder)
<<<<<<< HEAD
<<<<<<< HEAD
#pragma config(Motor,  mtr_S1_C2_1,     motorsRight,   tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     MotorsLeft,    tmotorTetrix, PIDControl, reversed, encoder)
=======
=======
>>>>>>> 40cd4a40bc51df061e017ad3afac774ffbc458c8
#pragma config(Motor,  mtr_S1_C2_1,     motorsRight,   tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorsLeft,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorHarvester, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, openLoop)
<<<<<<< HEAD
>>>>>>> 40cd4a40bc51df061e017ad3afac774ffbc458c8
=======
>>>>>>> 40cd4a40bc51df061e017ad3afac774ffbc458c8
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
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

//static speed of robot in precision mode rather than 100.
static int TOP_HAT_FWDBACK_SPEED = 20;
static int TOP_HAT_TURN_SPEED = 20;

static float MOTOR_SCALE = 200.0/256.0; //since joystick values range from -128 to 127 and motors from -100 to 100, we need to scale values from the joystick

void initializeRobot()
{
	//These 3 lines set up PID control for the drive motors (using encoders)
	nPidUpdateInterval = 8;
	nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg; //Copy this line (with motor name changed) for each motor you set up with an encoder
	nMotorPIDSpeedCtrl[motorB] = mtrSpeedReg;

	//define starting position for servos here
}

//This is the task where we define all servo/"arm" movements.
//By separating the arm and drive tasks, it lets us logically separate our code, and run each one in parallel.
//e.g. you can raise your arm while driving at the same time
task arm() {
	//define servo-position related variables here

	//Vacuum Cleaner/generic other
	while(true){
		getJoystickSettings(joystick); //grab snapshot of controller positions
<<<<<<< HEAD
<<<<<<< HEAD
		if(joy1Btn(5))
			motor[motorHarvester] = 100;
		else if(joy1Btn(6))
			motor[motorHarvester] = -100;
=======
		if(joy1Btn(6))//upper left button pressed, suck blocks in
			motor[motorHarvester] = 100;
=======
		if(joy1Btn(6))//upper left button pressed, suck blocks in
			motor[motorHarvester] = 100;
>>>>>>> 40cd4a40bc51df061e017ad3afac774ffbc458c8
		else if(joy1Btn(8))//lower left button, spit blocks out
			motor[motorHarvester] = -100;
		else //none
			motor[motorHarvester] = 0;

		if(joy1Btn(1))//1 button launch block
			motor[a] = 100;
		else if(joy1Btn(3))
			motor[a]=-100;
		else //none
			motor[a] = 0;

<<<<<<< HEAD
>>>>>>> 40cd4a40bc51df061e017ad3afac774ffbc458c8
=======
>>>>>>> 40cd4a40bc51df061e017ad3afac774ffbc458c8
	}


}

task main() {
	//to hold computed motor power
	int powerRight, powerLeft;

	writeDebugStreamLine("");
	writeDebugStreamLine("TELEOP");

	// Initialize robot actuators
	initializeRobot();
	writeDebugStreamLine("Initialized");

	// Wait for start of tele-op phase
	waitForStart();
	writeDebugStreamLine("Begin!");

	StartTask(arm); //Run block-harvesting-etc task in parallel
	ClearTimer(T1);

	while(true) {
		getJoystickSettings(joystick); //grab snapshot of controller positions

		powerLeft = powerRight = 0;//To reset.

		//Since joysticks rarely settle to zero, this makes sure each axis is reset to 0 even if it's within 10 from zero
		//Be sure to copy one of these statements for each joystick you use
		if(abs(joystick.joy1_y1) < 10)
			joystick.joy1_y1 = 0;
		if(abs(joystick.joy1_y2) < 10)
			joystick.joy1_y2 = 0;
		if (joy1Btn(1)) //Tophat, precision movement control
		{
			//Shorter = better. :D
			//int th=joystick.joy1_TopHat;powerLeft=(1-th%4)*(powerRight=(th%4==0)?TOP_HAT_FWDBACK_SPEED*(2-th)/2:(th%2==0)?TOP_HAT_TURN_SPEED*(th-4)/2:0);
			if (joystick.joy1_TopHat == 0) {  // forward
				powerLeft = TOP_HAT_FWDBACK_SPEED;
				powerRight = TOP_HAT_FWDBACK_SPEED;
			}
			else if (joystick.joy1_TopHat == 4) { // backward
				powerLeft = -1 * TOP_HAT_FWDBACK_SPEED;
				powerRight = -1 * TOP_HAT_FWDBACK_SPEED;
			}
			else if (joystick.joy1_TopHat == 2) { // right
				powerLeft = TOP_HAT_TURN_SPEED;
				powerRight = -1 * TOP_HAT_TURN_SPEED;
			}
			else if (joystick.joy1_TopHat == 6) { // left
				powerLeft = -1 * TOP_HAT_TURN_SPEED;
				powerRight = TOP_HAT_TURN_SPEED;
			}
		}
		else if(joy1Btn(2)) //one-joystick movement control
		{
			powerLeft=MOTOR_SCALE*(joystick.joy1_y1+joystick.joy1_x1/2);
			powerRight=MOTOR_SCALE*(joystick.joy1_y1-joystick.joy1_x1/2);
		}
		else //Default, tank movement control
		{
			powerRight = MOTOR_SCALE*joystick.joy1_y2;
			powerLeft = MOTOR_SCALE*joystick.joy1_y1;
		}

		motor[motorsRight] = -powerRight;
		motor[motorsLeft] = -powerLeft;
	}
	//we should implement random lag functions ?
}
