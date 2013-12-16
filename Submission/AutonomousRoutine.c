#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CCustom9V)
#pragma config(Motor,  motorA,          gun,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorsRight,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorsLeft,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     frontLift,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     backLift,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     dualWheels,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    singleWheel,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_2,    rampTilt,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    flagExtender,         tServoContinuousRotation)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Autonomous.c"
#include "Paths.c"

/* AutonomousRoutine.c
   Final layer of abstraction
   Uses paths from Paths.c and options from Autonomous.c
   to make routines based on our different inputs
*/

task main() {

    int initDelay = selectDelay();
    bool queue = selectBoolean("Should queue", "Queue", "Align");
    bool reverseOntoRamp = selectBoolean("Approach ramp", "Beginning", "End");
    bool reverse = selectBoolean("Should reverse", "Reverse", "Forwards");

	initAutonomous(); //call initialization function
	waitForStart();	//wait for start from FCS
	pause(initDelay);

	if(reverse) {
		reverseQueue(); // if we reverse, we queue, no reason to do anyting else
	}
	else if(queue && !reverse){
		forwardQueue();
	}
	else {
		lineUp();
	}

	int currentPos = 0;
	if(!reverse) {
		currentPos = driveUp();
	}
	else {
		currentPos = reverseDriveUp();
	}

	if(!reverse) {
		if(!reverseOntoRamp) {
			endOfRamp(currentPos);
		}
		else {
			beginningOfRamp(currentPos);
		}
	}
	else {
		if(!reverseOntoRamp) {
			reverseEndOfRamp(currentPos):
		}
		else {
			reverseBeginningOfRamp(currentPos):
		}
	}

	if((!reverse && !reverseOntoRamp) || (reverse && reverseOntoRamp)) {
		forwardRamp();
		turnAndPark();
	}
	else {
		reverseRamp();
		reverseTurnAndPark();
	}
}
