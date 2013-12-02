#pragma config(Hubs,  S1, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C2_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Tests a Tetrix motor in port 1 of the second controller on S1

task main() {
	while(true) {
			motor[motorD] = 100; //motor forward for half second
			wait1Msec(500);
			motor[motorD] = 0; //motor neutral for half second
			wait1Msec(500);
			motor[motorD] = -100; //motor backward for half second
			wait1Msec(500);
			motor[motorD] = 0; //motor neutral for half second
			wait1Msec(500);
	}
}