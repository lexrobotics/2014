#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     gyro,           sensorAnalogInactive)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  motorA,          gun,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     dualWheels,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorsLeft,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     lift1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     lift2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    singleWheelTilt,      tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_2,    rampTilt,             tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_3,    flagExtender,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    singleWheel,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_5,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servonone,                  tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "Autonomous.c"

const int MOTOR_SPEED = -1*BASE_MOTOR_SPEED;
const int MOTOR_SPEED_SLOW = -1*BASE_MOTOR_SPEED_SLOW;
const int SHORT_WAIT = 0.2;
const int LONG_WAIT = 0.5;

task main() {
  /*
  int initDelay = selectDelay();
  bool shouldQueue = selectQueue();
  bool shouldTakeSecondLine = selectLine();
	*/
	initAutonomous(); //call initialization function
	//waitForStart();	//wait for start from FCS (DNC!!)
	//pause(initDelay);
	bool shouldQueue = false; //huckin fooligasm

	if(shouldQueue) {
		moveDistance(MOTOR_SPEED_SLOW, 5);
		pause(SHORT_WAIT);
		turnWithGyro(-1*MOTOR_SPEED, 90);
		moveDistance(MOTOR_SPEED_SLOW, 25);
		turnWithGyro(MOTOR_SPEED, 38);
	}

	resetEncoders();
	//move slowly until IR is detected or passed ramp
	move(MOTOR_SPEED_SLOW);
	while(readIRSector()!= 5 && nMotorEncoder[motorsRight] < inchesToEncoder(65))
		;
	move(0);
	pause(SHORT_WAIT);

	//based on position, move the extra distance we need
  int currentPos = nMotorEncoder[motorsRight];
  if(inchesToEncoder(35) < nMotorEncoder[motorsRight]) {
  	//beyond center
  	moveDistance(MOTOR_SPEED_SLOW, 2);
  }
  else {
  	//behind center
  	moveDistance(MOTOR_SPEED_SLOW, 5);
  }
 	pause(SHORT_WAIT);

 	//shoot block!
 	motor[gun] = -100;

 	/**************************************************************************
 	 *DARK MAGIC DO NOT CHANGE!!                                              *
 	 *WARNING - IF VALUE OF 0.1 IS CHANGED, THE PROGRAM CEASES TO WORK.       *
 	 *THIS VALUE USES DARK MAGIG AND IS PIVOTAL TO PROPER AUTONOMOUS FUNCTION.*
 	 *IF YOU CHANGE THIS VALUE, I WILL KILL YOU                               *
 	 *(AND YOUR FAMILY)                                                       *
 	 **************************************************************************/
  pause(0.1);
  /*
  	DO NOT CHANGE ABOVE ARGUMENT!!
  	MUST BE 0.1!!
  */

  motor[gun] = 0;

  //drive to end of ramp
  resetEncoders();
  pause(LONG_WAIT);
  move(MOTOR_SPEED);
  while(abs(nMotorEncoder[motorsRight] + currentPos) < inchesToEncoder(60))
  	;
  move(0);

  //line up with ramp
  pause(SHORT_WAIT);
 	turnWithGyro(MOTOR_SPEED, 45);
  moveDistance(MOTOR_SPEED, 8);
  pause(SHORT_WAIT);
  turnWithGyro(MOTOR_SPEED, 40);
  moveDistance(-100, 30);
  pause(SHORT_WAIT);

  //turn and park
  turnWithGyro(MOTOR_SPEED, 90);
  moveDistance(100, 40);
}
