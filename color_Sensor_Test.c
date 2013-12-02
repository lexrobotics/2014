#pragma config(Sensor, S4,     colorPort,           sensorCOLORFULL)

/*
short nAtoDValues[3]={0,0,0};
short red = 0;
short green = 0;
short blue = 0;
*/

task main()
{
   wait1Msec(1000);  // Give sensor time to initialize
   eraseDisplay();
   string sColor;

   while(true) {

   		/*
    	SensorType[colorPort] = sensorCOLORRED;
	    short red = SensorRaw[colorPort];
	    nxtDisplayCenteredTextLine(2, "Red: %d", red);
	    wait10Msec(10);

	 		SensorType[colorPort] = sensorCOLORBLUE;
	    short blue = SensorRaw[colorPort];
	    nxtDisplayCenteredTextLine(3, "Blue: %d", blue);
	    wait10Msec(10);

	    SensorType[colorPort] = sensorCOLORGREEN;
	    short green = SensorRaw[colorPort];
	    nxtDisplayCenteredTextLine(4, "Green: %d", green);
	    wait10Msec(10);
	    */

	    switch(SensorValue[colorPort])
	    {
	    	case BLACKCOLOR: 	sColor = "Black"; break;
	    	case BLUECOLOR:		sColor = "Blue"; break;
	    	case REDCOLOR:		sColor = "Red"; break;
	    	case WHITECOLOR:	sColor = "White"; break;
	    	default: sColor = "???"; break;
	    }

	    nxtDisplayCenteredTextLine(3, sColor);

	    // short normColor = SensorValue[colorPort];
      // nxtDisplayCenteredTextLine(3, "Color: %d", normColor);

      wait1Msec(10);

   }
}
