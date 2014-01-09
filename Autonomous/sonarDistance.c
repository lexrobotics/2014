#pragma config(Sensor, S1,     sonarSensor,    sensorSONAR)
#include "sonarDistance.h"
task main()
{

while(1)nxtDisplayCenteredBigTextLine(3,"%d %d",SensorValue[sonarSensor],(int)isClearToRamp(50));

}
