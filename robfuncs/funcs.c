
//enum DIRECTION {
//	LEFT,
//	RIGHT
//}

int Msec(int sec)
{
	return sec / 1000;
}

void resetEncoders()
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
}

void setMotors(int left = 127, int right = 127)
{
	motor[leftMotor] = left;
	motor[rightMotor] = right;
}

void driveTime(long time = 3000, int power = DEFAULTPOWER)
{
	long timeRemaining = time;
	resetEncoders();
	while (timeRemaining > 0)
	{
		int leftEncoder = abs(SensorValue[leftEncoder]);
		int rightEncoder = abs(SensorValue[rightEncoder]);
		if (leftEncoder == rightEncoder)
		{
			setMotors(power, power);
		 }
		else if (leftEncoder < rightEncoder)
		{
			setMotors(power, (int) power * (leftEncoder / rightEncoder));
		}
		else if (rightEncoder < leftEncoder)
		{
			setMotors((int) power * (rightEncoder / leftEncoder), power);
		}
		wait1Msec(100);
		timeRemaining -= 100;
	}
}

void driveDistance(int cm = 60, int power = DEFAULTPOWER)
{
	resetEncoders();
	while (abs(SensorValue[leftEncoder]) < (cm / WHEELDIAMETER * 360))
	{
		int leftEncoder = abs(SensorValue[leftEncoder]);
		int rightEncoder = abs(SensorValue[rightEncoder]);
		if (leftEncoder == rightEncoder)
		{
			setMotors(power, power);
		 }
		else if (leftEncoder < rightEncoder)
		{
			setMotors(power, (int) power * (leftEncoder / rightEncoder));
		}
		else if (rightEncoder < leftEncoder)
		{
			setMotors((int) power * (rightEncoder / leftEncoder), power);
		}
		wait1Msec(100);
	}
}

void reverseTime(long time = 3000, int power = DEFAULTPOWER)
{
		driveTime(time, -127);
}

/*void stopDrive()
{
	if(motor[rightMotor] > 0 && motor[leftMotor] > 0)
	{
		while(motor[rightMotor] > 0 || motor[leftMotor] > 0)
		{
			motor[leftMotor] = motor[leftMotor] - 1;
			motor[rightMotor = motor[rightMotor] -1;
			Sleep(Msec)
		}
	}
	if else(motor[rightMotor] < 0 && motor[leftMotor] < 0)
	{
		while(motor[rightMotor] < 0 || motor[leftMotor] < 0)
		{
			motor[leftMotor] = motor[leftMotor] + 1;
			motor[rightMotor = motor[rightMotor] + 1;
			sleep(Msec)
		}
	}
}*/

void turn(/*DIRECTION direction = DIRECTION::RIGHT, */int deg = 90)
{
	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
	motor[rightMotor] = 127;
	motor[leftMotor]  = 0;
	while (((SensorValue[rightEncoder] * -1) / 360 * WHEELDIAMETER) < (deg / 360 * ROBOTDIAMETER))
	{
			wait1Msec(100);
	}
}
