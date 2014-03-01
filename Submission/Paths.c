#include "Autonomous.c"

/* Paths.c
   An additional layer of abstraction that contains functions that 
   use Autonomous.c functions to implement different subpaths for 
   completing Autonomous tasks
*/

const int SHORT_WAIT = 0.2;
const int LONG_WAIT = 0.5;

static int MOTOR_SPEED = BASE_MOTOR_SPEED;
static int MOTOR_SPEED_SLOW = BASE_MOTOR_SPEED_SLOW;
static int MOTOR_SPEED_MAX = BASE_MOTOR_SPEED_MAX;

static int REVERSE_MOTOR_SPEED = -1*BASE_MOTOR_SPEED;
static int REVERSE_MOTOR_SPEED_SLOW = -1*BASE_MOTOR_SPEED_SLOW;
static int REVERSE_MOTOR_SPEED_MAX = -1*BASE_MOTOR_SPEED_MAX;

//shoots block
void shoot()
{
	pause(SHORT_WAIT);
	motor[gun] = -100;
	pause (0.1);
	motor[gun] = 0;
}

/* Start: Back against wall, against leftmost line (next to tape in corner)
   Stop: A little bit ahead of driveUp start point, lined up with lower goal tape
*/
void lineUp() {
	moveDistance(MOTOR_SPEED, 7);
	turnWithGyro(REVERSE_MOTOR_SPEED, 45);
}

/* Start: Back against wall, against rightmost line (next to tape for block zone)
   Stop: A little bit ahead of driveUp start point, lined up with lower goal tape
*/
void forwardQueue() {
	moveDistance(MOTOR_SPEED_SLOW, 5);
	pause(SHORT_WAIT);
	turnWithGyro(-1*MOTOR_SPEED, 90);
	pause(SHORT_WAIT);
	moveDistance(MOTOR_SPEED_SLOW, 25);
	pause(SHORT_WAIT);
	turnWithGyro(MOTOR_SPEED, 38);
}

/* Start: Front against wall, same as forwardQueue, but on opposite end of field
   Stop: A little bit ahead of reverseDriveUp start point, lined up with lower goal tape
*/
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
	resetEncoders();
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

/*
	Start: Facing backwards, back lined up with floor goal tape
	Stop: With block launcher pointing at IR basket, with block fired
	Returns: Current encoder pos
*/
int reverseDriveUp() {
	resetEncoders();
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
	Starts: At IR basket, facing forwards, along tape (at currentPos encoder counts)
	Stops: End of ramp
*/
void endOfRamp(int currentPos)
{
	//drive to end of ramp
	resetEncoders();
	pause(SHORT_WAIT);
	move(MOTOR_SPEED);
	while(abs(nMotorEncoder[motorsRight] + currentPos) < inchesToEncoder(50))
		;
	move(0);
}

/*
	Starts: At IR basket, facing backwards, along tape (at currentPos encoder counts)
	Stops: End of ramp
*/
void reverseEndOfRamp(int currentPos) 
{
	//drive to end of ramp
	resetEncoders();
	pause(SHORT_WAIT);
	move(REVERSE_MOTOR_SPEED);
	while(abs(nMotorEncoder[motorsRight] + currentPos) < inchesToEncoder(50))
		;
	move(0);
}

/*
	Starts: At IR basket, facing forwards, along tape (at currentPos encoder counts)
	Stops: Beginning of ramp (side where robot started)
*/
void beginningOfRamp(int currentPos) 
{
	resetEncoders();
	pause(SHORT_WAIT);
	move(-1*MOTOR_SPEED);
	while(abs(nMotorEncoder[motorsRight] + currentPos) > inchesToEncoder(5))
		;
	move(0);
}

/*
	Starts: At IR basket, facing backwards, along tape (at currentPos encoder counts)
	Stops: Beginning of ramp (side where robot started)
*/
void reverseBeginningOfRamp(int currentPos) 
{
	resetEncoders();
	pause(SHORT_WAIT);
	move(MOTOR_SPEED);
	writeDebugStreamLine("%d+%d/%d", nMotorEncoder[motorsRight], currentPos, inchesToEncoder(5));
	while(nMotorEncoder[motorsRight] + currentPos < -1*inchesToEncoder(5))
		;
	move(0);
}

/*
	Starts: At the end of ramp, facing forwards
	Stops: Parallel to the edge of the ramp
*/
void forwardRamp()
{
	resetEncoders();
	pause(SHORT_WAIT);
	turnWithGyro(MOTOR_SPEED, 40);
	moveDistance(MOTOR_SPEED, 12);
	pause(SHORT_WAIT);
	turnWithGyro(MOTOR_SPEED, 40);
	moveDistance(MOTOR_SPEED_MAX, 30);
}

/*
	Starts: At the end of ramp, facing backwards
	Stops: Parallel to the edge of the ramp
*/
void reverseRamp()
{
	resetEncoders();
	pause(SHORT_WAIT);
	turnWithGyro(REVERSE_MOTOR_SPEED, 40);
	moveDistance(REVERSE_MOTOR_SPEED, 12);
	pause(SHORT_WAIT);
	turnWithGyro(REVERSE_MOTOR_SPEED_MAX, 30);
	moveDistance(REVERSE_MOTOR_SPEED_MAX, 30);
}

/*
	Starts: Parallel to the end of the ramp, facing forwards
	Stops: On the middle of the ramp
*/
void turnAndPark()
{
	resetEncoders();
	pause(SHORT_WAIT);
	turnWithGyro(REVERSE_MOTOR_SPEED, 85);
	moveDistance(REVERSE_MOTOR_SPEED_MAX, 40);
}

/*
	Starts: Parallel to the end of the ramp, facing backwards
	Stops: On the middle of the ramp
*/
void reverseTurnAndPark()
{
	resetEncoders();
	pause(SHORT_WAIT);
	turnWithGyro(REVERSE_MOTOR_SPEED, 85);
	moveDistance(REVERSE_MOTOR_SPEED_MAX, 40);
}
