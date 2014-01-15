#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,		 HTSMUX,				 sensorI2CCustom)
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
#pragma config(Servo,  srvo_S1_C4_4,    singleWheel,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_5,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servonone,          	tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "Autonomous.c"
#include "line_Tracking.c"
//#include "CollisionDetection.c"
#include "drivers/hitechnic-irseeker-v2.h"

static int motorSpeed = 50;
static int motorSpeedSlow = 25;
static int centerDist = 40;
static int rampDist = 80;

task main() {
	int initDelay = selectDelay();
	bool shouldQueue = selectQueue();
	bool shouldTakeSecondLine = selectLine();
	//waitForStart();
	//ClearTimer(T2);
	//StartTask(dropHarvester);
	pause(initDelay);

	//addToLogWithTime("AutoStart");

	int sector = 0;
	initAutonomous();
	resetEncoders();

	if(shouldQueue) {
		turnDistance(-1*motorSpeed, 32);
		moveDistance(motorSpeedSlow, 33);
		turnDistance(motorSpeed, 51);
	}
	resetEncoders();

	move(motorSpeedSlow);
	while(sector!= 5 && nMotorEncoder[motorsRight] < inchesToEncoder(65)) {
		sector = HTIRS2readACDir(HTIRS2);
	}
	/*
	bool scanning = true;
	while(scanning) {
		sector = HTIRS2readACDir(HTIRS2);
		if(sector==5)
			move(motorSpeedSlow);
		else
			scanning = false;
	}
	*/
	move(0);
	pause(0.1);
	int currentPos = nMotorEncoder[motorsRight];

	if(inchesToEncoder(35) < nMotorEncoder[motorsRight]) {
		//moveDistance(motorSpeedSlow, 4);
	}
	else {
		moveDistance(motorSpeedSlow, 3);
	}
	//pause(0.1);
	//move(0);

	motor[gun] = -100;
	pause(0.1);
	motor[gun] = 0;

  //addToLogWithTime("Shot gun");

  resetEncoders();
 pause(0.5);
  while(nMotorEncoder[motorsRight] + currentPos < inchesToEncoder(55)) {
		move(motorSpeed);
  }
  move(0);

  //addToLogWithTime("Past baskets");

	pause(0.1);
	turnDistance(motorSpeed, 45);
	moveDistance(100, 5);
	turnDistance(motorSpeed, 50);
	moveDistance(100, 30);
	pause(1);

	//lightsCameraAction();
	//runLineUp();

	if(robotInTheWay()) {
		moveDistance(100, 29);
	}
	turnDistance(-100, 100);
	moveDistance(-100, 40);
	/*
	if(shouldTakeSecondLine) {
		while(LSvalNorm(RLIGHT)<lightValue){
			move(-50);
		}
		turnDistance(-50, 20);
		moveDistance(-50, 10);
	}
	newLineUp();
	resetEncoders();
	*/
	/*
	int prevEncoder = 0;
 	do {
 		prevEncoder = nMotorEncoder[motorsRight];
		move(-50);
		pause(0.1);
		eraseDisplay();
		nxtDisplayTextLine(2, "%d/%d", nMotorEncoder[motorsRight], inchesToEncoder(40));
	}	while(abs(nMotorEncoder[motorsRight])<inchesToEncoder(40) && nMotorEncoder[motorsRight]!=prevEncoder);
	*/
	move(0);
	/*
	moveDistance(-1*motorSpeed, 40);
	turnDistance(-1*motorSpeed, 90);
	resetEncoders();
	move(-100);
	pause(0.5);
	while(!stationary && nMotorEncoder[motorsRight]<inchesToEncoder(40))
		move(-100);
  move(0);
	addToLogWithTime("On ramp");
	*/
}
