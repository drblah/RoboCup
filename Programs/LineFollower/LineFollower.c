#pragma config(Sensor, S1,     Color1,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     Gyro,           sensorEV3_Gyro)
#pragma config(Motor,  motorA,          LeftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorD,          RightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define WHEELDIAMETER 7 // Wheel diameter in cm
#define ENCODER_COUNT_REVOLUTION 360 // How many encoder counts goes to one revolution
#define TURN_RIGHT true
#define TURN_LEFT false

//Different robot moods
#define CONFIDENT 0
#define CONFUSED 1

#define DISPLAYX 178
#define DISPLAYY 128
#define DISPCENTERX DISPLAYX/2
#define DISPCENTERY DISPLAYY/2

short threshold = 0;
short stopLine = 0;
short stopLineCounts = 0; // Must start at 0
bool stopLineLock = false;

volatile short robotMood = 1;

float gyroHeading = 0;

// Prototypes
void manualCallibColor();
void autoCallibColor();
void checkIfLost(float lostTimer, bool direction);
void rotate(int degrees);
void moveDist(int dist, int speed);
void mission1(int degrees, int delayMS);
void mission2(int degrees, int delayMS);
void mission5();
void mission7();
void mission8();
float circleCoordsX(int a, int radius, float t);
float circleCoordsY(int b, int radius, float t);
unsigned short avgReflectedLight(unsigned short samples);
float calcDistMoved();

task playMusic() {
	setSoundVolume(100);
	while(true) {
		switch(robotMood) {
		case CONFIDENT:
			playSoundFile("/home/root/lms2012/prjs/rc/airlinesLoop");
			delay(2141);
		break;

		case CONFUSED:
			playSoundFile("/home/root/lms2012/prjs/rc/oh-oh");
			delay(2500);
		break;
		}
	}

}

task main()
{

	robotMood = CONFUSED;
	startTask(playMusic);
	manualCallibColor();
	robotMood = CONFIDENT;
	//autoCallibColor();
	eraseDisplay();
	while(true) {

		int reflection = getColorReflected(Color1);
		gyroHeading = getGyroDegrees(Gyro);

		clearTimer(timer1);
		/*
			If the current reflected light is brighter than the callibrated threshold
			the robot assumes that it is currently in the light area. Thus it will begin
			moving towards the dark area by turning slightly to the left.
		*/
		while(reflection > threshold) {
			stopLineLock = false;
			setMotorSpeed(LeftMotor, 10);
			setMotorSpeed(RightMotor, 20);
			reflection = getColorReflected(Color1);

			checkIfLost(getTimerValue(timer1), TURN_LEFT);
		}

		clearTimer(timer1);

		while(reflection >= threshold*0.90 && reflection <= threshold*1.10) {
			stopLineLock = false;
			setMotorSpeed(LeftMotor, 20);
			setMotorSpeed(RightMotor, 20);
			reflection = getColorReflected(Color1);
		}

		clearTimer(timer1);

		while(reflection < threshold && reflection > stopLine) {
			stopLineLock = false;
			setMotorSpeed(LeftMotor, 20);
			setMotorSpeed(RightMotor, 10);
			reflection = getColorReflected(Color1);

			checkIfLost(getTimerValue(timer1), TURN_RIGHT);
		}

		// Mission selector
		if(reflection <= stopLine && stopLineLock == false){
			stopLineLock = true;
			stopLineCounts++;
			switch(stopLineCounts) {
			case 1:
				mission1(30,1000);
			break;

			case 2:
				mission2(-30,1000);
			break;

			case 5:
				mission5();
			break;

			case 7:
				mission7();
			break;

			case 8:
				mission8();
			break;
			}
		}
	}

}



