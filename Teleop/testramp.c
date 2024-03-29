#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     HTIRS2,  sensorI2CCustom)
#pragma config(Sensor, S3,     gyro,           sensorAnalogInactive)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CCustom9V)
#pragma config(Motor,  motorA,          gun,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorsRight,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorsLeft,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     bottomLift,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     topLift,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     dualWheels,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    singleWheel,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_2,    rampTilt,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    liftLock,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    flagExtender,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)

task main()
{
	while(true) {
		for(int i=0; i<255; i++) {
			servo[rampTilt] = i;
			wait10Msec(5);
		}
		for(int i=255; i>=0; i--) {
			servo[rampTilt] = i;
			wait10Msec(5);
		}
	}
}
