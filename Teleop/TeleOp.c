#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  motorA,          gun,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     dualWheels,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorsLeft,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     lift1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     lift2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    singleWheelTilt,      tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_2,    rampTilt,             tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_3,    flagExtender,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    singleWheel,          tServoContinuousRotation)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c" //library with joystick controls

static float MOTOR_SCALE = 200.0/256.0; //since joystick values range from -128 to 127 and motors from -100 to 100, we need to scale values from the joystick

void initialize() {
	servo[rampTilt] = 127;
	servo[singleWheelTilt]  = 127;
	servo[singleWheel] = 127;
}

//This is the task where we define all servo/"arm" movements.
//By separating the arm and drive tasks, it lets us logically separate our code, and run each one in parallel.
//e.g. you can raise your arm while driving at the same time
//although technically you could just paste it all into main() and it would still work
task arm() {
	while(true){
	int	x = singleWheelTilt;
		getJoystickSettings(joystick); //grab snapshot of controller positions


		/******JOYSTICK 1*******/

		//WHEELS
		/*
		Shorthand for both dualwheels and singlewheel
		(both continous rotation)

		1 - spit-out
		6 - suck-in
		8 - turn off spit-out
		*/
		if(joy1Btn(1)){					//activates dualWheels and singleWheel using joy1's Right Triggers
			motor[dualWheels] = -20;//bringing in or shooting out blocks
			servo[singleWheel]  = 240;
		}
		else if(joy1Btn(6)){
			motor[dualWheels] = 40;
			servo[singleWheel] = 30;
		}
		else if(joy1Btn(8)){
			motor[dualWheels] = 0;
			servo[singleWheel] = 127;
		}
		/*
		singleWheel - continuous rotation servo
		changes SingleWheel (the one holding in the ramp blocks) speed
		Left trigger up inward
		Left trigger down stop
		*/
		if(joy1Btn(5))
			servo[singleWheel] = 240;
		else if(joy1Btn(7))
			servo[singleWheel] = 127;


		//TILTS
		/*
		rampTilt - 180-deg servo
		controls ramp angle with that servo
		joy1 btn 4 press+hold raises it (ignore the 00 01 02 03 in Joystick Control)
		joy1 btn 2 press+hold lowers it
		*/
		if(joy1Btn(4))
			servo[rampTilt] = 127+64;
		else if(joy1Btn(2))
			servo[rampTilt] = 127 - 64;
		else
			servo[rampTilt] = 127;


		/*
		singleWheelTilt - 180-deg servo
		That thingy controlling the arm with the wheel
		joy1 tophat up (0) press+hold raises it
		joy1 tophat down (4) press+hold lowers it
		*/

		if (joystick.joy1_TopHat == 0){
			servo[singleWheelTilt] = 127 + 64;
			servo[rampTilt] = 127 + 64;
		}
		else if (joystick.joy1_TopHat == 4){
			servo[singleWheelTilt] = 127 - 64;
			servo[rampTilt] = 127 - 64;
		}
		else
			servo[singleWheelTilt] = 127;
			servo[singleWheelTilt] = 127;



		/******JOYSTICK 2******/
		/*
		flagExtender - continuous servo

		*/
		if(joy2Btn(1))// flagExtender is controlled using joy2's buttons 1 and 3
			servo[flagExtender] = 255;
		else if(joy2Btn(3))
			servo[flagExtender] = 0;
		else
			servo[flagExtender]  = 127;

		/*
		flagMotor - motor
		spin dat flag using joy2's buttons 2 and 4
		2 (bottom) - wind up
		4 (top) - wind down
		*/
		if(joy2Btn(2))
			motor[flagMotor] = 100;
		else if(joy2Btn(4))
			motor[flagMotor] = -100;
		else
			motor[flagMotor] = 0;

		/*
		lift1 - motor
		Lifts the ramp level
		right up raises
		right down lowers
		*/
		if(joy2Btn(7))					//controls lift1 using joy2's left triggers
			motor[lift1] = 100;
		else if(joy2Btn(5))
			motor[lift1] = -100;
		else
			motor[lift1] = 0;

		/*
		lift2 - motor
		Lifts the hook level
		left up raises
		left down lowers
		*/
		if(joy2Btn(8))					//controls lift2 using joy2's right triggers
			motor[lift2] = 100;
		else if(joy2Btn(6))
			motor[lift2] = -100;
		else
			motor[lift2] = 0;
	}//while(true) arm
}//task arm()

task main() {
	/****************INITIALIZE TeleOp*****************/
	// Initialize robot actuators
	initialize();
	// Wait until receive relevant signal for start of tele-op phase
	waitForStart();

	/*******************BEGIN PROCESSES****************/
	StartTask(arm);//parallel 'arm' task

	//ClearTimer(T1);//I think this was for loss-of-connection detection, but the other code doesn't exist here anymore.

	//Process for driving.
	while(true) {
		getJoystickSettings(joystick); //grab snapshot of controller positions to 'joystick' 'object'

		//Joysticks don't settle to zero; so each axis zeroed if within 10 of zero
		//Copy this for each joystick x/y direction used, or drift will happen.
		if(abs(joystick.joy1_y1) < 10)
			joystick.joy1_y1 = 0;
		if(abs(joystick.joy1_y2) < 10)
			joystick.joy1_y2 = 0;

		writeDebugStreamLine("%d %d",joystick.joy1_y1,joystick.joy1_y2);

		int j1=MOTOR_SCALE*joystick.joy1_y1;
		int j2=MOTOR_SCALE*joystick.joy1_y2;

		motor[motorsLeft] = j1;//powerLeft
		motor[motorsRight] = j2;//powerRight
	}//while(true) driving
}//task arm()
