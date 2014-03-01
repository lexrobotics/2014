#include "drivers/hitechnic-superpro.h"
#include "drivers/hitechnic-eopd.h"
#include "drivers/hitechnic-sensormux.h"

const tMUXSensor eopd = msensor_S3_2;

/* Task to flash LEDs depending on # of blocks in tray, as measured by the EOPD
 * This is to aid the drivers during TeleOp
 * 4 blocks - constant on
 * 3 blocks - quickest flash
 * 2 blocks - quicker flash
 * 1 block - quick flash
 * No blocks - constant off
 */

task eopd_leds() {
	// Set B0 for output
	HTSPBsetupIO(HTSPB, 0x1);
	HTEOPDsetLongRange(eopd);
	int val;

	while(true) {
		nxtDisplayCenteredBigTextLine(3,"%d",val=HTEOPDreadProcessed(eopd));
		
		if(val>50){ //4 blocks in tray
			HTSPBwriteIO(HTSPB, 0x01);
			wait10MSec(40);
		}
		else if(30){ //3 blocks in tray
			for(int i=0;i<4;i++){
				HTSPBwriteIO(HTSPB, 0x01);
				wait10MSec(5);
				HTSPBwriteIO(HTSPB, 0x00);
				wait10MSec(5);
			}
		}
		else if(val>20){ //2 blocks in tray
			for(int i=0;i<2;i++){
				HTSPBwriteIO(HTSPB, 0x01);
				wait10MSec(10);
				HTSPBwriteIO(HTSPB, 0x00);
				wait10MSec(10);
			}
		}
		else if(val>12){ //1 block in tray
			HTSPBwriteIO(HTSPB, 0x01)
			wait10MSec(20);
			HTSPBwriteIO(HTSPB, 0x00);
			wait10MSec(20);
		}
		else{ //No blocks in tray
			HTSPBwriteIO(HTSPB, 0x00);
			wait10MSec(40);
		}
	}
}

