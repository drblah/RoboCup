#pragma config(Sensor, S1,     Gyro,           sensorEV3_Gyro)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	int angle;
	while(true) {
		angle = getGyroDegrees(Gyro);
		displayBigTextLine(1, "Angle: %d", angle);
	}


}
