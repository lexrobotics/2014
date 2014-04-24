#include "drivers/hitechnic-superpro.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-eopd.h"

const tMUXSensor eopd = msensor_S2_2;

/* Task to flash LEDs depending on # of blocks in tray, as measured by the EOPD
 * This is to aid the drivers during TeleOp
 * 4 blocks - constant on
 * 3 blocks - quickest flash
 * 2 blocks - quicker flash
 * 1 block - quick flash
 * No blocks - constant off
 */

static int FIFTH_BLOCK_THRESH = 7;
int ledMode = 0;
int lockState = 0;

task eopd_leds() {
	// Set B0 for output
	HTSPBsetupIO(HTSPB, 0x1);
	HTSPBwriteIO(HTSPB, 0x01);

	HTEOPDsetLongRange(eopd);
	int val;
	bool lit = false;
	while(true) {
		val=HTEOPDreadProcessed(eopd);
		if(ledMode == 0) {
			if(val > FIFTH_BLOCK_THRESH){ //5th block
				HTSPBwriteIO(HTSPB, 0x01);
				wait10Msec(15);
				HTSPBwriteIO(HTSPB, 0x00);
				wait10Msec(15);
				lit = false;
			}
			else{ //No blocks in tray
				if(!lit)
					HTSPBwriteIO(HTSPB, 0x01);
				lit = true;
			}
		}
		else {
			if(lockState == 2) {
				HTSPBwriteIO(HTSPB, 0x01);
				wait10Msec(5);
				HTSPBwriteIO(HTSPB, 0x00);
				wait10Msec(5);
			}
			else if(lockState == 1) {
				HTSPBwriteIO(HTSPB, 0x01);
				wait10Msec(15);
				HTSPBwriteIO(HTSPB, 0x00);
				wait10Msec(15);
			}
			else {
				HTSPBwriteIO(HTSPB, 0x01);
			}
		}
	}
}
