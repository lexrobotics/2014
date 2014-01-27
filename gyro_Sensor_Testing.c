#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S3,     gyroPort,       sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  motorA,          gun,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     dualWheels,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorsRight,   tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     motorsLeft,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     lift1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     flagMotor,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     lift2,         tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    singleWheelTilt,      tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_2,    rampTilt,             tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_3,    flagExtender,         tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C4_4,    servoasdf,            tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    singleWheel,          tServoContinuousRotation)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void turnRightForGyroAndStop(int power,int gyroDist)
{
	motor[motorsRight] = power;
	motor[motorsLeft] = -power;
	float gyroVal = 0;
	float gyroOff = 0;
	bool running = true;
	bool returning = false;
	while (running) {
		float deltaGyro = (float)(abs(SensorValue[gyroPort]-gyroOff) < 2 ? 0 : (SensorValue[gyroPort]-gyroOff))/200.0;
		gyroVal += deltaGyro;
		if (abs(gyroVal) > abs(gyroDist)){
			returning = true;
		}
		if (returning){
			motor[motorsRight] = -power/4;
			motor[motorsLeft] = power/4;
			if (abs(gyroVal) < abs(gyroDist)){
				running = false;
				writeDebugStreamLine("Final GyroVal: %f",gyroVal);
			}
		}
	}
	wait1Msec(5);
}

task main()
{
	turnRightForGyroAndStop(-200, 90);
	motor[motorsRight] = 0;
	motor[motorsLeft] = 0;
}