/* Turns the wheels on only one side of the robot
 * The robot will drift toward one side
 * Defined for both sides
*/
void driftLeft(int speed);
void driftRight(int speed);

/* Follows a line
 * Pivots when an intersection is reached
*/
void lineFollow();
