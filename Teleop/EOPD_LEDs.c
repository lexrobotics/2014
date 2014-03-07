#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     gyro,           sensorAnalogInactive)
#pragma config(Sensor, S4,     HTSPB,          sensorI2CCustom9V)

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

task eopd_leds() {
	// Set B0 for output
	HTSPBsetupIO(HTSPB, 0x1);
	HTEOPDsetLongRange(eopd);
	int val;

	while(true) {

		if(val>7){ //4 blocks in tray
			HTSPBwriteIO(HTSPB, 0x01);
			wait10MSec(15);
			HTSPBwriteIO(HTSPB, 0x00);
			wait10Msec(15);
		}
		else{ //No blocks in tray
			HTSPBwriteIO(HTSPB, 0x01);
		}
	}
}
