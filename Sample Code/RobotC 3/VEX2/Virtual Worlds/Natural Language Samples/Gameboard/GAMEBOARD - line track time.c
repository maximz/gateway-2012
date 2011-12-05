#pragma config(Sensor, in1,    lightSensor,         sensorLineFollower)
#pragma config(Sensor, dgtl1,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,         sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  compassSensor,       sensorVirtualCompass)
#pragma config(Sensor, dgtl6,  touchSensor,         sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,         sensorSONAR_inch)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/********************************************\
|*  ROBOTC Virtual World (GAMEBOARD)        *|
|*  Line Track for Time (Natural Language)  *|
\********************************************/

// This program follows a black line on a white surface for 5.7 seconds.
// THIS PROGRAM FOLLOWS THE LEFT OUTTER EDGE OF A LINE!

task main()
{
  lineTrackForTime(5.7);    // track a dark line on a light surface for 5.7 seconds
  stop();                   // stop the robot
}