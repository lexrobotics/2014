#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorRight,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

	#include "JoystickDriver.c"  //include this library to use controller methods

task main()
{
	getJoystickSettings(joystick); //store controller input in joystick struct (joystick automatically exists, no need to create it)
	static float MOTOR_SCALE = 200.0/256.0;


		motor[motorRight] = 0;
		motor[motorLeft] = 0;
		servo[servo1] = 127;


	while(true){
		if(abs(joystick.joy1_y1) > 10){
			motor[motorLeft] = -1 * joystick.joy1_y1*MOTOR_SCALE;
		}
		else
		{
			motor[motorLeft] = 0;
		}
	if(abs(joystick.joy1_y2) > 10){
			motor[motorRight] = -1 * joystick.joy1_y2*MOTOR_SCALE;
		}
		else
		{
			motor[motorRight] = 0;
		}

		// make the servo do the thing
		if(joy1Btn(03) == 1)
		{
			servo[servo1] = 256;
		}
		else if (joy1Btn(01) == 1)
		{
			servo[servo1] = 0;
		}
		else
			servo[servo1] = 127;



	}
}
