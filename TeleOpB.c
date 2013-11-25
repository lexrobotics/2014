

 /*
	* TeleOpB.c
	* 2 Bits and a Byte [Team 4029]
	*
	* Last edited by: Noah Moroze, 5/28
	* Notes: I modified TeleOpBotside.c to create this general TeleOp program, which will serve as a learning template/reference for our programmers.
	*
	* CONFIGURATION
	* - 1: Motor Controller 1 - Servo Controller 1
	* 	- Motor Controller 1:
	*		- M1: Right side drive wheels (with encoder)
	*		- M2: Left side drive wheels (with encoder)
	*	- Servo Controller 1:
	*		- S1: Arm shoulder (standard)
	*		- S2: Arm pivot (continuous)
	* - 2: <item plugged into port 2>
	* - 3: <item plugged into port 3>
	* - 4: <item plugged into port 4>
	*
	* CONTROLS
	* - Controller 1:
	*	- Left and Right Sticks up/down: drive (tank style)
	*	- Holding down 1 + top hat: precision drive
	* - Controller 2:
	*	- Buttons 1/3: Pivot arm left/right
	* 	- Buttons 2/4: Bend arm up/down
*/

#include "JoystickDriver.c"  //library with joystick control methods

//static speed of robot in precision mode
static int TOP_HAT_FWDBACK_SPEED = 20;
static int TOP_HAT_TURN_SPEED = 20;

static float MOTOR_SCALE = 200.0/256.0; //since joystick values range from -128 to 127 and motors from -100 to 100, we need to scale values from the joystick

void initializeRobot()
{
	//These 3 lines set up PID control for the drive motors (using encoders)
	nPidUpdateInterval = 8;
	nMotorPIDSpeedCtrl[motorsLeft] = mtrSpeedReg; //Copy this line (with motor name changed) for each motor you set up with an encoder
	nMotorPIDSpeedCtrl[motorsRight] = mtrSpeedReg;

	//define starting position for servos here
}

//This is the task where we define all servo/"arm" movements.
//By separating the arm and drive tasks, it lets us logically separate our code, and run each one in parallel.
//e.g. you can raise your arm while driving at the same time
task arm() {
	//define servo-position related variables here

	while(true){
		getJoystickSettings(joystick); //grab snapshot of controller positions

		if(joy1Btn(6)) {
			//actuate wheel thingies
		}
		else if(joy1Btn(8)) {
			//wheel thingies reverse
		}
		else
			//stop wheel thingie

		if(joy2Btn(6)) {
			//lower level up
		}
		else(joy2Btn(8)) {
			//lower level down
		}
		else
			//lower level stop

		if(joy2Btn(5)) {
			//upper level up
		}
		else if(joy2Btn(7)) {
			//upper level down
		}
		else

		if(joy2Btn(1)) {
			//release trigger
		}
		else if(joy2Btn(3)) {
			//reengage trigger
		}

		if(joy1Btn(3)) {
			//take a spazz for a couple seconds
		}
	}
}

task main() {
	//variables for motor power that we can modify before feeding to motors
	int powerRight = 0;
	int powerLeft = 0;

	writeDebugStreamLine("");
	writeDebugStreamLine("TELEOP");

	// Initialize robot actuators
	initializeRobot();
	writeDebugStreamLine("Initialized");

	// Wait for start of tele-op phase
	waitForStart();
	writeDebugStreamLine("Begin!");

	StartTask(arm); //start running "arm" task in parallel
	ClearTimer(T1);

	while(true) {
		getJoystickSettings(joystick); //grab snapshot of controller positions

		if (joy1Btn(1))
		{
			powerLeft = 0;
			powerRight = 0;

			if (joystick.joy1_TopHat == 0) {  // forward
				powerLeft = TOP_HAT_FWDBACK_SPEED;
				powerRight = TOP_HAT_FWDBACK_SPEED;
			}
			else if (joystick.joy1_TopHat == 4) { // backward
				powerLeft = -1 * TOP_HAT_FWDBACK_SPEED;
				powerRight = -1 * TOP_HAT_FWDBACK_SPEED;
			}
			else if (joystick.joy1_TopHat == 2) { // right
				powerLeft = TOP_HAT_TURN_SPEED;
				powerRight = -1 * TOP_HAT_TURN_SPEED;
			}
			else if (joystick.joy1_TopHat == 6) { // left
				powerLeft = -1 * TOP_HAT_TURN_SPEED;
				powerRight = TOP_HAT_TURN_SPEED;
			}
		}
		else
		{
			//Since joysticks rarely settle to zero, this makes sure each axis is reset to 0 even if it's within 10 from zero
			//Be sure to copy one of these statements for each joystick you use
			if(abs(joystick.joy1_y1) < 10)
				joystick.joy1_y1 = 0;
			if(abs(joystick.joy1_y2) < 10)
				joystick.joy1_y2 = 0;

			powerRight = MOTOR_SCALE*joystick.joy1_y2;
			powerLeft = MOTOR_SCALE*joystick.joy1_y1;
		}

		motor[motorsRight] = powerRight;
		motor[motorsLeft] = powerLeft;
	}
}
