#pragma config(Sensor, S1,     Color1,         sensorEV3_Color)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true) {
		displayBigTextLine(0, "%d" , getColorAmbient(Color1));
	}

}
