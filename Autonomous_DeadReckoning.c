#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorsRight,   tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     pulleyMotor,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     hangingMotor,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorsLeft,    tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     harvestMotor,  tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    gun,                  tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    flagExtender,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_3,    harvestLifter,        tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "AutonomousStandard.h"

task main(){
	servo[gun] = 0;
	pause(1);
	servo[gun] = 255;
	pause(1);

}
