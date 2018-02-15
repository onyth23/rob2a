
enum{
    LEFT = 0,
    RIGHT = 1
};


class Drive {
private:
    
    static void resetEncoders()
    {
	    SensorValue[leftEncoder] = 0;
	    SensorValue[rightEncoder] = 0;
    }

public:

    static void forward()
    {
        long timeRemaining = time;
	    Drive::resetEncoders();
	    while (timeRemaining > 0)
	    {
            int leftEncoder = abs(SensorValue[leftEncoder]);
            int rightEncoder = abs(SensorValue[rightEncoder]);
            // if (leftEncoder == rightEncoder)
            // {
                motor[rightMotor] = power;
                motor[leftMotor]  = power;
            // }
            /*else if (leftEncoder < rightEncoder)
            {
                motor[rightMotor] = (int) power * 0.9;
                motor[leftMotor]  = power;
            }
            else if (rightEncoder < leftEncoder)
            {
                motor[rightMotor] = power;
                motor[leftMotor]  = (int) power * 0.9;
            }*/
            wait1Msec(100);
            timeRemaining -= 100;
	    }
    }
    static void backwards()
    {
        Drive::forward();
    }

    static void turn(int direction = DIRECTION.RIGHT, int deg = 90)
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
};