#pragma config(Hubs,  S3, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S3_C1_1,     FrontLeftWheel, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S3_C1_2,     FrontRightWheel, tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_1,     BackRightWheel, tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_2,     BackLeftWheel, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
task main()
{
	int threshold=25;
	while(true)
	{
		int  right_flag =0;
		int left_flag=0;

		if(abs(joystick.joy1_y1)>threshold)
		{
			//motor[FrontRightWheel] = joystick.joy1_y1 * (100.0/128.0);
			motor[BackRightWheel] = joystick.joy1_y1 * (100.0/128.0);
			right_flag=1;
		}

		if(abs(joystick.joy1_y2)>threshold)
		{
			//motor[FrontLeftWheel] = joystick.joy1_y2 * (100.0/128.0);
			motor[BackLeftWheel] = joystick.joy1_y2 * (100.0/128.0);
			left_flag=1;
		}

		if(left_flag==0)
		{
			//motor[FrontLeftWheel] =0;
			motor[BackLeftWheel]=0;
		}
		if(right_flag==0)
		{
			//motor[FrontRightWheel]=0;
			motor[BackRightWheel]=0;
		}
}
}