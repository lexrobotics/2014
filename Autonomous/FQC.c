#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S3,     gyro,           sensorI2CCustom)
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
#include "JoystickDriver.c"

/* AutonomousRoutine.c
   Final layer of abstraction
   Uses paths from Paths.c and options from Autonomous.c
   to make routines based on our different inputs
*/

task main() {

    int initDelay = selectDelay();
    /*
    bool queue = selectBool("Should queue", "Queue", "Align");
    bool reverseOntoRamp = selectBool("Approach ramp", "Beginning", "End");
    bool reverse = selectBool("Should reverse", "Reverse", "Forwards");
    */
    bool queue = true;
    bool	reverseOntoRamp = true;
    bool	reverseStart = false;

	initAutonomous(); //call initialization function
	waitForStart();	//wait for start from FCS
	pause(initDelay);

	if(reverseStart) {
		reverseQueue(); // if we reverse, we queue, no reason to do anyting else
	}
	else if(queue){
		forwardQueue();
	}
	else {
		lineUp();
	}

	StartTask(ejectFlag);

	int currentPos = 0;
	if(!reverseStart) {
		currentPos = driveUp();
		if(!reverseOntoRamp) {
			endOfRamp(currentPos);
		}
		else {
			beginningOfRamp(currentPos);
		}
	}
	else {
		currentPos = reverseDriveUp();
		if(!reverseOntoRamp) {
			reverseEndOfRamp(currentPos);
		}
		else {
			reverseBeginningOfRamp(currentPos);
		}
	}

	if(reverseStart==reverseOntoRamp) {//on the same side of the ramp
		forwardRamp();
		turnAndPark();
	}
	else {
		reverseRamp();
		turnAndPark();
	}
}
