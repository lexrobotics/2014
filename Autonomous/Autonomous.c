
#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/hitechnic-superpro.h"
#include "drivers/hitechnic-gyro.h"

const tMUXSensor HTIRS2 = msensor_S2_1;

//Task prototypes
task getHeading();

//Function prototypes
// Sets the mode (frequency) of the infrared sensor
void initAutonomous();

// Converts inches to target value for encoder
int inchesToEncoder(int distance);

// Converts degrees to target value for encoder
int degreesToEncoder(int angle);

/* Moves robot with motor power "speed"
 * speed > 0: forward
 * speed < 0: backwards
 * speed = 0: stop
 */
void move(int speed);

/* Turns robot at the center with motor power "speed"
 * speed > 0: clockwise
 * speed < 0: counter-clockwise
 * speed = 0: stop
 */
void turn(int speed);

/* Moves robot a certain distance
 * Works like move() function, except stops when robot reaches "distance" inches
 */
void moveDistance(int speed, int distance);

/* Turns robot a certain angle
 * Works like turn(), except stops when robot reaches angle degrees
 * Degrees is always positive, speed determines direction of rotation
 */
 //void turnDistance(int speed, int angle);

/* Turns robot a certain angle
 * Works like turnDistance()
 * Uses gyroscope, so much more precise!
 */
void turnDistance(int speed, int angle);

// Wait a number of seconds
void pause(float seconds);

// Menu that displays question on screen, gets boolean answer of either two options
bool selectBool(char* s1, char* s2, char* s3);

// Menu that allows user to select an integer delay for beginning of autonomous
int selectDelay();

// Resets all encoder values to 0
void resetEncoders();

//Robot physical constants
const float DIAMETER = 4.0; //diameter of wheel in inches
const float ENCODER_SCALE = 1440.0; //number of encoder counts per rotation
const float CIRCUMFERENCE = DIAMETER * PI;
const float TURN_RADIUS = 11.02; //center of robot to turning circle in inches
const float TURN_CIRCUMFERENCE = 2.0 * TURN_RADIUS * PI; //circumference of circle robot turns in
const float TURN_SCALAR = 1.3; //because it's not a square

//Autonomous related constants
const int BASE_MOTOR_SPEED = 60;
const int BASE_MOTOR_SPEED_SLOW = 30;
const int BASE_MOTOR_SPEED_MAX = 100;

const string PATHS[8] = {"FLE", "FLC", "FQE", "FQC", "RLE", "RLC", "RQE", "RQC"};
/*
bool robotInTheWay() {
	return CLIVE < 30; //30 inches
} */

int readIRSector() {
	return HTIRS2readACDir(HTIRS2);
}

task ohno() {
	HTSPBsetupIO(HTSPB, 0x1);
	HTSPBwriteIO(HTSPB, 0x01);

	while(externalBatteryAvg < 0 || HTSMUXreadPowerStatus(HTSMUX)) {
			HTSPBwriteIO(HTSPB, 0x01);
			wait10Msec(5);
			HTSPBwriteIO(HTSPB, 0x00);
			wait10Msec(5);
	}
	StopTask(ohno);
}

void initAutonomous() {
	tHTIRS2DSPMode _mode = DSP_1200;
	//StartTask(getHeading);
	//pause(2);
	resetEncoders();
	if(externalBatteryAvg < 0 || HTSMUXreadPowerStatus(HTSMUX))
		StartTask(ohno);
}

int inchesToEncoder(int distance) {
	 return distance/CIRCUMFERENCE * ENCODER_SCALE;
}

int degreesToEncoder(int angle) {
	return (angle/360.0 * TURN_CIRCUMFERENCE)/CIRCUMFERENCE * ENCODER_SCALE * TURN_SCALAR;
}

void move(int speed) {
	motor[motorsLeft] = speed;
	motor[motorsRight] = speed;
}

void turn(int speed) {
	motor[motorsLeft] = speed;
	motor[motorsRight] = -1 * speed;
}

void moveDistance(int speed, int distance) {
	int target = inchesToEncoder(distance);
	resetEncoders();

	while(abs(nMotorEncoder[motorsLeft]) < abs(target)  //wait until position reached
		&& abs(nMotorEncoder[motorsRight]) < abs(target)) move(speed); //move at desired speed

	move(0); //stop
}

void turnDistance(int speed, int angle) {
	int target = degreesToEncoder(angle);
	resetEncoders();

	while(abs(nMotorEncoder[motorsLeft]) < abs(target)  //wait until position reached
		&& abs(nMotorEncoder[motorsRight]) < abs(target)) turn(speed); //turn at desired speed

	turn(0); //stop
}

