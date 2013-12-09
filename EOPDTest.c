#pragma config(Sensor, S1,     HTEOPD,              sensorAnalogActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#include "drivers/hitechnic-eopd.h"

task main() {
  int _raw = 0;
  //int _processed = 0;

  // Standard range is set to short range
  //bool shortrange = false;

  	//nNxtButtonTask  = -2;
    HTEOPDsetLongRange(HTEOPD);
    //nxtDisplayClearTextLine(1);
    //nxtDisplayTextLine(1, "Long range");
    //shortrange = false;

    while(nNxtButtonPressed != kEnterButton) {
      // Read the raw sensor value
      _raw = HTEOPDreadRaw(HTEOPD);

      // read the processed value which is linear with
      // the distance detected.  Use the processed value
      // when you want to determine distance to an object
      //_processed = HTEOPDreadProcessed(HTEOPD);
      //nxtDisplayClearTextLine(3);
      nxtDisplayClearTextLine(4);

    	//nxtDisplayTextLine(3,"Dist:       %d",);

      nxtDisplayCenteredBigTextLine(1,"%d",_raw);
      if(_raw==0)nxtDisplayCenteredBigTextLine(3, "D:");//nothing in front
      else nxtDisplayCenteredBigTextLine(3, ":D");//something a finite distance there
      wait1Msec(50);
    }
}