/*
	Checks if the robot has been turning for more than 1500 ms.
	If that is the case, then the robot will enter a stationary search mode,
	where it will turn on the spot in an attempt to find a color contrast.
*/
void checkIfLost(float lostTimer, bool direction) {
	while(lostTimer > 1000) {
		robotMood = CONFUSED;
		if(direction == TURN_LEFT) {
			setMotorSpeed(LeftMotor, -10);
			setMotorSpeed(RightMotor, 10);
		}
		else {
			setMotorSpeed(LeftMotor, 10);
			setMotorSpeed(RightMotor, -10);
		}
		int reflection = getColorReflected(Color1);

		if(reflection < threshold && TURN_LEFT) {
			robotMood = CONFIDENT;
			clearTimer(timer1);
			break;
		}
		else if (reflection > threshold && TURN_RIGHT) {
			robotMood = CONFIDENT;
			clearTimer(timer1);
			break;
		}
	}
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

/*
	Returns the average reflected light from a given sample size.
*/
unsigned short avgReflectedLight(unsigned short samples) {

	unsigned int avgLight = 0;

	for(unsigned short i = 0; i < samples; i++) {
		avgLight = avgLight + getColorReflected(Color1);
	}

	avgLight = avgLight / samples;
	return avgLight;
}

void manualCallibColor() {

	unsigned short lightVal = 0;
	unsigned short greyVal = 0;
	unsigned short darkVal = 0;
	displayBigTextLine(0, "Color callib.");
	displayTextLine(3, "Place sensor on light surface.");
	displayTextLine(4, "Press Enter to accept.");
	while(true) {
		// Display the reflected value live to help manual positioning.
		lightVal = getColorReflected(Color1);
		displayBigTextLine(6, "Reflected: %d", lightVal);

		// Press enter to take 10 light sampels then tage the average and break out of the loop.
		if(getButtonPress(buttonEnter) == 1) {
			lightVal = avgReflectedLight(10);
			break;
		}
	}

	delay(1000);

	eraseDisplay();

	displayBigTextLine(0, "Color callib.");
	displayTextLine(3, "Place sensor on grey surface.");
	displayTextLine(4, "Press Enter to accept.");

	while(true) {
		// Display the reflected value live to help manual positioning.
		greyVal = getColorReflected(Color1);
		displayBigTextLine(6, "Reflected: %d", greyVal);

		// Press enter to take 10 light sampels then tage the average and break out of the loop.
		if(getButtonPress(buttonEnter) == 1) {
			greyVal = avgReflectedLight(10);
			break;
		}
	}

	delay(1000);

	displayBigTextLine(0, "Color callib.");
	displayTextLine(3, "Place sensor on dark surface.");
	displayTextLine(4, "Press Enter to accept.");
	while(true) {
		// Display the reflected value live to help manual positioning.
		darkVal = getColorReflected(Color1);
		displayBigTextLine(6, "Reflected: %d", darkVal);

		// Press enter to take 10 light sampels then tage the average and break out of the loop.
		if(getButtonPress(buttonEnter) == 1) {
			darkVal = avgReflectedLight(10);
			break;
		}
	}
		delay(5000);

	threshold = (lightVal + greyVal) / 2;
	stopLine = darkVal;
}

float circleCoordsX(int a,int radius, float t) {
	return a+radius*cos(t);
}

float circleCoordsY(int b, int radius, float t) {
	return b+radius*sin(t);
}

void rotate(int degrees){
	resetGyro(Gyro);

	if(degrees > 0){
		setMotorSpeed(LeftMotor,10);
		setMotorSpeed(RightMotor,-10);
		}
	else {
		setMotorSpeed(LeftMotor,-10);
		setMotorSpeed(RightMotor,10);
		}
	while(abs(getGyroDegrees(Gyro)) <= abs(degrees)){
	}
	setMotorSpeed(LeftMotor,0);
	setMotorSpeed(RightMotor,0);
}

float calcDistMoved() {
	return ((PI*WHEELDIAMETER)/ENCODER_COUNT_REVOLUTION) * (getMotorEncoder(LeftMotor)+getMotorEncoder(RightMotor))/2;
}

void moveDist(int dist, int speed) {
	resetMotorEncoder(LeftMotor);
	resetMotorEncoder(RightMotor);
	if(dist > 0) {
		while(calcDistMoved() < dist) {
			setMotorSpeed(LeftMotor, speed);
			setMotorSpeed(RightMotor, speed);
		}

		setMotorSpeed(LeftMotor, 0);
		setMotorSpeed(RightMotor, 0);
	}
	else {
		setMotorSpeed(LeftMotor, speed*-1);
		setMotorSpeed(RightMotor, speed*-1);

		while(calcDistMoved() > dist) {
			setMotorSpeed(LeftMotor, speed);
			setMotorSpeed(RightMotor, speed);
		}

		setMotorSpeed(LeftMotor, 0);
		setMotorSpeed(RightMotor, 0);
	}

}

void mission1(int degrees,int delayMS) {
	rotate(degrees);
	setMotorSpeed(LeftMotor, 15);
	setMotorSpeed(RightMotor, 15);
	delay(delayMS);

		// Move forward until the grey line is detected again.
		while(true) {
			int reflected = getColorReflected(Color1);
			if(reflected <= threshold && reflected > stopLine) {
				break;
			}
		}
		// Seek opposite edge of line
		while(true) {
			int reflected = getColorReflected(Color1);
			if(reflected > threshold) {
				break;
			}
		}

}

void mission2(int degrees,int delayMS) {
	rotate(degrees);
	setMotorSpeed(LeftMotor, 15);
	setMotorSpeed(RightMotor, 15);
	delay(delayMS);

		// Move forward until the grey line is detected again.
		while(true) {
			int reflected = getColorReflected(Color1);
			if(reflected <= threshold && reflected > stopLine) {
				break;
			}
		}
}

void mission5() {
	moveDist(20,15);
	mission1(-70,300);
	mission1(10,500);
}

void mission7() {
	rotate(45);
	moveDist(40, 15);
	mission2(-45, 0);
}

void mission8() {
	moveDist(40, 15);
	rotate(-30);

	moveDist(30, 15);
	rotate(55);
	moveDist(50, 15);

	mission2(-65, 50);
}
