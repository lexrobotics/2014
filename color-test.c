#pragma config(Sensor, S1,     colorPort,           sensorCOLORFULL)

short nAtoDValues[3]={0,0,0};
short red = 0;
short green = 0;
short blue = 0;

task main()
{
   wait1Msec(1000);  // Give sensor time to initialize
   eraseDisplay();

   while(true) {
     /*
       SensorType[colorPort] = sensorCOLORRED;
     	 red = SensorRaw[colorPort];
     	 nxtDisplayCenteredTextLine(2, "Red: %d", red);
     	 wait10Msec(10);
     	 */
     	 /*
     	 SensorType[colorPort] = sensorCOLORBLUE;
     	 blue = SensorRaw[colorPort];
     	 nxtDisplayCenteredTextLine(3, "Blue: %d", blue);
     	 wait10Msec(10);
     	 */
     	 SensorType[colorPort] = sensorCOLORGREEN;
     	 blue = SensorRaw[colorPort];
     	 nxtDisplayCenteredTextLine(4, "Green: %d", green);
     	 wait10Msec(10);

   }
}
