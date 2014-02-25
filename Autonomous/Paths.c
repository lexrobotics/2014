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
	pause(SHORT_WAIT);

	//shoot block
	motor[gun] = -100;

	//Do not change the value below
	//It is an ancient and powerful value naturally imbued with DARK MAGIC
	//The one who changes it will be bestowed with a curse upon
	//Thee and your family
	//Dooming them to being smited by supernatural forces
	//(It seriously won't work if you change it so please don't)

	pause (0.1);
	/*
	DO NOT CHANGE ABOVE ARGUMENT!!
	MUST BE 0.1!!
	*/

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
	moveDistance(MOTOR_SPEED_SLOW, 5);
	pause(SHORT_WAIT);
	turnWithGyro(-1*MOTOR_SPEED, 90);
	pause(SHORT_WAIT);
	moveDistance(MOTOR_SPEED_SLOW, 25);
	pause(SHORT_WAIT);
	turnWithGyro(MOTOR_SPEED, 38);
}

void reverseQueue() {
	moveDistance(MOTOR_SPEED_SLOW, 5);
	pause(SHORT_WAIT);
	turnWithGyro(-1*MOTOR_SPEED, 90);
	pause(SHORT_WAIT);
	moveDistance(MOTOR_SPEED_SLOW, 34);
	pause(SHORT_WAIT);
	turnWithGyro(MOTOR_SPEED, 42);
	pause(SHORT_WAIT);
	moveDistance(-1*MOTOR_SPEED, 2);
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
		moveDistance(REVERSE_MOTOR_SPEED_SLOW, 5);
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
	resetEncoders();
	pause(SHORT_WAIT);
	move(-1*MOTOR_SPEED);
	while(abs(nMotorEncoder[motorsRight] + currentPos) > inchesToEncoder(5))
		;
	move(0);
}

void reverseBeginningOfRamp(int currentPos) {
	resetEncoders();
	pause(SHORT_WAIT);
	move(MOTOR_SPEED);
	writeDebugStreamLine("%d+%d/%d", nMotorEncoder[motorsRight], currentPos, inchesToEncoder(5));
	while(nMotorEncoder[motorsRight] + currentPos < -1*inchesToEncoder(5))
		;
	move(0);
}

void forwardRamp()
{
	//line up with ramp
	resetEncoders();
	pause(SHORT_WAIT);
	turnWithGyro(MOTOR_SPEED, 40);
	moveDistance(MOTOR_SPEED, 12);
	pause(SHORT_WAIT);
	turnWithGyro(MOTOR_SPEED, 40);
	moveDistance(MOTOR_SPEED_MAX, 30);
}//end of forwardRamp

void reverseRamp()
{
	//line up with ramp
	resetEncoders();
	pause(SHORT_WAIT);
	turnWithGyro(-1*MOTOR_SPEED, 40);
	moveDistance(-1*MOTOR_SPEED, 12);
	pause(SHORT_WAIT);
	turnWithGyro(-1*MOTOR_SPEED, 30);
	moveDistance(-1*MOTOR_SPEED_MAX, 30);
}//end of reverseRamp

void turnAndPark()
{
	//turn and park
	resetEncoders();
	pause(SHORT_WAIT);
	turnWithGyro(-50, 85);
	moveDistance(-100, 40);
}//end of turnAndPark
