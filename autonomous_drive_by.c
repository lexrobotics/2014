#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorsRight,   tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     pulleyMotor,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     hangingMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorsLeft,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     harvestMotor,  tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    gun,                  tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    flagExtender,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_3,    harvestLifter,        tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "AutonomousStandard.h"

static int motorSpeed = 50;
static int motorSpeedSlow=25;
static int centerDist = 40;
static int rampDist = 80;

task main() {
	waitForStart();
	int sector = 0;
	initAutonomous();
	resetEncoders();
	servo[gun] = 255;

	bool scanning = true;
	move(motorSpeedSlow);
	while(sector!=5 && nMotorEncoder[motorsRight]<inchesToEncoder(65))
		sector = HTIRS2readACDir(HTIRS2);
	/*while(scanning) {
		sector = HTIRS2readACDir(HTIRS2);
		if(sector==5) {
			move(motorSpeedSlow);
		}
		else
			scanning = false;
	}*/


	move(0);

	pause(0.1);
	int currentPos = nMotorEncoder[motorsRight];

	if(inchesToEncoder(35)<nMotorEncoder[motorsRight]) {

		moveDistance(motorSpeedSlow, 6);
	}
else {
	moveDistance(motorSpeedSlow, 9);
}
	pause(0.1);

	move(0);

	servo[gun] = 0;
	pause(0.5);
	servo[gun] = 255;

	while(nMotorEncoder[motorsRight]+currentPos<inchesToEncoder(65)) {
		move(motorSpeed);
  }
  move(0);
	pause(0.2);
	turnDistance(motorSpeed, 60);
	moveDistance(-1*motorSpeed, 40);
	turnDistance(-1*motorSpeed, 55);
	moveDistance(-100, 40);

	servo[harvestLifter] = 0;
	pause(6.5);
	servo[harvestLifter] = 127;
}
