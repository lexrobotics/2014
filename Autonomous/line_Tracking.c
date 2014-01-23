#include "Autonomous.c"
#include "line_Tracking.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-light.h"

const tMUXSensor LLIGHT = msensor_S3_3;
const tMUXSensor RLIGHT = msensor_S3_4;

const int LINE_SPEED = 30;
const int TURN_SPEED = 60;
const int LIGHT_VALUE = 45;
short leftLight, rightLight, leftLightPrev, rightLightPrev;

void driftLeft(int speed) {
	motor[motorsLeft] = 0;
	motor[motorsRight] = speed;
}

void driftRight(int speed) {
	motor[motorsLeft] = speed;
	motor[motorsRight] = 0;
}

void lightsCameraAction() {
	LSsetActive(LLIGHT);
	LSsetActive(RLIGHT);
	pause(0.2);
}

void lineFollow() {
	resetEncoders();
	/*
	int lineTarget = inchesToEncoder(60);
	while(abs(nMotorEncoder[motorsLeft]) < abs(lineTarget)
		&& abs(nMotorEncoder[motorsRight]) < abs(lineTarget)) {
		leftLight = LSvalNorm(LLIGHT);
		leftLightPrev = leftLight;
		if(leftLight < LIGHT_VALUE || leftLightPrev < LIGHT_VALUE) {
			driftRight(TURN_SPEED);
			leftLightPrev = leftLight;
			leftLight = LSvalNorm(LLIGHT);
		}
		rightLight = LSvalNorm(RLIGHT);
		rightLightPrev = rightLight;
		if(rightLight < LIGHT_VALUE || rightLightPrev < LIGHT_VALUE) {
			driftLeft(TURN_SPEED);
			rightLightPrev = rightLight;
			rightLight = LSvalNorm(RLIGHT);
		}
	}
	*/
	leftLight = LSvalNorm(LLIGHT);
	while(leftLight < LIGHT_VALUE) {
			leftLight = LSvalNorm(LLIGHT);
			driftRight(TURN_SPEED);
	}
	rightLight = LSvalNorm(RLIGHT);
	while(rightLight < LIGHT_VALUE) {
			rightLight = LSvalNorm(RLIGHT);
			driftLeft(TURN_SPEED);
	}
}

void findLine(int reverse) {
	int findTarget = inchesToEncoder(72);
	resetEncoders();
	move(LINE_SPEED);
	leftLight = LSvalNorm(LLIGHT);
	rightLight = LSvalNorm(RLIGHT);
	leftLightPrev = leftLight;
	rightLightPrev = rightLight; // checks previous light sensor values to minimize the effects of an unusual sensor reading
	while((leftLight < LIGHT_VALUE || leftLightPrev < LIGHT_VALUE) && (rightLight < LIGHT_VALUE || rightLightPrev < LIGHT_VALUE)) {
  	if(abs(nMotorEncoder[motorsLeft]) > abs(findTarget)  // hits wall
	 && abs(nMotorEncoder[motorsRight]) > abs(findTarget)) {
			moveDistance(LINE_SPEED, 18);
			turnDistance(reverse * LINE_SPEED, 30);
			findLine(reverse);
			return;
	 	}
		leftLightPrev = leftLight;
		rightLightPrev = rightLight;
		leftLight = LSvalNorm(LLIGHT);
		rightLight = LSvalNorm(RLIGHT);
	}
	move(0);
	pause(0.1);
}

void alignLine(int reverse) {
	int alignTarget = degreesToEncoder(360);
	resetEncoders();
	turn(reverse * TURN_SPEED);
	pause(0.4); // don't start checking the sensor until the robot moves off of the line.
	rightLight = LSvalNorm(RLIGHT);
	rightLightPrev = rightLight;
	while(rightLight < LIGHT_VALUE || rightLightPrev < LIGHT_VALUE) {
		if(abs(nMotorEncoder[motorsLeft]) > abs(alignTarget)  // misses line
	 && abs(nMotorEncoder[motorsRight]) > abs(alignTarget)) {
			findLine(reverse);
			alignLine(reverse);
			return;
		}
		rightLightPrev = rightLight;
		rightLight = LSvalNorm(RLIGHT);
	}
	move(0);
	pause(0.1);
}

void newLineUp(short rightLight) {
	while(LSvalNorm(LLIGHT) < LIGHT_VALUE || LSvalNorm(RLIGHT) < LIGHT_VALUE) { // not aligned
		if(rightLight > LIGHT_VALUE) { // right hit first
			while(LSvalNorm(LLIGHT) < LIGHT_VALUE)
				driftRight(TURN_SPEED);
			while(LSvalNorm(RLIGHT) < LIGHT_VALUE)
				driftLeft(-1 * TURN_SPEED);
		}
		else { // left hit first
			while(LSvalNorm(RLIGHT) < LIGHT_VALUE)
				driftLeft(TURN_SPEED);
			while(LSvalNorm(LLIGHT) < LIGHT_VALUE)
				driftRight(-1 * TURN_SPEED);
		}
	}
}

void runLineUp() {
	leftLight = LSvalNorm(LLIGHT);
	rightLight = LSvalNorm(RLIGHT);
	leftLightPrev = leftLight;
	rightLightPrev = rightLight;
	while((leftLight < LIGHT_VALUE || leftLightPrev < LIGHT_VALUE) && (rightLight < LIGHT_VALUE || rightLightPrev < LIGHT_VALUE)) {
		move(LINE_SPEED);
		leftLightPrev = leftLight;
		rightLightPrev = rightLight;
		leftLight = LSvalNorm(LLIGHT);
		rightLight = LSvalNorm(RLIGHT);
	}
	move(0);
	pause(0.2);
	if(leftLight > LIGHT_VALUE && rightLight > LIGHT_VALUE) { // already good
		return;
	}
	if(rightLight > LIGHT_VALUE) { // right hit first
			newLineUp(rightLight);
			move(0);
			turnDistance(TURN_SPEED, 8);
	}
	else { // left hit first
			newLineUp(rightLight);
			move(0);
			turnDistance(-1 * TURN_SPEED, 8);
	}
}
