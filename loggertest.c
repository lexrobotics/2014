#pragma config(Motor,  motorB,          right,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          left,          tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Logger.c"

task main()
{
	ClearTimer(T2);
	StartTask(Logger);
	addToLogWithTime("123456789012345678901234567890");
	wait1Msec(1000);
	stopLogger();
	wait1Msec(1000);
}
