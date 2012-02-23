#pragma config(Sensor, dgtl1,  leftEncoder,        sensorQuadEncoder) /* dgtl 2 is also for this encoder */
#pragma config(Sensor, dgtl3,  rightEncoder,         sensorQuadEncoder) /* dgtl 4 is also for this encoder */
#pragma config(Sensor, dgtl11, sonarSensor,         sensorSONAR_inch) /* dgtl 12 is also for this encoder. 11: output; 12: input. */
#pragma config(Motor,  port1,           leftMotor,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port2,           elclawo,       tmotorServoStandard, openLoop)
#pragma config(Motor,  port4,           elevatorThreeMotor, tmotorNormal, openLoop, reversed) /* left */
#pragma config(Motor,  port5,           elevatorFourMotor, tmotorNormal, openLoop) /* right */
#pragma config(Motor,  port6,           basketMotor, tmotorNormal, openLoop) /* flips the basket */
#pragma config(Motor,  port7,           elevatorOneMotor, tmotorNormal, openLoop) /* left */
#pragma config(Motor,  port8,           elevatorTwoMotor, tmotorNormal, openLoop, reversed) /* right */
#pragma config(Motor,  port9,           lateralMotor,  tmotorNormal, openLoop)
#pragma config(Motor,  port10,          rightMotor,    tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/* BroBots - The Bishop's School 2011-2012 Robotics Team Varsity Bot */

#include "settings/settings.c"

/*										  ROBOT CONFIGURATION										  *|
|*	  NOTES:																						  *|
|*	  1)  Ch1 is the X axis and Ch2 is the Y axis for the RIGHT joystick.							  *|
|*	  2)  Ch3 is the Y axis and Ch4 is the X axis for the LEFT joystick.							  *|
|*	  3)  'abs(z)' is the ABSOLUTE VALUE of 'z'.													  */

int ljoy_x; // This is the X value of the LEFT analog stick.
int ljoy_y; // This is the Y value of the LEFT analog stick.
int rjoy_x; // This is the X value of the RIGHT analog stick.
int rjoy_y; // This is the Y value of the RIGHT analog stick.
int threshold = 12.7;

float currentX;
float currentY;
float currentAngle;

#include "logic/aitoggles.c"
#include "logic/sticklayouts.c"
#include "logic/sticktoggles.c"

#include "logic/ai.c"

#include "logic/controlflow.c"

/* Region: Competition Code */


void pre_auton()
{
	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
	currentX = 0;
	currentY = 0;
}
task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................
	launchCompetitionAI();
}
task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................
	  // Insert user code here. This is where you use the joystick values to update your motors, etc.
	  // .....................................................................................

	  userControlLooped();
	}
}

/* Region: Main Task */

void startBot(left, right, up, down) // passed by value, so after startBot is called, these variables don't change during the execution of the method. Thus, subsequent button presses or releases have no effect on what AI is being currently used, except for the button presses that switch to one or two stick layout, which end the AI prematurely.
{
	while(true)
	{
		aiControlTimed(left, right, up, down);
		// Time to go back to user control.
		userControlLooped();

		// if we break out of user control, that means AI was activated or something weird happened...
		continue;
	}

} // end function

void debugMain()
{
	while (true)
	{
		if (handleAISwitch(vexRT[Btn8L], vexRT[Btn8R], vexRT[Btn8U], vexRT[Btn8D]))
		{
			startBot(vexRT[Btn8L], vexRT[Btn8R], vexRT[Btn8U], vexRT[Btn8D]);
			break; // bot has been "started" (competition mode), and now the execution loop takes place in startBot()
		}

		else // pre-competition or testing mode: two stick layout is enabled
		{
			if (handleLayoutSwitch(vexRT[Btn7L], vexRT[Btn7U])) // combination to switch to a layout, if necessary
			{
				wait1Msec(20); // short reset time
			}
			if (isOneStickLayout == true)
			{
				oneStickLayout();
			}
			else
			{
				twoStickLayout();
			}
		}
	}
}
