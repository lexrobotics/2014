#include "Autonomous.h"

const float DIAMETER = 4.0; //diameter of wheel in inches
const float ENCODER_SCALE = 1440.0; //number of encoder counts per rotation
const float CIRCUMFERENCE = DIAMETER * PI;
const float TURN_RADIUS = 0.0; //center of robot to turning circle in inches
const float TURN_CIRCUMFERENCE = 2.0 * TURN_RADIUS * PI; //circumference of circle robot turns in
const float
void move(int speed) {
	motor[motorsLeft] = speed;
	motor[motorsRight] = speed;
}

void turn(int speed) {
	motor[motorsLeft] = -1 * speed;
	motor[motorsRight] = speed;
}

void moveDistance(int speed, int distance) {
	int target = distance/CIRCUMFERENCE * ENCODER_SCALE; 
	int targetLeft = target - nMotorEncoder[motorsLeft]; //offset targets by current positions
	int targetRight = target - nMotorEncoder[motorsRight];
	
	move(speed); //move at desired speed

	while(abs(nMotorEncoder[motorsLeft]) < abs(targetLeft)  //wait until position reached
		&& abs(nMotorEncoder[motorsRight]) < abs(targetRight));

	move(0); //stop
}

void turnDistance(int speed, int angle) {
	int target = (angle/360 * TURN_CIRCUMFERENCE) / CIRCUMFERENCE * ENCODER_SCALE;
	int targetLeft = target - nMotorEncoder[motorsLeft]; //offset targets by current positions
	int targetRight = target - nMotorEncoder[motorsRight];

	turn(speed); //turn at desired speed

	while(abs(nMotorEncoder[motorsLeft]) < abs(targetLeft)  //wait until position reached
		&& abs(nMotorEncoder[motorsRight]) < abs(targetRight));

	turn(0); //speed
}

void resetEncoders() {
	nMotorEncoder[motorsLeft] = 0;
	nMotorEncoder[motorsRight] = 0;
}