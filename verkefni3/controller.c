
#pragma config(Sensor, in1,    potientm,       sensorPotentiometer)
#pragma config(Sensor, in2,    lightsensor,    sensorReflection)
#pragma config(Sensor, in3,    lineRight,      sensorLineFollower)
#pragma config(Sensor, in4,    lineCenter,     sensorLineFollower)
#pragma config(Sensor, in5,    lineLeft,       sensorLineFollower)
#pragma config(Sensor, in6,    accel,          sensorAccelerometer)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  ,               sensorTouch)
#pragma config(Sensor, dgtl6,  armDown,        sensorTouch)
#pragma config(Sensor, dgtl8,  sonarCM,        sensorSONAR_cm)
#pragma config(Motor,  port2,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port4,           armMotor,      tmotorVex393, openLoop)
#pragma config(Motor,  port5,           armGrab,       tmotorVex269, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*										-- Verkefni 3 - Remote Controller --						  *|
|*																									  *|
|*				Programs the remote to be able to move the robot forward and backwards, turn, and	  *|
|*				Move the arm and grab with it.														  *|
\*-----------------------------------------------------------------------------------------------4246-*/
#include "../robheaders/const.h"
#include "../robfuncs/funcs.c"

int forwardValue = 0;

void turnWithController(int *motorValue1, int *motorValue2, int turnValue)
{
		if (*motorValue1 < -5)
		{
			*motorValue1 += turnValue;
		}
		else if (*motorValue1 > 5)
		{
			*motorValue1 -= turnValue;
		}
		else
		{
			*motorValue2 = turnValue;
			*motorValue1 = (turnValue * -1);
		}
}

void updateControllerValues()
{
	forwardValue = vexRT[Ch3];
}

void move()
{
		int leftMotorValue = forwardValue;
		int rightMotorValue = forwardValue;
		if (vexRT[ch1] > 10)
		{
				turnWithController(&rightMotorValue, &leftMotorValue, abs(vexRT[ch1]));
		}
		else if (vexRT[ch1] < -10)
		{
			turnWithController(&leftMotorValue, &rightMotorValue, abs(vexRT[ch1]));
		}
		setMotors(leftMotorValue, rightMotorValue);
}

void moveArm()
{
		if (vexRT[Btn5D])
		{
			motor[armMotor] = 20;
		}
		else if (vexRT[Btn6D])
		{
			motor[armMotor] = -50;
		}
		else
		{
			motor[armMotor] = 0;
		}
}

void moveArmGrab()
{
	if (vexRT[Btn8R])
	{
		motor[armGrab] = 50;
	}
	else if (vexRt[Btn8D])
	{
		motor[armGrab] = -50;
	}
	else {
		motor[armGrab] = 0;
	}
}

task main()
{
	wait10Msec(1000);
	calibrate();
	while (true)
	{
		updateControllerValues();
		move();
		moveArm();
		moveArmGrab();
		if (vexRT[STOPBUTTON])
    {
        stopAll();
        break;
    }
	 //setMotors((int) vexRT[Ch2], (int) vexRT[Ch3]);
	}
}
