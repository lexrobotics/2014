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


//This file should theoretically work, but who knows what ROBOTC has in store?
//(not yet tested with ROBOTC)

/*
//The code which worked on ideone.com:

#include <stdio.h>

struct Chassis_s;
typedef struct Chassis_s Chassis;

struct Chassis_s{
	char* name;
	Chassis (*move)(Chassis, int);
	Chassis (*turn)(Chassis, int);
};

Chassis Chassis_move(Chassis self,int speed) {
	printf("%s: I'z a movin' at speed %d.\n",self.name,speed);
	return self;
}

Chassis Chassis_turn(Chassis self,int speed) {
	printf("%s: I'z a turnin' at speed %d.\n",self.name,speed);
	return self;
}

Chassis initChassis(char* name)
{
    Chassis c;
    c.name=name;
    c.move=&Chassis_move;
    c.turn=&Chassis_turn;
    return c;
}
int main()
{
	Chassis oink=initChassis("asdf");
	oink.move(oink,10).turn(oink,100);
	return 0;
}

*/


struct Chassis_s;
typedef struct Chassis_s Chassis;
struct Chassis_s{
	tMotor motorsLeft, motorsRight;
	Chassis (*move)(Chassis, int);
	Chassis (*turn)(Chassis, int);
	Chassis (*stop)(Chassis, int);
	Chassis (*msec)(Chassis, int);
	Chassis (*moveDistSpeed)(Chassis, int);
	Chassis (*turnDegSpeed)(Chassis, int);
	int locationX, locationY; //This can be computed every time around.
};

Chassis Chassis_move(Chassis self,int speed) {
	//printf("%s: I'z a movin' at speed %d.\n",self.name,speed);
	self.motorsLeft=speed;
	self.motorsRight=speed;
	return self;
}

Chassis Chassis_turn(Chassis self,int speed) {
	//printf("%s: I'z a turnin' at speed %d.\n",self.name,speed);
	self.motorsLeft=speed;
	self.motorsRight=-speed;
	return self;
}

Chassis Chassis_stop(Chassis self){
	self.motorsLeft=0;
	self.motorsRight=0;
	return self;
}

Chassis Chassis_msec(Chassis self,int time) {
	wait1MSec(time);
	return self;
}

Chassis Chassis_moveDistSpeed(Chassis self, int distance, int speed){//(forward)
	self.move(self,speed).msec(self,1000).stop(self);//this is placeholder
	//use stuff with encoders here
	return self;
}
Chassis Chassis_turnDegSpeed(Chassis self, int deg, int speed){//(Counterclockwise, like math)
	self.turn(self,speed).msec(self,1000).stop(self);//this is placeholder
	//use stuff with encoders and gyro/compass here
	return self;
}

Chassis initChassis(tMotor& motorsLeft, tMotor& motorsRight)
{
    Chassis c;
    c.motorsLeft=motorsLeft;
	c.motorsRight=motorsRight;
    c.move=&Chassis_move;
    c.turn=&Chassis_turn;
	c.stop=&Chassis_stop;
	c.msec=&Chassis_msec;
	c.moveDistSpeed=&Chassis_moveDistSpeed;
	c.turnDegSpeed=&Chassis_turnDegSpeed;
    return c;
}
int main()
{
	Chassis bot=initChassis(motor[motorsLeft],motor[motorsRight]);//Initialization: pass motors to itself.
	bot.moveDistSpeed(bot,100,100);
	return 0;
}


