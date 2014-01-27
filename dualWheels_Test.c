#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  motorA,          gun,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     dualWheels,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorsLeft,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     lift1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     lift2,				 tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    singleWheelTilt,      tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_2,    rampTilt,             tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_3,    flagExtender,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    servoasdf,            tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    singleWheel,         	tServoContinuousRotation)

task main()
{
	while(true)
	{
		nxtDisplayClearTextLine(2);//displays text "D-Wheel Tester" on NXT
		nxtDisplayCenteredTextLine(3, "D-Wheel Tester");

		if(nNxtButtonPressed == 1)
		{
			motor[dualWheels] = 100;
			servo[singleWheel] = 50;
		}
		else if(nNxtButtonPressed  == 2)
		{
			motor[dualWheels] = -60;
			servo[singleWheel]  = 240;
		}
		else if(nNxtButtonPressed == 3)
		{
			motor[dualWheels] = 0;
			servo[singleWheel] = 127;
		}
	}


}