// Current heading of the robot
float currHeading = 0;

// Task to keep track of the current heading using the HT Gyro
task getHeading () {
	float delTime = 0;
	//float prevHeading = 0;
	float curRate = 0;
	nSchedulePriority = kHighPriority;
  HTGYROstartCal(gyro);
  pause(1);
  PlaySound(soundBeepBeep);
  while (true) {
    time1[T1] = 0;
    curRate = HTGYROreadRot(gyro);
    if (abs(curRate) > 3) {
      currHeading += curRate * delTime; //Approximates the next heading by adding the rate*time.
      if (currHeading > 360) currHeading -= 360;
      else if (currHeading < -360) currHeading += 360;
    }
    wait1Msec(5);
    delTime = ((float)time1[T1]) / 1000; //set delta (zero first time around)
  }
}

void turnWithGyro(int speed, float degrees) {
	float delTime = 0;
	float curRate = 0;
	float currHeading = 0;
	nSchedulePriority = kHighPriority;
	move(0);
	pause(1);
  HTGYROstartCal(gyro);
 	pause(1);
 	PlaySound(soundBeepBeep);
	turn(speed);
  while (abs(currHeading) < degrees) {
    time1[T1] = 0;
    curRate = HTGYROreadRot(gyro);
    if (abs(curRate) > 3) {
      currHeading += curRate * delTime; //Approximates the next heading by adding the rate*time.
      if (currHeading > 360) currHeading -= 360;
      else if (currHeading < -360) currHeading += 360;
    }
    wait1Msec(5);
    delTime = ((float)time1[T1]) / 1000; //set delta (zero first time around)
  }
  turn(0);
}

void pause(float seconds) {
	wait10Msec(seconds * 100);
}

int selectDelay() {
	int current = 0;
  ClearTimer(T1);
	int delay = -999;

  while (delay == -999) {
    nxtDisplayCenteredTextLine(1 , "Select Delay");
    nxtDisplayCenteredTextLine(2, "%d seconds", current);

    if (time1[T1] > 300) {
    	if (nNxtButtonPressed == 1)       current++;
    	else if (nNxtButtonPressed == 2)  current--;
  		else if (nNxtButtonPressed == 3)  delay = current;

  		if (current < 0)  current = 0;

  		if (nNxtButtonPressed != -1) {
    		// if any buttons were pressed, play sound and wait
      	PlaySound(soundBlip);
     	 	ClearTimer(T1);
    	}
    }
  }
  pause(0.3);
  return delay;
}

bool selectBool(char* s1, char* s2, char* s3){
	bool b = false;
	ClearTimer(T1);
	while(true) {
			nxtDisplayCenteredTextLine(1, s1);
			if(b)
				nxtDisplayCenteredTextLine(2, s2);
			else
				nxtDisplayCenteredTextLine(2, s3);

			if (time1[T1] > 300) {
    		if (nNxtButtonPressed == 1)       b = !b;
    		else if (nNxtButtonPressed == 2)  b = !b;
  			else if (nNxtButtonPressed == 3)  break;

  		if (nNxtButtonPressed != -1) {
    		// if any buttons were pressed, play sound and wait
      	PlaySound(soundBlip);
     	 	ClearTimer(T1);
    	}
    }
	}
	pause(0.3);
	return b;
}
bool selectQueue() {return selectBool("Select start","Queue","Align");}
bool selectLine() {return selectBool("Select end","Second line","First line");}

int selectPath() {
	int max = 7;
	int index = 0;
	ClearTimer(T1);
	while(true) {
		  if(index < 0)
    		index = max;
    	else if(index > max)
    		index = 0;
			nxtDisplayCenteredTextLine(1, "Choose Path");
			nxtDisplayCenteredTextLine(2, PATHS[index]);

			if (time1[T1] > 300) {
    		if (nNxtButtonPressed == 1)       index++;
    		else if (nNxtButtonPressed == 2)  index--;
  			else if (nNxtButtonPressed == 3)  return index;
  		if (nNxtButtonPressed != -1) {
    		// if any buttons were pressed, play sound and wait
      	PlaySound(soundBlip);
     	 	ClearTimer(T1);
    	}
    }
  }
}

void resetEncoders() {
	nMotorEncoder[motorsLeft] = 0;
	nMotorEncoder[motorsRight] = 0;
}

task ejectFlag() {
	servo[flagExtender] = 200;
	servo[singleWheel] = 127;
	pause(1);
	servo[flagExtender] = 127;
}
