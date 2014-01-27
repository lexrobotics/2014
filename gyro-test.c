#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S2,     gyro,           sensorAnalogInactive)
#pragma config(Sensor, S4,     sonarSensor,    sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     motorsRight,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorsLeft,    tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "drivers/hitechnic-gyro.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "Autonomous/Autonomous.c"

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
	currHeading = 0;
	while(currHeading < degrees) {
			turn(speed);
			nxtDisplayCenteredTextLine(2, "%f/%d", currHeading, degrees);
	}
	finalSamples = samples;
	move(0);
}

task main()
{
	StartTask(getHeading);
	wait10Msec(100);
	turnWithGyro(20, 90);
	pause(5);
	moveDistance(50, 72);
	move(0);
/*	nxtDisplayCenteredTextLine(1, "%d", finalSamples);
	while(true) {
		nxtDisplayCenteredTextLine(2, "%f", currHeading);
	}
	while(true) {
		turnWithGyro(20, 84.5);
		pause(0.2);
		moveDistance(50, 24);
		pause(0.2);
	}*/
}
