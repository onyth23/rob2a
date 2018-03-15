#pragma config(Sensor, in1,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in2,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*																							Verkefni 5																						*|
|*											Program that makes the robot follow a line using 3 line sensors							  *|
\*-----------------------------------------------------------------------------------------------4246-*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
  wait1Msec(2000);          // The program waits for 2000 milliseconds before continuing.

  int threshold = 505;      /* found by taking a reading on both DARK and LIGHT    */
                            /* surfaces, adding them together, then dividing by 2. */
  while(true)
  {
    // RIGHT sensor sees dark:
    if(SensorValue(lineRight) > threshold)
    {
      // counter-steer right:
			setMotor(63, 0)
    }
    // CENTER sensor sees dark:
    if(SensorValue(lineCenter) > threshold)
    {
      // go straight
			setMotor(63, 63)
    }
    // LEFT sensor sees dark:
    if(SensorValue(lineLeft) > threshold)
    {
      // counter-steer left:
    	setMotor(0, 63)
    }
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
