


void calArm()
{
    while (!SensorValue[armDown])
    {
        motor[armMotor] = 20;
    }
    motor[armMotor] = 0;
    SensorValue[potientm] = 0;
}

void calibrate()
{
    // calArm();
}