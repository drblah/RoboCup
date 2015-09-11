#pragma config(Sensor, S1,     Color1,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     Gyro,           sensorEV3_Gyro)
#pragma config(Motor,  motorA,          LeftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorD,          RightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define WHEELSIZE 7 // Wheel diameter in cm
#define ENCODER_COUNT_REVOLUTION 360 // How many encoder counts goes to one revolution
#define ENCODER_SCALE_FACTOR ((PI*WHEELSIZE)/360)
#define WHEELSEPARATION 15 // Distance between wheels in cm

short threshold = 0;

float displacement = 0;
float rotation = 0;
float position_x = 0;
float position_y = 0;
float heading = 0;

void manualCallibColor();
void calcDisplacement();
void autoCallibColor();

task main()
{

	//manualCallibColor();
	autoCallibColor();

	while(true) {

		int reflection = getColorReflected(Color1);

		if(reflection > threshold) {
			setMotorSpeed(LeftMotor, 0);
			setMotorSpeed(RightMotor, 15);

		}
		else if(reflection >= threshold*0.90 && reflection <= threshold*1.10) {
			setMotorSpeed(LeftMotor, 20);
			setMotorSpeed(RightMotor, 20);
			delay(100);
		}
		else {
			setMotorSpeed(LeftMotor, 15);
			setMotorSpeed(RightMotor, 0);
		}

	}

}

void calcDisplacement() {
		displacement = (getMotorEncoder(LeftMotor) + getMotorEncoder(RightMotor)) * ENCODER_SCALE_FACTOR / 2;
		rotation = (getMotorEncoder(LeftMotor) - getMotorEncoder(RightMotor)) * ENCODER_SCALE_FACTOR/WHEELSEPARATION;

		position_x = position_x + displacement * cos(heading + rotation / 2);
		position_y = position_y + displacement * sin(heading + rotation / 2);
		heading = heading + rotation;
		eraseDisplay();
		//displayBigTextLine(1, "Hue: %d", reflection);
		displayBigTextLine(4, "Heading: %d", heading);
		displayBigTextLine(6, "X: %d", position_x);
		displayBigTextLine(8, "Y: %d", position_y);
}

void autoCallibColor() {
	unsigned short lightVal = 0;
	unsigned short darkVal = 255;

	while(getButtonPress(buttonEnter) != 1) {
		displayBigTextLine(2, "Press Enter to Calib");
	}

	clearTimer(timer1);
	setMotorSpeed(LeftMotor, 25);
	setMotorSpeed(RightMotor, 5);

	while(getTimerValue(timer1) < 1000) {
		unsigned short reflection = getColorReflected(Color1);

		if(reflection > lightVal) {
			lightVal = reflection;
		}
		if(reflection < darkVal) {
			darkVal = reflection;
		}
	}

	setMotorSpeed(LeftMotor, 0);
	setMotorSpeed(RightMotor, 0);

	threshold = (lightVal + darkVal) / 2;

}

void manualCallibColor() {

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
