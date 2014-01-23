#ifndef LIGHTS_H
#define LIGHTS_H

/* Turns the wheels on only one side of the robot
 * The robot will drift in the other direction
 * Defined for both sides
 */
void driftLeft(int speed);
void driftRight(int speed);

// Starts up the light sensors
void lightsCameraAction();

/* Drifts along the line
 * OLD
 */
void lineFollow();

/* Drives forward until the line is reached
 * Input is 1 or -1 (for reverse)
 * OLD
 */
void findLine(int reverse);

/* Aligns the robot with the line
 * Input is 1 or -1 (for reverse)
 * OLD
 */
void alignLine(int reverse);


// Aligns with the line
void newLineUp(short rightLight);

// Finds the line
void runLineUp();

#endif
