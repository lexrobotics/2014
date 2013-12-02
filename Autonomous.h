#ifndef HEADERFILE_H
#define HEADERFILE_H

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

// Resets all encoder values to 0
 void resetEncoders();

#endif