#pragma config(Sensor, S3,     LIGHTS3,        sensorLightActive)
#pragma config(Sensor, S4,     LIGHTS4,        sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	wait1Msec(1000);
	eraseDisplay();

	while(true) {
		nxtDisplayCenteredTextLine(3, "Light Value: %d", SensorValue[LIGHTS3]);
		wait1Msec(100);
	}
}
