#ifndef HEADERFILE_H
#define HEADERFILE_H

/* Sets mode for IR sensor
 * Sets initial position of harvester
*/
void initAutonomous();

// Converts inches to target value for encoder
int inchesToEncoder(int distance);

// Converts degrees to target value for encoder
int degreesToEncoder(int angle);

/* Moves robot with motor power "speed"
 * speed > 0: forward
 * speed < 0: backwards
 * speed = 0: stop
*/
void move(int speed);

/* Turns robot at the center with motor power "speed"
 * speed > 0: clockwise
 * speed < 0: counter-clockwise
 * speed = 0: stop
*/
void turn(int speed);

/* Moves robot a certain distance
 * Works like move() function, except stops when robot reaches "distance" inches
*/
void moveDistance(int speed, int distance);

/* Turns robot a certain angle
 * Works like turn(), except stops when robot reaches angle degrees
 * Degrees is always positive, speed determines direction of rotation
*/
 void turnDistance(int speed, int angle);

// Wait a number of seconds
 void pause(float seconds);

// Resets all encoder values to 0
 void resetEncoders();

#endif
