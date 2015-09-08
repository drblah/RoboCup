#pragma config(Sensor, S1,     Gyro,           sensorEV3_Gyro)
#pragma config(Motor,  motorA,          LeftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorD,          RightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//



task main()
{
	resetMotorEncoder(LeftMotor);
	resetMotorEncoder(RightMotor);
	while(true) {
			while(getMotorEncoder(LeftMotor) < 500) {
				setMotorSpeed(LeftMotor, 50);
				setMotorSpeed(LeftMotor, -50);
			}
			while(getMotorEncoder(LeftMotor) > 0) {
				setMotorSpeed(LeftMotor, -50);
				setMotorSpeed(LeftMotor, 50);
			}
	}


}
