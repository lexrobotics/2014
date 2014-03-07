#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S3,     gyro,           sensorI2CCustom)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CCustom9V)
#pragma config(Motor,  motorA,          gun,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorsRight,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorsLeft,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     frontLift,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     backLift,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     dualWheels,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    singleWheel,          tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_2,    rampTilt,             tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    flagExtender,         tServoContinuousRotation)
//(above for testing only)


typedef struct {
	const int doesntmatter=10;
} Chassis;


Chassis* move(Chassis* self,int speed) {
	motor[motorsLeft] = speed;
	motor[motorsRight] = speed;
	return self;
}

Chassis* turn(Chassis* self,int speed) {
	motor[motorsLeft] = speed;
	motor[motorsRight] = -1 * speed;
	return self;
}

Chassis* initChassis(motorsLeft,motorsRight)
{
    Chassis *c = (PString*)malloc(sizeof(PString));
    return c;
}
int main()
{
  PString *p=initializeString(30);
  strcpy(p->chars,"Hello");
  printf("\n%d",p->length(p));
 return 0;
}
