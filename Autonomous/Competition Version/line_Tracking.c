#include "Autonomous.c"
#include "line_Tracking.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-light.h"

const tMUXSensor LLIGHT = msensor_S3_3;
const tMUXSensor RLIGHT = msensor_S3_4;

static int lineSpeed = 30;
static int turnSpeed = 60;
static int lightValue = 45;
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
		if(leftLight < lightValue || leftLightPrev < lightValue) {
			driftRight(turnSpeed);
			leftLightPrev = leftLight;
			leftLight = LSvalNorm(LLIGHT);
		}
		rightLight = LSvalNorm(RLIGHT);
		rightLightPrev = rightLight;
		if(rightLight < lightValue || rightLightPrev < lightValue) {
			driftLeft(turnSpeed);
			rightLightPrev = rightLight;
			rightLight = LSvalNorm(RLIGHT);
		}
	}
	*/
	leftLight = LSvalNorm(LLIGHT);
	while(leftLight < lightValue) {
			leftLight = LSvalNorm(LLIGHT);
			driftRight(50);
	}
	rightLight = LSvalNorm(RLIGHT);
	while(rightLight < lightValue) {
			rightLight = LSvalNorm(RLIGHT);
			driftLeft(50);
	}
}

void findLine(int reverse) {
	int findTarget = inchesToEncoder(72);
	resetEncoders();
	move(lineSpeed);
	leftLight = LSvalNorm(LLIGHT);
	rightLight = LSvalNorm(RLIGHT);
	leftLightPrev = leftLight;
	rightLightPrev = rightLight; // checks previous light sensor values to minimize the effects of an unusual sensor reading
	while((leftLight < lightValue || leftLightPrev < lightValue) && (rightLight < lightValue || rightLightPrev < lightValue)) {
  	if(abs(nMotorEncoder[motorsLeft]) > abs(findTarget)  // hits wall
	 && abs(nMotorEncoder[motorsRight]) > abs(findTarget)) {
			moveDistance(-1 * lineSpeed, 18);
			turnDistance(reverse * lineSpeed, 30);
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
	turn(reverse * turnSpeed);
	pause(0.4); // don't start checking the sensor until the robot moves off of the line.
	rightLight = LSvalNorm(RLIGHT);
	rightLightPrev = rightLight;
	while(rightLight < lightValue || rightLightPrev < lightValue) {
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

void newLineUp(short rightLightValue) {
	while(LSvalNorm(LLIGHT) < lightValue || LSvalNorm(RLIGHT) < lightValue) { // not aligned
		if(rightLightValue > lightValue) { // right hit first
			while(LSvalNorm(LLIGHT) < lightValue)
				driftRight(turnSpeed);
			while(LSvalNorm(RLIGHT) < lightValue)
				driftLeft(-1 * turnSpeed);
		}
		else { // left hit first
			while(LSvalNorm(RLIGHT) < lightValue)
				driftLeft(turnSpeed);
			while(LSvalNorm(LLIGHT) < lightValue)
				driftRight(-1 * turnSpeed);
		}
	}
}

void runLineUp() {
	leftLight = LSvalNorm(LLIGHT);
	rightLight = LSvalNorm(RLIGHT);
	leftLightPrev = leftLight;
	rightLightPrev = rightLight;
	while((leftLight < lightValue || leftLightPrev < lightValue) && (rightLight < lightValue || rightLightPrev < lightValue)) {
		move(lineSpeed);
		leftLightPrev = leftLight;
		rightLightPrev = rightLight;
		leftLight = LSvalNorm(LLIGHT);
		rightLight = LSvalNorm(RLIGHT);
	}
	move(0);
	pause(0.2);
	if(leftLight > lightValue && rightLight > lightValue) { // already good
		return;
	}
	if(rightLight > lightValue) { // right hit first
			newLineUp(rightLight);
			move(0);
			turnDistance(turnSpeed, 8);
	}
	else { // left hit first
			newLineUp(rightLight);
			move(0);
			turnDistance(-1 * turnSpeed, 8);
	}
}
