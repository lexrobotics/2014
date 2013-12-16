//#include "Autonomous.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-gyro.h"

const tMUXSensor HTIRS2 = msensor_S1_1;

/* Autonomous.c:
   Contains abstraction functions for low-level control of hardware
   such as motors, sensors, etc
*/

//Task prototypes

// Continuously polls the gyroscope to update the robot's current heading
task getHeading();

//Function prototypes

// Returns 1 if an object is within 30 cm of the ultrasonic sensor
// Currently unused
bool robotInTheWay();

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
 bool selectBoolean(char* question, char* option1, char* option2);

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
const float TURN_SCALAR = 1.2; //because it's not a square

//Autonomous related constants
const int BASE_MOTOR_SPEED = 50;
const int BASE_MOTOR_SPEED_SLOW = 20;
const int BASE_MOTOR_SPEED_MAX = 100;

bool robotInTheWay() {
	return SensorValue[sonarSensor] / 2.54 < 30; //30 inches
}

int readIRSector() {
	return HTIRS2readACDir(HTIRS2);
}

void initAutonomous() {
	tHTIRS2DSPMode _mode = DSP_1200;
	StartTask(getHeading);
	pause(2); // wait for gyro to calibrate
	resetEncoders();
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

// Current heading of the robot, updated continuously by getHeading
float currHeading = 0;

task getHeading () {
	float delTime = 0;
	//float prevHeading = 0;
	float curRate = 0;
	nSchedulePriority = kHighPriority;
  HTGYROstartCal(gyro);//Gyro cannot be mux'd.
  pause(1);
  PlaySound(soundBeepBeep);
  while (true) {
    time1[T1] = 0;
    curRate = HTGYROreadRot(gyro);
    //samples ++;
    if (abs(curRate) > 3) {
      //prevHeading = currHeading;
      currHeading += curRate * delTime; //Approximates the next heading by adding the rate*time.
      if (currHeading > 360) currHeading -= 360;
      else if (currHeading < -360) currHeading += 360;
    }
    wait1Msec(5);
    delTime = ((float)time1[T1]) / 1000; //set delta (zero first time around)
  }
}

void turnWithGyro(int speed, float degrees) {
	clearDebugStream();
	currHeading = 0;
	move(0);
	HTGYROstartCal(gyro);
	pause(1);
	//samples = 0;
	if(speed > 0) {
		while(currHeading < degrees) {
				turn(speed);
		}
	}
	else {
		while(currHeading > -1*degrees) {
				turn(speed);
		}
	}
	//finalSamples = samples;
	move(0);
}

void pause(float seconds) {
	wait1Msec(seconds * 1000);
}

bool selectBoolean(char* question, char* option1, char* option2) {
	bool selection = false;
	ClearTimer(T1);
	while(true) {
			nxtDisplayCenteredTextLine(1, question);
			if(selection)
				nxtDisplayCenteredTextLine(2, option1);
			else
				nxtDisplayCenteredTextLine(2, option2);

			if (time1[T1] > 300) {
    		if (nNxtButtonPressed == 1)       selection = !selection;
    		else if (nNxtButtonPressed == 2)  selection = !selection;
  			else if (nNxtButtonPressed == 3)  break;

  		if (nNxtButtonPressed != -1) {
    		// if any buttons were pressed, play sound and wait
      	PlaySound(soundBlip);
     	 	ClearTimer(T1);
    	}
    }
	}
	pause(0.3);
	return selection;
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

void resetEncoders() {
	nMotorEncoder[motorsLeft] = 0;
	nMotorEncoder[motorsRight] = 0;
}
