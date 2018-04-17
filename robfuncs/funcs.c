
#include "calibration.c"
#include "update.c"

int Msec(int sec)
{
	return sec / 1000;
}

int randomInt(int min, int max)
{
	return min + rand() % (max - min + 1);
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

void moveArm(int time, int speed = 60)
{
	int counter = 0;
	while (time <= counter)
	{
		motor[armMotor] = speed;
		counter++;
		wait1Msec(1);
	}
	motor[armMotor] = 0;
}

void setArmPos(int pos)
{
	bool moveArmUp = pos < SensorValue[potientm];
	while (moveArmUp && SensorValue[potientm] < pos || !moveArmUp && SensorValue[potientm] > pos)
	{
		motor[armMotor] = moveArmUp ? -60 : 20;
		wait1Msec(3);
	}
}

void driveTime(long time = 3000, int power = DEFAULTPOWER)
{
	long timeRemaining = time;
	resetEncoders();
	int currentPower = (int) (motor[leftMotor] + motor[rightMotor]) / 2;
	while (currentPower > power + 10 || currentPower < power - 10)
	{
		if (currentPower > power)
		{
			currentPower -= 1;
		}
		else if (currentPower < power)
		{
			currentPower += 1;
		}
		setMotors(currentPower, currentPower);
		wait1Msec(3);
	}
	currentPower = power;
	while (timeRemaining > 0)
	{
		int leftEncoder = abs(SensorValue[leftEncoder]);
		int rightEncoder = abs(SensorValue[rightEncoder]);
		if (leftEncoder == rightEncoder)
		{
			setMotors(currentPower, currentPower);
		}
		else if (leftEncoder < rightEncoder)
		{
			setMotors(currentPower, (int) currentPower * (leftEncoder / rightEncoder));
		}
		else if (rightEncoder < leftEncoder)
		{
			setMotors((int) currentPower * (rightEncoder / leftEncoder), currentPower);
		}
		wait1Msec(10);
		timeRemaining -= 10;
	}
}

void driveDistance(int cm = 60, int power = DEFAULTPOWER)
{
	resetEncoders();
	int currentPower = (int) (motor[leftMotor] + motor[rightMotor]) / 2;
	while (currentPower > power + 10 || currentPower < power - 10)
	{
		if (currentPower > power)
		{
			currentPower -= 1;
		}
		else if (currentPower < power)
		{
			currentPower += 1;
		}
		setMotors(currentPower, currentPower);
		wait1Msec(3);
	}
	currentPower = power;
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
		wait1Msec(10);
	}
}

void reverseTime(long time = 3000, int power = DEFAULTPOWER)
{
	driveTime(time, power * -1);
}

void reverseDistance(long time = 3000, int power = DEFAULTPOWER)
{
	driveDistance(time, power * -1);
}

bool lineUnder(int sensor)
{
	switch (sensor)
	{
		case 0: return SensorValue(lineRight) > threshold;
		case 1: return SensorValue(lineCenter) > threshold;
		case 2: return SensorValue(lineLeft) > threshold;
		default: return false;
	}
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
	else if(motor[rightMotor] < 0 && motor[leftMotor] < 0)
	{
		while(motor[rightMotor] < 0 || motor[leftMotor] < 0)
		{
			motor[leftMotor] = motor[leftMotor] + 1;
			motor[rightMotor = motor[rightMotor] + 1;
			sleep(Msec)
		}
	}
}*/

void turn(int direction = RIGHT, int deg = 90)
{
	resetEncoders();
	int encoder;
	if (direction == RIGHT)
	{
		encoder = rightEncoder;
		setMotors(127, -127);
	}
	else
	{
		encoder = leftEncoder;
		setMotors(-127, 127);
	}
	// while ((abs(SensorValue[encoder]) / 360 * WHEELDIAMETER) < (deg / 360 * ROBOTDIAMETER))
	// {
	// 	wait1Msec(10);
	// }
	while (abs(SensorValue[encoder]) < deg / 90 * 240)
	{
		wait1Msec(10);
	}
}


void stopAll()
{
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	motor[armMotor] = 0;
	motor[armGrab] = 0;
}