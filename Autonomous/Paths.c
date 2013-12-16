#include "Autonomous.c"

const int SHORT_WAIT = 0.2;
const int LONG_WAIT = 0.5;

static int MOTOR_SPEED = BASE_MOTOR_SPEED;
static int MOTOR_SPEED_SLOW = BASE_MOTOR_SPEED_SLOW;
static int MOTOR_SPEED_MAX = BASE_MOTOR_SPEED_MAX;

static int REVERSE_MOTOR_SPEED = -1*BASE_MOTOR_SPEED;
static int REVERSE_MOTOR_SPEED_SLOW = -1*BASE_MOTOR_SPEED_SLOW;
static int REVERSE_MOTOR_SPEED_MAX = -1*BASE_MOTOR_SPEED_MAX;

void shoot()
{
	move(0);
	pause(LONG_WAIT);

	motor[gun] = -100;

	//DARK MAGIC do not change from 0.1. Seriously.
	pause (0.1);

	motor[gun] = 0;
}//end function shoot

/* Start: Back against wall, against leftmost line (next to tape in corner)
	 Stop: A little bit ahead of driveUp start point, lined up with lower goal tape
*/
void lineUp() {
	moveDistance(MOTOR_SPEED, 7);
	turnWithGyro(REVERSE_MOTOR_SPEED, 45);
}

// DOES NOT FUNCTION
void reverseLineUp() {
	//moveDistance(MOTOR_SPEED, 1);
	turnWithGyro(REVERSE_MOTOR_SPEED, 45);
}

void forwardQueue() {
	moveDistance(MOTOR_SPEED_SLOW, 3);
	pause(SHORT_WAIT);
	turnWithGyro(-1*MOTOR_SPEED, 90);
	pause(SHORT_WAIT);
	moveDistance(MOTOR_SPEED_SLOW, 25);
	pause(SHORT_WAIT);
	turnWithGyro(MOTOR_SPEED, 45);
}

void reverseQueue() {
	moveDistance(REVERSE_MOTOR_SPEED, 3);
	pause(SHORT_WAIT);
	turnWithGyro(MOTOR_SPEED, 90);
	pause(SHORT_WAIT);
	moveDistance(REVERSE_MOTOR_SPEED, 34);
	pause(SHORT_WAIT);
	turnWithGyro(REVERSE_MOTOR_SPEED, 43);
	moveDistance(MOTOR_SPEED_SLOW, 3);
}

/*
	Start: Facing forwards, front lined up with floor goal tape
	Stop: With block launcher pointing at IR basket, with block fired
	Returns: Current encoder pos
*/
int driveUp()
{
	//drives up to basket
	resetEncoders();
	//move slowly until IR is detected or passed ramp
	move(MOTOR_SPEED_SLOW);
	while(readIRSector()!= 5 && nMotorEncoder[motorsRight] < inchesToEncoder(65))
		;
	move(0);
	pause(SHORT_WAIT);
	int stopPos = nMotorEncoder[motorsRight];
	//based on position, move the extra distance we need
	if(inchesToEncoder(35) < abs(nMotorEncoder[motorsRight])) {
		//beyond center
		moveDistance(MOTOR_SPEED_SLOW, 2);
	}
	else {
		//behind center
		moveDistance(MOTOR_SPEED_SLOW, 5);
	}
	shoot();

	return stopPos + nMotorEncoder[motorsRight];
}

int reverseDriveUp() {
	//drives up to basket
	resetEncoders();
	//move slowly until IR is detected or passed ramp
	move(REVERSE_MOTOR_SPEED_SLOW);
	while(readIRSector()!= 5 && nMotorEncoder[motorsRight] < inchesToEncoder(65))
		;
	move(0);
	pause(SHORT_WAIT);
	int stopPos = nMotorEncoder[motorsRight];
	//based on position, move the extra distance we need
	if(inchesToEncoder(35) < abs(nMotorEncoder[motorsRight])) {
		//beyond center
		moveDistance(REVERSE_MOTOR_SPEED_SLOW, 2);
	}
	else {
		//behind center
		moveDistance(REVERSE_MOTOR_SPEED_SLOW, 6);
	}
	shoot();
	return stopPos + nMotorEncoder[motorsRight];
}

/*
	Starts: At IR basket, along tape (at currentPos encoder counts)
	Stops: End of ramp
*/
void endOfRamp(int currentPos)
{
	//drive to end of ramp
	resetEncoders();
	pause(SHORT_WAIT);
/*	if(reverseOntoRamp) {
		move(-1*MOTOR_SPEED);
		while(abs(nMotorEncoder[motorsRight] + currentPos) > inchesToEncoder(5))
			;
		move(0);
	}
	else {*/
	move(MOTOR_SPEED);
	while(abs(nMotorEncoder[motorsRight] + currentPos) < inchesToEncoder(50))
		;
	move(0);
//	}
}//end of function endOfRamp

/*
	Starts: At IR basket, along tape (at currentPos encoder counts) (rear of robot facing forwards)
	Stops: End of ramp
*/
void reverseEndOfRamp(int currentPos) {
		//drive to end of ramp
	resetEncoders();
	pause(SHORT_WAIT);
/*	if(reverseOntoRamp) {
		move(-1*MOTOR_SPEED);
		while(abs(nMotorEncoder[motorsRight] + currentPos) > inchesToEncoder(5))
			;
		move(0);
	}
	else {*/
	move(REVERSE_MOTOR_SPEED);
	while(abs(nMotorEncoder[motorsRight] + currentPos) < inchesToEncoder(50))
		;
	move(0);
}

void beginningOfRamp(int currentPos) {
	int rev=1;

	resetEncoders();
	pause(SHORT_WAIT);
	move(-rev*MOTOR_SPEED);
	while(rev*(nMotorEncoder[motorsRight] + currentPos) > inchesToEncoder(15))
		;
	move(0);
}

void reverseBeginningOfRamp(int currentPos) {
	int rev=-1;

	resetEncoders();
	pause(SHORT_WAIT);
	move(-rev*MOTOR_SPEED);
	while(rev*(nMotorEncoder[motorsRight] + currentPos) > inchesToEncoder(5))
		;
	move(0);
}

void ramp(int rev){
	//line up with ramp
	resetEncoders();
	pause(SHORT_WAIT);
	turnWithGyro(rev*MOTOR_SPEED, 40, false);
	moveDistance(rev*MOTOR_SPEED, 12);
	pause(SHORT_WAIT);
	turnWithGyro(rev*MOTOR_SPEED, 30, false);//NOTE for original: in forwardRamp it's 40, in reverseRamp it's 30. --should not matter a whole lot--
	moveDistance(rev*MOTOR_SPEED_MAX, 30);
}
void forwardRamp(){ramp(1);}
void reverseRamp(){ramp(-1);}

void turnAndPark(){
	//turn and park
	resetEncoders();
	pause(SHORT_WAIT);
	turnWithGyro(REVERSE_MOTOR_SPEED, 85, false);
	moveDistance(REVERSE_MOTOR_SPEED_MAX, 50);
}//end of turnAndPark
