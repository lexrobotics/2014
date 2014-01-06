/* Turns the wheels on only one side of the robot
 * The robot will drift toward one side
 * Defined for both sides
*/
void driftLeft(int speed);
void driftRight(int speed);

// Starts up light sensors
void lightsCameraAction();

// Drifts along the line
void lineFollow();

/* Drives forward until the line is reached
 * Input is 1 or -1 (for reverse)
*/
void findLine(int reverse);

/* Aligns the robot with the line
 * Input is 1 or -1 (for reverse)
*/
void alignLine(int reverse);

/* lightsCameraAction, findLine, alignLine, lineFollow
 * Defined for the second set of lines and for reverse
*/
void lineUp(bool secondLine);
void reverseLineUp(bool secondLine);
