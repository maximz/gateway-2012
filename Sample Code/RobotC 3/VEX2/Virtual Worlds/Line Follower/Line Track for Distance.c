#pragma config(Sensor, in1,    lightSensor,         sensorLineFollower)
#pragma config(Sensor, dgtl1,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,         sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  compassSensor,       sensorVirtualCompass)
#pragma config(Sensor, dgtl6,  touchSensor,         sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,         sensorSONAR_inch)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Line Track for Distance
This program uses 1 VEX Line Follower Sensor to track a black line on a light(er) surface
for 5 rotations of the encoders. There is a two second pause at the beginning of the program.

The threshold variable defined in this program may need to be changed for the line/surface your
robot is tracking and the lighting conditions.

Robot Model(s): Squarebot

[I/O Port]          [Name]              [Type]                [Description]
Motor Port 2        rightMotor          VEX Motor             Right side motor
Motor Port 3        leftMotor           VEX Motor             Left side motor
Analog Port 1       lightSensor         VEX Line Follower     Front-center, facing down
Digital Port 1      rightEncoder        VEX Shaft Encoder     Right side encoder
Digital Port 3      leftEncoder         VEX Shaft Encoder     Left side encoder

*To run this sample program on Swervebot, be sure to Reverse Motor Port 3 in the Motors and Sensors
 Setup, and to make sure that Motor Port 2 is NOT Reversed.
----------------------------------------------------------------------------------------------------*/

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
  wait1Msec(2000);          // The program waits for 2000 milliseconds before continuing.

  int threshold = 1500;      /* found by taking a reading on both DARK and LIGHT    */
                            /* surfaces, adding them together, then dividing by 2. */

  //Clear Encoder Values
  SensorValue(rightEncoder) = 0;
  SensorValue(leftEncoder) = 0;

  //Line Track for 5 rotations...
  while(SensorValue(rightEncoder) < 1800)
  {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\
    displayLCDCenteredString(0, "Light Sensor:");           //  Display   |
    displayLCDPos(1,6);                                     //  Sensor    |
    displayNextLCDNumber(SensorValue(lightSensor));         //  Readings  |
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -/

    // sensor sees light:
    if(SensorValue(lightSensor) < threshold)
    {
      // counter-steer left:
      motor[leftMotor]  = 63;
      motor[rightMotor] = 0;
    }
    // sensor sees dark:
    else
    {
      // counter-steer right:
      motor[leftMotor]  = 0;
      motor[rightMotor] = 63;
    }
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
