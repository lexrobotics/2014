#pragma config(Hubs,  S3, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S3_C1_1,     FrontLeftWheel, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S3_C1_2,     FrontRightWheel, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     BackLeftWheel, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_2,     BackRightWheel, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_6,    servo6,               tServoNone)
#include "JoystickDriver.c"
task main()
{
	while(true)
{
	if(joystick.joy1_y1>0)
{
	motor[BackLeftWheel]=100;
	motor[BackRightWheel]=100;
}
}

}
