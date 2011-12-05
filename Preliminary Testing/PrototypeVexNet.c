#pragma config(Motor,  port10,			rightMotor,	   tmotorNormal, openLoop, reversed) // Define motors here: port numbers, isReversed
#pragma config(Motor,  port1,			leftMotor,	   tmotorNormal, openLoop)
#pragma config(Motor,  port9,			lateralMotor,	  tmotorNormal, openLoop)
#pragma config(Motor,  port7,			elevatorOneMotor,	  tmotorNormal, openLoop)
#pragma config(Motor,  port8,			elevatorTwoMotor,	  tmotorNormal, openLoop, reversed)
#pragma config(Sensor, dgtl1,  solenoid1,           sensorDigitalOut)
#pragma config(Sensor, dgtl2,  solenoid2,           sensorDigitalOut)


// Prototype bot: VEXNet movement tester

/*										  ROBOT CONFIGURATION										  *|
|*	  NOTES:																						  *|
|*	  1)  Ch1 is the X axis and Ch2 is the Y axis for the RIGHT joystick.							  *|
|*	  2)  Ch3 is the Y axis and Ch4 is the X axis for the LEFT joystick.							  *|
|*	  3)  'abs(z)' is the ABSOLUTE VALUE of 'z'.													  */

int ljoy_x;   // This is the X value of the LEFT analog stick.
	int ljoy_y;   // This is the Y value of the LEFT analog stick.

	int rjoy_x;   // This is the X value of the RIGHT analog stick.
	int rjoy_y;   // This is the Y value of the RIGHT analog stick.

	int threshold = 12.7;
  bool isOneStickLayout = false; // Very hacky toggling (because we don't know if RobotC has support for enums and delegates)


void oneStickLayout()
{
/* This is for the joystick layout where the left analog stick controls robot movement and the right one controls the elevator.
* Controls:

	Left stick:
		Up: leftMotor = 127, rightMotor = 127: both wheels forward
		Down: leftMotor = -127, rightMotor = -127: both wheels backward
		Left: leftMotor = -127, rightMotor = 127: turn left
		Right: leftMotor = 127, rightMotor = -127: turn right
	Right stick:
		Up: elevatorOneMotor = 127, elevatorTwoMotor = 127: both elevator motors up
		Down: elevatorOneMotor = -127, elevatorTwoMotor = -127: both elevator motors down
		Left: lateralMotor goes left
		Right: lateralMotor goes right
	<strike>Back buttons:
		5 LH, U button: lateralMotor = 127: lateral goes left
		6 RH, U button: lateralMotor = -127: lateral goes right</strike>
	Front buttons:
		// No assignments

*/
	ljoy_x = vexRT[Ch4];   // This is the X value of the LEFT analog stick.
	ljoy_y = vexRT[Ch3];   // This is the Y value of the LEFT analog stick.

	rjoy_x = vexRT[Ch1];   // This is the X value of the RIGHT analog stick.
	rjoy_y = vexRT[Ch2];   // This is the Y value of the RIGHT analog stick.

	// Step 1: process left analog stick
	if((abs(ljoy_x) > threshold) && (abs(ljoy_y) > threshold)) // Left analog stick position is above threshold
	{
		// Let's move!
		if(ljoy_y > 0) // Is the analog stick pointing up or down?
		{
			// Move forward
			motor[leftMotor]  = (ljoy_y + ljoy_x)/2;
			motor[rightMotor] = (ljoy_y - ljoy_x)/2;
		}
		else
		{
			// Move backward
			motor[leftMotor]  = (ljoy_y - ljoy_x)/2;
			motor[rightMotor] = (ljoy_y + ljoy_x)/2;
		}
	}
	else if((abs(ljoy_x) > threshold) && (abs(ljoy_y) < threshold)) // Analog stick is pointing right or left(abs(X) is above the threshold, abs(Y) is below the threshold)
	{
	  motor[leftMotor]  = ljoy_x;
	  motor[rightMotor] = (-1 * ljoy_x);
	  //motor[lateralMotor] = ljoy_x;
	}
	else // Left analog stick position is below threshold
	{
		// Stop moving
		motor[leftMotor]  = 0;
		motor[rightMotor] = 0;
		//motor[lateralMotor] = 0;
	}

	// Step 2: process right analog stick
	if((abs(rjoy_x) > threshold)) // Analog stick is pointing right or left(abs(X) is above the threshold, abs(Y) is below the threshold)
	{
	  motor[lateralMotor] = (-1) * rjoy_x;
	}
  else
  {
	motor[lateralMotor] = 0;
  }


  // Elevator

  if((vexRT[Btn5D]==1)&&(vexRT[Btn5U]==1))
  {
	motor[elevatorOneMotor]=0;
	motor[elevatorTwoMotor]=0;
  }
  else if (vexRT[Btn5U]==1)
  {
	motor[elevatorOneMotor]=127;
	motor[elevatorTwoMotor]=127;
  }
  else if (vexRT[Btn5D]==1)
  {
	motor[elevatorOneMotor]=-127;
	motor[elevatorTwoMotor]=-127;
  }
  else if ((vexRT[Btn5D]==0)&&(vexRT[Btn5U]==0))
  {
	motor[elevatorOneMotor]=0;
	motor[elevatorTwoMotor]=0;
  }

	/* A pneumatic test

	if ((vexRT[Btn6D] ==1))
	{
		SensorValue[solenoid] = 0;
	}
	else if ((vexRT[Btn6U]==1))
	{
		SensorValue[solenoid] = 1;
	} */

}


