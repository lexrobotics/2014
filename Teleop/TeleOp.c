#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     gyro,           sensorAnalogInactive)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  motorA,          gun,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorsRight,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorsLeft,    tmotorTetrix, openLoop, reversed)
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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c" //library with joystick controls

static float MOTOR_SCALE = 200.0/256.0; //since joystick values range from -128 to 127 and motors from -100 to 100, we need to scale values from the joystick

void initialize() {
        servo[rampTilt] = 127;
        servo[singleWheel] = 127;
}

/*
This is the task where we define all servo/"arm" movements.
By separating the arm and drive tasks, it lets us logically separate our code, and run each one in parallel.
e.g. you can raise your arm while driving at the same time
Although technically you could just paste it all into main() and it would still work
*/
task arm() {
        while(true){
                getJoystickSettings(joystick); //grab snapshot of controller positions


                /******JOYSTICK 1*******/

                //WHEELS
                /*
                Shorthand for both dualWheels and singleWheel
                (both continous rotation)

                                dualWheels:                singleWheel:
                1 - spit-out                        spit-out
                6 - suck-in                                suck-in
                8 - turn off                        suck-in
                7 -                                                         turn off

                Noah: the singleWheel now spins inward on its own unless stopped
                */
                if(joy1Btn(1)) { //bring in or shoot out blocks by spinning dualWheels and singleWheel together
                        motor[dualWheels] = -40;
                        servo[singleWheel] = 240;
                }
                else if(joy1Btn(6)) {
                        motor[dualWheels] = 50;
                        servo[singleWheel] = 10;
                }
                else if(joy1Btn(8)) {
                        motor[dualWheels] = 0;
                        servo[singleWheel] = 10;
                }
                else if(joy1Btn(3)) {
                        motor[dualWheels] = -40;
                        servo[singleWheel] = 10;
                }
                else if(joy1Btn(7))
                        servo[singleWheel] = 127;

                if(joy1Btn(5)//a driver triggered quick block disterber
                {
                				//motor[dualwheels] = -100qq;
                }
                else
            						motor[dualWheels] = 0;

                //TILTS
                /*
                rampTilt - 180-deg servo
                Controls ramp angle with that servo
                joy1 Y button (4) press+hold raises it (ignore the 00 01 02 03 in Joystick Control)
                joy1 A button (2) press+hold lowers it
                */
                if(joy1Btn(4))
                        servo[rampTilt] = 127 + 64;
                else if(joy1Btn(2))
                        servo[rampTilt] = 127 - 64;
                else
                        servo[rampTilt] = 127;

                /*
                singleWheelTilt - 180-deg servo
                Separates the singleWheel from the ramp to dump cubes
                joy1 tophat up (0) press+hold raises it\
                joy1 tophat down (4) press+hold lowers it
                */
                if (joystick.joy1_TopHat == 4) {
                        servo[rampTilt] = 127 + 64;
                }
                else if (joystick.joy1_TopHat == 0) {

                        servo[rampTilt] = 127 - 64;
                }



                /******JOYSTICK 2*******/

                /*
                flagMotor - motor
                Spin dat flag using joy2's buttons 2 and 4
                joy2 A button (2) - wind up
                joy2 Y button (4) - wind down
                */
                if(joy2Btn(2))
                        motor[flagMotor] = 100;
                else if(joy2Btn(4))
                        motor[flagMotor] = -100;
                else if (joystick.joy2_TopHat == 0){
                        motor[flagMotor] = 20;
                }
                else if (joystick.joy2_TopHat == 4){
                        motor[flagMotor] = -20;
                }
                else
                        motor[flagMotor] = 0;

                /*
                flagExtender - continuous servo
                Move dat flag raiser using joy2's buttons 1 and 3
                joy2 X button (1) - flag raiser in
                joy2 B button (3) - flag raiser out
                */
                if(joy2Btn(1))
                        servo[flagExtender] = 255;
                else if(joy2Btn(3))
                        servo[flagExtender] = 0;
                else
                        servo[flagExtender]  = 127;

                /*
                frontLift - motor
                Lifts the ramp level
                Left upper trigger raises
                Left lower trigger lowers
                */
                if(joy2Btn(7)) //controls lift1 using joy2's left triggers
                        motor[frontLift] = 100;
                else if(joy2Btn(5))
                        motor[frontLift] = -100;
                else
                        motor[frontLift] = 0;

                /*
                lift2 - motor
                Lifts the hook level
                Right upper trigger raises
                Right lower trigger lowers
                */
                if(joy2Btn(8)) //controls lift2 using joy2's right triggers
                        motor[backLift] = 100;
                else if(joy2Btn(6))
                        motor[backLift] = -100;
                else
                        motor[backLift] = 0;
        } //while(true) arm
} //task arm()

task main() {
        /****************INITIALIZE TeleOp*****************/
        //Initialize robot actuators
        initialize();
        //Wait until receive relevant signal for start of tele-op phase
        waitForStart();
        /*******************BEGIN PROCESSES****************/
        StartTask(arm); //parallel 'arm' task
        //ClearTimer(T1); //I think this was for loss-of-connection detection, but the other code doesn't exist here anymore

        //Process for driving.
        while(true) {
                getJoystickSettings(joystick); //grab snapshot of controller positions to 'joystick' 'object'
                //Joysticks don't settle to zero, so each axis zeroed if within 10 of zero
                //Copy this for each joystick x/y direction used, or drift will happen
                if(abs(joystick.joy1_y1) < 10)
                        joystick.joy1_y1 = 0;
                if(abs(joystick.joy1_y2) < 10)
                        joystick.joy1_y2 = 0;

                writeDebugStreamLine("%d %d",joystick.joy1_y1,joystick.joy1_y2);

                int j1 = MOTOR_SCALE * joystick.joy1_y1;
                int j2 = MOTOR_SCALE * joystick.joy1_y2;

                motor[motorsLeft] = j1; //powerLeft
                motor[motorsRight] = j2; //powerRight
        } //while(true) driving
} //task arm()
