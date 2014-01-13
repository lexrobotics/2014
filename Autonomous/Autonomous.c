#include "Autonomous.h"
#include "drivers/hitechnic-irseeker-v2.h"

//TODO: remeasure
const float DIAMETER = 4.0; //diameter of wheel in inches
const float ENCODER_SCALE = 1440.0; //number of encoder counts per rotation
const float CIRCUMFERENCE = DIAMETER * PI;
const float TURN_RADIUS = 11.02; //center of robot to turning circle in inches
const float TURN_CIRCUMFERENCE = 2.0 * TURN_RADIUS * PI; //circumference of circle robot turns in
const float TURN_SCALAR = 1.2; //because it's not a square

void initAutonomous()
{
	tHTIRS2DSPMode _mode = DSP_1200;
	/*nMotorPIDSpeedCtrl[motorsRight] = mtrSpeedReg; //enable PID on all the motors
	  nMotorPIDSpeedCtrl[motorsLeft] = mtrSpeedReg;
	  nMotorPIDSpeedCtrl[motorRightFront] = mtrSpeedReg;
	  nMotorPIDSpeedCtrl[motorRightBack] = mtrSpeedReg;*/
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

	move(speed); //move at desired speed

	while(abs(nMotorEncoder[motorsLeft]) < abs(target)  //wait until position reached
		&& abs(nMotorEncoder[motorsRight]) < abs(target));

	move(0); //stop
}

void turnDistance(int speed, int angle) {
	int target = degreesToEncoder(angle);
	resetEncoders();

	turn(speed); //turn at desired speed

	while(abs(nMotorEncoder[motorsLeft]) < abs(target)  //wait until position reached
		&& abs(nMotorEncoder[motorsRight]) < abs(target));

	turn(0); //stop
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
