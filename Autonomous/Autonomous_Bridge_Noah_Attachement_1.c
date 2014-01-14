#pragma config(Hubs,  S1, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          armNoah,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorsRight,   tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorsLeft,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "AutonomousStandard.h"

task main(){
		initAutonomous();
		moveDistance(20, 22);//distance was 24
		pause(0.5);
		motor[armNoah]=100;
		pause(0.4);
		motor[armNoah]=0;
		pause(1.0);
		moveDistance(20, 18);//distance was 24
		pause(0.5);
		turnDistance(-20, 90);
		pause(0.5);
		moveDistance(20, 30);
	}