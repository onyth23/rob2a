#pragma config(Sensor, in1,    potientm,       sensorPotentiometer)
#pragma config(Sensor, in2,    lightsensor,    sensorReflection)
#pragma config(Sensor, in3,    lineRight,      sensorLineFollower)
#pragma config(Sensor, in4,    lineCenter,     sensorLineFollower)
#pragma config(Sensor, in5,    lineLeft,       sensorLineFollower)
#pragma config(Sensor, in6,    accel,          sensorAccelerometer)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  ,               sensorTouch)
#pragma config(Sensor, dgtl6,  armDown,        sensorTouch)
#pragma config(Sensor, dgtl8,  sonarCM,        sensorSONAR_cm)
#pragma config(Sensor, dgtl10, rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port2,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port4,           armMotor,      tmotorVex393, openLoop)
#pragma config(Motor,  port5,           armGrab,       tmotorVex269, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                         - Verkefni 2 - part 1 -                                    *|
|*                                      															  *|
|*			Using time, tells the robot to move forward 0.5m and then reverse the 		  *|
|*			same length, then increament by 0.5m until 2.5m.										  *|
|*																		                              *|
\*-----------------------------------------------------------------------------------------------4246-*/
#include "../robheaders/const.h"
#include "../robfuncs/funcs.c"

int state = 0;


void checkStopButton()
{
	if (vexRT[STOPBUTTON])
  {
      stopAll();
      StopAllTasks();
  }
}

void driveLine()
{
	while (true)
  {
    checkStopButton();
    if (lineUnder(0))
    {
        setMotors(75, 0);
    }
    if (lineUnder(1))
    {
        setMotors(55, 55);
    }
    if (lineUnder(2))
    {
        setMotors(0, 75);
	}
	if (SensorValue(sonarCM) < 32 && SensorValue(sonarCM) != -1)
	{
		state++;
		setMotors(0, 0);
		return;
	}
  }
}

void pickupBall()
{
	moveArm(1000, 60);
	for (int i = 0; i < 600; i++)
	{
		checkStopButton();
		motor[armGrab] = 60;
		wait1Msec(1);
	}
	motor[armGrab] = 0;
	while (SensorValue(sonarCM) > 28)
	{
		checkStopButton();
		setMotors(60, 60);
		wait1Msec(1);
	}
	setMotors(0, 0);
	for (int i = 0; i < 300; i++)
	{
		checkStopButton();
		motor[armGrab] = -60;
		wait1Msec(1);
	}
	motor[armGrab] = 0;
	state++;
}

void turnAround()
{
	turn(360);
	state++;
}

void setBallIntoBasket()
{
	while (SensorValue(sonarCM) > 3)
	{
		checkStopButton();
		setMotors(60, 60);
		wait1Msec(1);
	}
	setMotors(0, 0);
	for (int i = 0; i < 100; i++)
	{
		checkStopButton();
		motor[armGrab] = 30;
		wait1Msec(1);
	}
	motor[armGrab] = 0;
	for (int i = 0; i < 200; i++)
	{
		checkStopButton();
		motor[armGrab] = -30;
		wait1Msec(1);
	}
	motor[armGrab] = 0;
	state++;
}

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

task main()
{
    wait10Msec(1000);
    while (True)
    {
    	if (vexRT[STOPBUTTON])
      {
          stopAll();
          break;
      }
      switch (state)
      {
      	case 0: driveLine(); break;
      	case 1: pickupBall(); break;
      	case 2: driveLine(); break;
      	case 3: setBallIntoBasket(); break;
      	case 4: stopAll(); return;
      	default: stopAll(); return;
    	}
  	}
}								        // Program ends, and the robot stops
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
