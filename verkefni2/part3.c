#pragma config(Sensor, in1,    potientm,       sensorPotentiometer)
#pragma config(Sensor, in2,    lightsensor,    sensorReflection)
#pragma config(Sensor, in3,    lineRight,      sensorLineFollower)
#pragma config(Sensor, in4,    lineCenter,     sensorLineFollower)
#pragma config(Sensor, in5,    lineLeft,       sensorLineFollower)
#pragma config(Sensor, in6,    accel,          sensorAccelerometer)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  ,               sensorTouch)
#pragma config(Sensor, dgtl6,  sonarCM,        sensorSONAR_cm)
#pragma config(Sensor, dgtl8,  armDown,        sensorTouch)
#pragma config(Sensor, dgtl10, rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port2,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port4,           armMotor,      tmotorVex393, openLoop)
#pragma config(Motor,  port5,           armGrab,       tmotorVex269, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                         - Verkefni 2 - part 3 -                                    *|
|*                                      																															*|
|*							Tells the robot to move forward 50cm, then turn left, move 50cm again, turn right,		*|
|*							move 50cm, turn right again and finally move 50cm again.															*|
\*-----------------------------------------------------------------------------------------------4246-*/
#include "../robheaders/const.h"
#include "../robfuncs/funcs.c"


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

task main()
{
	while (true)
	{
    wait10Msec(1000);

    driveDistance(10);
    turn(LEFT);
    driveDistance(10);
    turn(RIGHT);
    driveDistance(10);
    turn(RIGHT);
    driveDistance(10);

		stopAll();
	}
}										        // Program ends, and the robot stops
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
