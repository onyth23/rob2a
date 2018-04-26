
#include "../robheaders/const.h"
#include "../robfuncs/funcs.c"

// Verkefni 2

task verkefni2()
{
	while (true)
	{
		wait10Msec(1000);
		for (int i = 850; i < (850 * 6); i += 850)
		{
			driveTime((long) i);
			if (vexRT[STOPBUTTON])
      {
           stopAll();
           break;
      }
			reverseTime((long) i);
			if (vexRT[STOPBUTTON])
      {
           stopAll();
           break;
      }
		}
		setMotors(0, 0);
		break;
	}
}

// Verkefni 3

int v3_forwardValue = 0;

void v3_turnWithController(int *motorValue1, int *motorValue2, int turnValue)
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

void v3_updateControllerValues()
{
	v3_forwardValue = vexRT[Ch3];
}

void v3_move()
{
		int leftMotorValue = v3_forwardValue;
		int rightMotorValue = v3_forwardValue;
		if (vexRT[ch1] > 10)
		{
				v3_turnWithController(&rightMotorValue, &leftMotorValue, abs(vexRT[ch1]));
		}
		else if (vexRT[ch1] < -10)
		{
			v3_turnWithController(&leftMotorValue, &rightMotorValue, abs(vexRT[ch1]));
		}
		setMotors(leftMotorValue, rightMotorValue);
}

void v3_moveArm()
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

void v3_moveArmGrab()
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

task verkefni3()
{
	wait10Msec(1000);
	calibrate();
	while (true)
	{
		v3_updateControllerValues();
		v3_move();
		v3_moveArm();
		v3_moveArmGrab();
		if (vexRT[STOPBUTTON])
        {
            stopAll();
            break;
        }
	}
}

// Verkefni 4

task verkefni4()
{
    wait10Msec(500);
    while (SensorValue[lightsensor] < 500)
    {
        driveTime(10, 63);
        if (SensorValue[sonarCM] <= 40 && SensorValue[sonarCM] != -1)
        {
            int rndDeg = randomInt(90, 180);
            int rndTurn = randomInt(1, 2);
            turn(rndTurn, rndDeg);
        }
        if (vexRT[STOPBUTTON])
        {
            stopAll();
            break;
        }
    }

}

// Verkefni 5

task verkefni5()
{
   wait10Msec(1000);
	while (true)
	{
        if (vexRT[STOPBUTTON])
        {
            stopAll();
            break;
        }
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
	}
}

// Verkefni 6

int v6_state = 0;
int v6_lastLineUnder = 0;

void v6_checkStopButton()
{
	if (vexRT[STOPBUTTON])
	{
		stopAll();
		StopAllTasks();
	}
}

void v6_driveLine(int endAt)
{
	while (true)
	{
		v6_checkStopButton();
		if (lineUnder(0))
		{
			setMotors(75, 0);
			v6_lastLineUnder = 0;
		}
		if (lineUnder(1))
		{
			setMotors(55, 55);
		}
		if (lineUnder(2))
		{
			setMotors(0, 75);
			v6_lastLineUnder = 2;
		}
		if (SensorValue(sonarCM) < endAt && SensorValue(sonarCM) != -1)
		{
			v6_state++;
			setMotors(0, 0);
			return;
		}
	}
	wait10Msec(100);
}

void v6_pickupBall()
{
	moveArm(700, 60);
	for (int i = 0; i < 600; i++)
	{
		v6_checkStopButton();
		motor[armGrab] = 60;
		wait1Msec(1);
	}
	motor[armGrab] = 0;
	while (SensorValue(sonarCM) > 28)
	{
		v6_checkStopButton();
		setMotors(60, 60);
		wait1Msec(1);
	}
	setMotors(0, 0);
	for (int i = 0; i < 300; i++)
	{
		v6_checkStopButton();
		motor[armGrab] = -60;
		wait1Msec(1);
	}
	motor[armGrab] = 0;
	v6_state++;
	wait10Msec(100);
}

void v6_turnAround()
{
	turn(360);
	v6_state++;
}

void v6_setBallIntoBasket()
{
	while (SensorValue(sonarCM) > 22)
	{
		v6_checkStopButton();
		setMotors(60, 60);
		wait1Msec(1);
	}
	setMotors(0, 0);
	for (int i = 0; i < 300; i++)
	{
		v6_checkStopButton();
		motor[armGrab] = 60;
		wait1Msec(1);
	}
	motor[armGrab] = 0;
	v6_state++;
	wait10Msec(100);
}



task verkefni6()
{
	wait10Msec(1000);
	while (True)
	{
		if (vexRT[STOPBUTTON])
		{
			stopAll();
			break;
		}
		switch (v6_state)
		{
		case 0: v6_driveLine(32); break;
		case 1: v6_pickupBall(); break;
		case 2: v6_turnAround(); break;
		case 3: v6_driveLine(25); break;
		case 4: v6_setBallIntoBasket(); break;
		case 5: stopAll(); return;
		default: stopAll(); return;
		}
	}
}
