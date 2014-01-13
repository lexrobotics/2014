#include "Autonomous.c"
#include "line_Tracking.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-light.h"

const tMUXSensor RLIGHT = msensor_S3_2;
const tMUXSensor LLIGHT = msensor_S3_1;

static int lineSpeed = -30;
static int turnSpeed = -60;
static int lightValue = 50;
short leftLight, rightLight, leftLightPrev, rightLightPrev;

void driftLeft(int speed) {
	motor[motorsLeft] = -50;
	motor[motorsRight] = -10;
}

void driftRight(int speed) {
	motor[motorsLeft] = -10;
	motor[motorsRight] = -50;
}

void lightsCameraAction() {
	LSsetActive(RLIGHT);
	LSsetActive(LLIGHT);
	pause(0.2);
}

void lineFollow() {
	int lineTarget = inchesToEncoder(60);
	resetEncoders();
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
}

void findLine(int reverse) {
	int findTarget = inchesToEncoder(72);
	resetEncoders();
	move(lineSpeed);
	leftLight = LSvalNorm(LLIGHT);
	rightLight = LSvalNorm(RLIGHT);
	leftLightPrev = leftLight;
	rightLightPrev = rightLight; // Checks previous light sensor values to minimize the effects of an unusual sensor reading
	while((leftLight < lightValue || leftLightPrev < lightValue) && (rightLight < lightValue || rightLightPrev < lightValue)) {
  	if(abs(nMotorEncoder[motorsLeft]) > abs(findTarget)  // Hits wall
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
	pause(0.4); // Don't start checking the sensor until the robot moves off of the line.
	rightLight = LSvalNorm(RLIGHT);
	rightLightPrev = rightLight;
	while(rightLight < lightValue || rightLightPrev < lightValue) {
		if(abs(nMotorEncoder[motorsLeft]) > abs(alignTarget)  // Misses line
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

void lineUp(bool secondLine) {
	lightsCameraAction();
	findLine(1);
	alignLine(1);
	lineFollow();
}

void reverseLineUp(bool secondLine) {
	lightsCameraAction();
	findLine(-1);
	alignLine(-1);
	lineFollow();
}
