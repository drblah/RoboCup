#pragma config(Sensor, S1,     Color1,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     Gyro,           sensorEV3_Gyro)
#pragma config(Motor,  motorA,          LeftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorD,          RightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while(true){
	setMotorSpeed(LeftMotor, 20);
	setMotorSpeed(RightMotor, -20);
}
}
