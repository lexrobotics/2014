#pragma config(Sensor, S1,     HTSPB,                sensorI2CCustom9V)
#pragma config(Sensor, S1,     eopd,              sensorAnalogActive)

#include "drivers/hitechnic-superpro.h"
#include "drivers/hitechnic-eopd.h"

task eopd_leds() {
	// Set B0 for output
	HTSPBsetupIO(HTSPB, 0x1);
	HTEOPDsetLongRange(eopd);
	int val;

	while(true) {
		nxtDisplayCenteredBigTextLine(3,"%d",val=HTEOPDreadProcessed(eopd));
		
		if(val>50){//4
			HTSPBwriteIO(HTSPB, 0x01);
			wait10MSec(40);
		}
		else if(30){//3
			for(int i=0;i<4;i++){
				HTSPBwriteIO(HTSPB, 0x01);
				wait10MSec(5);
				HTSPBwriteIO(HTSPB, 0x00);
				wait10MSec(5);
			}
		}
		else if(val>20){//2
			for(int i=0;i<2;i++){
				HTSPBwriteIO(HTSPB, 0x01);
				wait10MSec(10);
				HTSPBwriteIO(HTSPB, 0x00);
				wait10MSec(10);
			}
		}
		else if(val>12){//1
			HTSPBwriec(20);
		}
		else{//0
			HTSPBwriteIO(HTSPB, 0x00);
			wait10MSec(40);
		}
	}
}

