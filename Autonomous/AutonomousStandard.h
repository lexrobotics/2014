
/*
* Autonomous.h
* Two Bits and a Byte
*/

/*
* Static & Global Variables
*/
static float pi = PI;//Experimentally determined to be more correct.
static float wheelRadius = 2; // radius of the wheel in INCHES; 4-inch diameter wheels
static float distanceScale = PI * 2.0 * wheelRadius; //inches traveled per rotation
static float encoderScale = 1440;//1440 encoder counts per rotation
static float wheelRectWidth=13.50;//Width of rectangle formed by wheels (INCHES)
static float wheelRectLength=10.00;//Length of rectangle formed by wheels (INCHES)
static float wheelRectDiag=sqrt(wheelRectWidth*wheelRectWidth+wheelRectLength*wheelRectLength);//Diagonal of rectangle formed by wheels
static float turnCircumference = wheelRectDiag * pi;//Circumference of circle traced by wheels of turning robot
// end Static Variables section

/*
* Function Prototypes
*/

void turn(float speed);
void turnDistance(float speed, int degrees); //speed: -100 to 100, degrees: degrees to turn
void move(float speed);
void moveDistance(float speed, float distance); //speed: -100 (backwards) to 100 (forwards), distance: distance to travel in CM
void pause(float seconds);
void resetEncoders();
void initAutonomous();

#include "drivers/hitechnic-irseeker-v2.h"

// end Function Prototype section

void initAutonomous(){
	tHTIRS2DSPMode _mode = DSP_1200;
	//Enable PID on all the motors
	//nMotorPIDSpeedCtrl[motorsRight] = mtrSpeedReg;
	//nMotorPIDSpeedCtrl[motorsLeft] = mtrSpeedReg;
	//nMotorPIDSpeedCtrl[motorRightFront] = mtrSpeedReg;
	//nMotorPIDSpeedCtrl[motorRightBack] = mtrSpeedReg;
	servo[harvestLifter] = 127;
}


//It's easy, just make sure it's in the *right orientation*.
bool rampIsClear(){
	const int distanceToCheckCM=20*2.54;//inches to cm
	return SensorValue[sonarSensor]>distanceToCheckCM;
}


void turn(float speed){
	motor[motorsLeft] = speed;
	motor[motorsRight] = -speed;
}

void turnDistance(float speed, int degrees){
	//degrees*=87/90;//Experimentally determined error
  float encoderTarget = (((degrees/360.0)*turnCircumference*wheelRectDiag/wheelRectLength)/distanceScale)*encoderScale;

  resetEncoders(); // make sure no overflow (-65536,65535)

	motor[motorsLeft] = speed;
	motor[motorsRight] = -speed;

	if(speed>0)
		while(nMotorEncoder[motorsRight]>-1*encoderTarget || nMotorEncoder[motorsLeft]<encoderTarget){}
	else
		while(nMotorEncoder[motorsRight]<encoderTarget || nMotorEncoder[motorsLeft]>-1*encoderTarget){}

	motor[motorsLeft] = 0;
	motor[motorsRight] = 0;
}

void move(float speed){
	motor[motorsLeft] = speed;
	motor[motorsRight] = speed*1.1;//lol experimentally determined or something
}

void moveDistance(float speed, float distance){
	resetEncoders();
	float encoderTarget = encoderScale*distance/distanceScale;
	//encoderTarget = encoderTarget/3;

	motor[motorsLeft] = speed;
	motor[motorsRight] = speed;

	if(speed<0)
		while(/*nMotorEncoder[motorsRight]-currentPosRight>-1*encoderTarget &&*/ nMotorEncoder[motorsLeft]>-1*encoderTarget)
						nxtDisplayCenteredTextLine(3, "%d, %d", nMotorEncoder[motorsLeft], nMotorEncoder[motorsRight]);
	else
		while(/*nMotorEncoder[motorsRight]-currentPosRight<(encoderTarget) &&*/ nMotorEncoder[motorsLeft]<(encoderTarget))
			nxtDisplayCenteredTextLine(3, "%d, %d", nMotorEncoder[motorsLeft], nMotorEncoder[motorsRight]);

	motor[motorsLeft] = 0;
	motor[motorsRight] = 0;
}

int inchesToEncoder(float inches) {
	float encoderTarget = encoderScale*inches/distanceScale;
	return encoderTarget;
}
void pause(float seconds){
	wait1Msec(seconds*1000);
}

void resetEncoders(){
	nMotorEncoder[motorsLeft] = 0;
	nMotorEncoder[motorsRight] = 0;
}