void twoStickLayout()
{

  // Main wheels

  if(abs(vexRT[Ch3]) > threshold)		  // If the left joystick is greater than or less than the threshold:
  {
	  motor[leftMotor]  = (vexRT[Ch3]);   // Left Joystick Y value / 2.
  }
  if(abs(vexRT[Ch3]) < threshold)								   // If the left joystick is within the threshold:
  {
	  motor[leftMotor]  = 0;				// Stop the left motor (cancel noise)
  }

  if(abs(vexRT[Ch2]) > threshold)		  // If the right joystick is greater than or less than the threshold:
  {
	  motor[rightMotor] = (vexRT[Ch2]);   // Right Joystick Y value / 2.
  }
  if(abs(vexRT[Ch2]) < threshold)									 // If the right joystick is within the threshold:
  {
	  motor[rightMotor] = 0;				// Stop the right motor (cancel noise)
  }
  if((abs(vexRT[Ch4]) > threshold) && (abs(vexRT[Ch1]) < threshold)) //&& (abs(ljoy_y) < threshold)) // Analog stick is pointing right or left(abs(X) is above the threshold, abs(Y) is below the threshold)
  {
		motor[lateralMotor] = -vexRT[Ch4]/2;
  }
  if((abs(vexRT[Ch1]) > threshold) && (abs(vexRT[Ch4]) < threshold)) // Analog stick is pointing right or left(abs(X) is above the threshold, abs(Y) is below the threshold)
	{
	  motor[lateralMotor] = -vexRT[Ch1]/2;
	}
  if((abs(vexRT[Ch4]) > threshold) && (abs(vexRT[Ch1])>threshold))
  {
	  motor[lateralMotor]=-(vexRT[Ch4]+vexRT[Ch1])/2;
  }
  if((abs(vexRT[Ch4]) < threshold) && (abs(vexRT[Ch1]) < threshold))
  {
	motor[lateralMotor]=0;
  }
   if (vexRT[Btn5U] == 1)
    {
    SensorValue[solenoid1] = 1;
    SensorValue[solenoid2] = 1;
    }
    if (vexRT[Btn5D] == 1)
    {
    SensorValue[solenoid1] = 0;
    SensorValue[solenoid2] = 0;
    }


  // Elevator

  if((vexRT[Btn5D]==1)&&(vexRT[Btn5U]==1))
  {
	motor[elevatorOneMotor]=0;
	motor[elevatorTwoMotor]=0;
  }
  else if (vexRT[Btn5U]==1)
  {
	motor[elevatorOneMotor]=127;
	motor[elevatorTwoMotor]=127;
  }
  else if (vexRT[Btn5D]==1)
  {
	motor[elevatorOneMotor]=-127;
	motor[elevatorTwoMotor]=-127;
  }
  else if ((vexRT[Btn5D]==0)&&(vexRT[Btn5U]==0))
  {
	motor[elevatorOneMotor]=0;
	motor[elevatorTwoMotor]=0;
  }

}

void blueAIFree()
{
while(true)
{
if(false) // combination to switch to a layout
{
break;
}

// AI stuff

}
}
void redAIFree()
{
while(true)
{
if(false) // combination to switch to a layout
{
break;
}

// AI stuff

}
}

void blueAITrapped()
{
while(true)
{
if(false) // combination to switch to a layout
{
break;
}

// AI stuff

}
}
void redAITrapped()
{
while(true)
{
if(false) // combination to switch to a layout
{
break;
}

// AI stuff

}
}



/* void doAI()
{
  motor[leftMotor] = 127;
  motor[rightMotor] = 127;
} */

void startBot(aiMethod)
{
  ClearTimer(T1);
  while(time10[T1] < 2000)
	{
	aiMethod();
	continue;
	}




  while(true) // while(1==1)
  {
		  if((vexRT[Btn7L] == 1))
		{
				isOneStickLayout = true;
					wait1Msec(20);
		}

		if ((vexRT[Btn7U] == 1))
	  {
		isOneStickLayout =false;
		wait1Msec(20);
	}




	if(isOneStickLayout == true)
	{
		oneStickLayout();
	}
	else
	{
		twoStickLayout();
	}
} // end while
} // end function

task main ()
{
  while(true)
  {
if (vexRT[Btn8L] == 1)
   {
   startBot(redAITrapped);
   break;
   }
else if (vexRT[Btn8R] == 1)
   {
   startBot(blueAITrapped);
   break;
   }
else if (vexRT[Btn8U] == 1)
   {
   startBot(redAIFree);
   break;
   }
else if (vexRT[Btn8D] == 1)
   {
   startBot(blueAIFree);
   break;
   }

   else
   {
	twoStickLayout(); // before we start competition mode, two stick layout is enabled
   }
  }
}


//++++++++++++++++++++++++