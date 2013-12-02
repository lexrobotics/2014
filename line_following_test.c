#pragma config(Sensor, S3,     COLORS3,        sensorCOLORFULL)
#pragma config(Sensor, S4,     COLORS4,        sensorCOLORFULL)
#pragma config(Motor,  motorB,          LMOTOR,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          RMOTOR,        tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	wait1Msec(1000);
	eraseDisplay();
	string s3Color;
	string s4Color;

	while(true) {

		switch(SensorValue[COLORS3])
	    {
	    	case BLACKCOLOR: 	s3Color = "Black"; break;
	    	case BLUECOLOR:		s3Color = "Blue"; break;
	    	case REDCOLOR:		s3Color = "Red"; break;
	    	case WHITECOLOR:	s3Color = "White"; break;
	    	default: s3Color = "???"; break;
	    }

		switch(SensorValue[COLORS4])
	    {
	    	case BLACKCOLOR: 	s4Color = "Black"; break;
	    	case BLUECOLOR:		s4Color = "Blue"; break;
	    	case REDCOLOR:		s4Color = "Red"; break;
	    	case WHITECOLOR:	s4Color = "White"; break;
	    	default: s4Color = "???"; break;
	    }

	  if(s3Color == "Black") {
	  	if(s4Color == "Black") {
	  		motor[LMOTOR] = 20;
	  		motor[RMOTOR] = 20;
	  	}
	  	else if( s4Color == "White") {
	  		motor[LMOTOR] = 10;
	  		motor[RMOTOR] = 30;
	  	}
	  	else {
	  		motor[LMOTOR] = 0;
	  		motor[RMOTOR] = 0;
	  		nxtDisplayCenteredTextLine(2, "IT'S A TRAP");
	  	}
	  }
	  else if (s3Color == "White") {
	  	if(s4Color == "Black") {
	  		motor[LMOTOR] = 30;
	  		motor[RMOTOR] = 10;
	  	}
	  	else if(s4Color == "White") {
	  		motor[LMOTOR] = 0;
	  		motor[RMOTOR] = 0;
	  		nxtDisplayCenteredTextLine(2, "INTERSECTION!");
	  	}
	  	else {
	  		motor[LMOTOR] = 0;
	  		motor[RMOTOR] = 0;
	  		nxtDisplayCenteredTextLine(2, "IT'S A TRAP");
	  	}
	  }

		nxtDisplayCenteredTextLine(3, s3Color);
		nxtDisplayCenteredTextLine(4, s4Color);
		wait1Msec(10);

	}
}