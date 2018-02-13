
int Msec(int sec)
{
	return sec / 1000;
}

void drive(long time = 3000, int power = DEFAULTPOWER)
{
	long timeRemaining = time;
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	while (timeRemaining > 0)
	{
		int leftEncoder = abs(SensorValue[leftEncoder]);
		int rightEncoder = abs(SensorValue[rightEncoder]);
		if (leftEncoder == rightEncoder)
		{
			motor[rightMotor] = power;
			motor[leftMotor]  = power;
		}
		else if (leftEncoder < rightEncoder)
		{
				motor[rightMotor] = (int) power * 0.9;
				motor[leftMotor]  = power;
		}
		else if (rightEncoder < leftEncoder)
		{
				motor[rightMotor] = power;
				motor[leftMotor]  = (int) power * 0.9;
		}
		wait1Msec(10);
		timeRemaining -= 10;
	}
}

void driveDistance(int cm = 60, int power = DEFAULTPOWER)
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0;
	while (abs(SensorValue[leftEncoder]) < (cm / WHEELDIAMETER * 360))
	{
		int leftEncoder = abs(SensorValue[leftEncoder]);
		int rightEncoder = abs(SensorValue[rightEncoder]);
		if (leftEncoder == rightEncoder)
		{
			motor[rightMotor] = power;
			motor[leftMotor]  = power;
		}
		else if (leftEncoder < rightEncoder)
		{
			motor[rightMotor] = power * 0.9;
			motor[leftMotor]  = power;
		}
		else if (rightEncoder < leftEncoder)
		{
			motor[rightMotor] = power;
			motor[leftMotor]  = power * 0.9;
		}
		wait1Msec(100);
	}
}

void reverse(long time = 3000, int power = DEFAULTPOWER)
{
		drive(time, -127);
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

void turnRight(int deg = 90)
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

void turnLeft(int deg = 90)
{
	motor[rightMotor] = 0;
	motor[leftMotor]  = 127;
	wait1Msec(1000);
}
