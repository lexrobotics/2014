#include "Autonomous.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/hitechnic-gyro.h"

#define CLIVE SensorValue[sonarSensor] / 2.54
// Cool
// Legendary
// Ingenious
// Victorious
// Elephant

//Task prototypes
task getHeading();

//Function prototypes
//TODO

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
	return CLIVE < 30; //30 inches
}

/*void wallFollow(int distance) {
	const int ERROR = 2; //error in inches/2
	nxtDisplayCenteredTextLine(2, "%d / %d", CLIVE, distance);
	if(CLIVE > distance + ERROR) {
		//drift right
		motor[motorsRight] = MOTOR_SPEED * 0.1;
		motor[motorsLeft] = MOTOR_SPEED;
	}
	else if(CLIVE < distance - ERROR) {
		//drift left
		motor[motorsRight] = MOTOR_SPEED;
		motor[motorsLeft] = MOTOR_SPEED * 0.1;
	}
	else {
		//straight ahead
		motor[motorsRight] = MOTOR_SPEED;
		motor[motorsLeft] = MOTOR_SPEED;
	}
}*/

int readIRSector() {
	return HTIRS2readACDir(HTIRS2);
}
void initAutonomous() {
	tHTIRS2DSPMode _mode = DSP_1200;
	StartTask(getHeading);
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

// Current heading of the robot
float currHeading = 0;
int samples = 0;
int finalSamples = 0;

// Task to keep track of the current heading using the HT Gyro
task getHeading () {
	float delTime = 0;
	float prevHeading = 0;
	float curRate = 0;
	nSchedulePriority = kHighPriority;
  HTGYROstartCal(gyro);
  PlaySound(soundBeepBeep);
  while (true) {
    time1[T1] = 0;
    curRate = HTGYROreadRot(gyro);
    samples ++;
    if (abs(curRate) > 3) {
      prevHeading = currHeading;
      currHeading = prevHeading + curRate * delTime;
      if (currHeading > 360) currHeading -= 360;
      else if (currHeading < 0) currHeading += 360;
    }
    wait1Msec(5);
    delTime = ((float)time1[T1]) / 1000;
    //delTime /= 1000;
  }
}

void turnWithGyro(int speed, float degrees) {
	move(0);
	HTGYROstartCal(gyro);
	pause(1);
	samples = 0;
	if(speed > 0) {
		currHeading = 0;
		while(currHeading < degrees) {
				turn(speed);
		}
	}
	else {
		currHeading = 359;
		while(currHeading > 360 - degrees) {
				turn(speed);
		}
	}
	finalSamples = samples;
	move(0);
}

void pause(float seconds) {
	wait1Msec(seconds * 1000);
}

bool selectQueue() {
	bool queue = false;
	ClearTimer(T1);
	while(true) {
			nxtDisplayCenteredTextLine(1, "Select start");
			if(queue)
				nxtDisplayCenteredTextLine(2, "Queue");
			else
				nxtDisplayCenteredTextLine(2, "Align");

			if (time1[T1] > 300) {
    		if (nNxtButtonPressed == 1)       queue = !queue;
    		else if (nNxtButtonPressed == 2)  queue = !queue;
  			else if (nNxtButtonPressed == 3)  break;

  		if (nNxtButtonPressed != -1) {
    		// if any buttons were pressed, play sound and wait
      	PlaySound(soundBlip);
     	 	ClearTimer(T1);
    	}
    }
	}
	pause(0.3);
	return queue;
}

bool selectLine() {
	bool second = false;
	ClearTimer(T1);
	while(true) {
			nxtDisplayCenteredTextLine(1, "Select end");
			if(second)
				nxtDisplayCenteredTextLine(2, "Second line");
			else
				nxtDisplayCenteredTextLine(2, "First line");

			if (time1[T1] > 300) {
    		if (nNxtButtonPressed == 1)       second = !second;
    		else if (nNxtButtonPressed == 2)  second = !second;
  			else if (nNxtButtonPressed == 3)  break;

  		if (nNxtButtonPressed != -1) {
    		// if any buttons were pressed, play sound and wait
      	PlaySound(soundBlip);
     	 	ClearTimer(T1);
    	}
    }
	}
	pause(0.3);
	return second;
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
