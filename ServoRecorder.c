int recordServoPos(tServo _servo, int button1, int button2, int recordButton) {
	while(!joy1Btn(recordButton)) {
		if(joy1Btn(button1))
			servo[_servo] += 1;
		else if(joy1Btn(button2))
			servo[_servo] -= 1;
	}
	return servo[_servo];
}