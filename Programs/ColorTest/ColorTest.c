#pragma config(Sensor, S1,     Color1,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorA,          LeftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorD,          RightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

short threshold = 0;

void callibColor();

task main()
{

	callibColor();


	while(true) {
		int reflection = getColorReflected(Color1);

		if(reflection > threshold) {
			setMotorSpeed(LeftMotor, -20);
			setMotorSpeed(RightMotor, 20);
		}
		else if(reflection >= threshold*0.90 && reflection <= threshold*1.10) {
			setMotorSpeed(LeftMotor, 40);
			setMotorSpeed(RightMotor, 40);
		}
		else {
			setMotorSpeed(LeftMotor, 20);
			setMotorSpeed(RightMotor, -20);
		}

		displayBigTextLine(1, "Hue: %d", reflection);
	}

}

void callibColor() {

	short lightVal = 0;
	short darkVal = 0;

	displayBigTextLine(0, "Color callib.");
	displayTextLine(3, "Place sensor on light surface.");
	displayTextLine(4, "Press Enter to accept.");

	while(getButtonPress(buttonEnter) != 1) {
		lightVal = getColorReflected(Color1);
		displayBigTextLine(6, "Hue: %d", lightVal);
	}

	delay(1000);

	eraseDisplay();

	displayBigTextLine(0, "Color callib.");
	displayTextLine(3, "Place sensor on dark surface.");
	displayTextLine(4, "Press Enter to accept.");

	while(getButtonPress(buttonEnter) != 1) {
		darkVal = getColorReflected(Color1);
		displayBigTextLine(6, "Hue: %d", darkVal);
	}

	threshold = (lightVal + darkVal) / 2;
}
