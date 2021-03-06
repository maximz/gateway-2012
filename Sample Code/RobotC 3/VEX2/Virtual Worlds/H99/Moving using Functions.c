#pragma config(Sensor, in1,    lightSensor,         sensorLineFollower)
#pragma config(Sensor, dgtl1,  rightEncoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,         sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  compassSensor,       sensorVirtualCompass)
#pragma config(Sensor, dgtl6,  touchSensor,         sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,         sensorSONAR_inch)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


/******************************\
|*  ROBOTC Virtual World      *|
|*  Moving (using Functions)  *|
\******************************/


// This program uses functions to move and turn.  Each function accepts some parameters.
// Functions are usefull for saving space when you need to perform the same actions over and over.

//----------------------------------------------| MOVE |----------------------------------------------
void move(int speed)
{
  motor[rightMotor] = speed;        // set port2 to speed, 'speed'
  motor[leftMotor]  = speed;        // set port3 to speed, 'speed'
}
//----------------------------------------------------------------------------------------------------

//----------------------------------------------| TURN |----------------------------------------------
void turn(int rightSpeed, int leftSpeed)
{
  motor[rightMotor] = rightSpeed;	// set port2 to speed, 'rightSpeed'
  motor[leftMotor]  = leftSpeed;   	// set port3 to speed, 'leftSpeed'
}
//----------------------------------------------------------------------------------------------------


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
  move(75);         // call our move function with a speed of 75 (forward)
  wait1Msec(2000);  // wait for 2 seconds
  move(0);          // call our move function with a speed of 0 (stop)
  wait1Msec(2000);  // wait for 2 seconds


  turn(75, -75);    // call our turn function with a right speed of 75
                    // and a left speed of -75 (point turn left)

  wait1Msec(3000);  // wait for 1 second

  move(-75);        // call our move function with a speed of -75 (backward)
  wait1Msec(2000);  // wait for 2 seconds
  move(0);          // call our move function with a speed of 0 (stop)
  wait1Msec(2000);  // wait for 2 seconds


  turn(-75, 75);    // call our turn function with a right speed of -75
                    // and a left speed of 75 (point turn right)

  wait1Msec(3000);  // wait for 1 second*/
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
