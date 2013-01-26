#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rearRight,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     frontRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     light,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     lift,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     rearLeft,      tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    claw,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

/*
-------------------TEAM 5359 TELEOP PROGRAM-------------------
main robot movement:
	left stick:
		- up -> forward
		- down -> backward
		- left -> strafe left
		- right -> strafe right
	right stick:
		- left -> turn left
		- right -> turn right

lift movement:
	D-pad up moves lift up
	D-pad down moves lit down

claw open/close: button 5 opens, button 6 closes

lights: 2 to turn on, 4 to turn off

*/

task main()
{

  waitForStart();   // wait for start of tele-op phase

  while (true)
  {
	  getJoystickSettings(joystick);

	  //------------MAIN ROBOT CONTROL------------//

	  //====LEFT JOYSTICK====//

	  //***FORWARD***//
	  if (joystick.joy1_y1>10 && abs(joystick.joy1_x1)<10 && abs(joystick.joy1_x2)<10)
		{
		  motor[frontLeft] = -abs(joystick.joy1_y1); //counterclockwise
		  motor[frontRight] = abs(joystick.joy1_y1); //clockwise
		  motor[rearLeft]  = -abs(joystick.joy1_y1); //counterclockwise
		  motor[rearRight]	= abs(joystick.joy1_y1); //clockwise
		}

	  //***REVERSE***//
		if (joystick.joy1_y1<-10 && abs(joystick.joy1_x1)<10 && abs(joystick.joy1_x2)<10)
		{
		  motor[frontLeft] =	 abs(joystick.joy1_y1); //counterclockwise
		  motor[frontRight] = -abs(joystick.joy1_y1); //clockwise
		  motor[rearLeft] = 	 abs(joystick.joy1_y1); //counterclockwise
		  motor[rearRight] =  -abs(joystick.joy1_y1); //clockwise
		}

	  //***STRAFE LEFT***//
		if (joystick.joy1_x1>10 && abs(joystick.joy1_x1)<10 && abs(joystick.joy1_x2)<10)
		{
		  motor[frontLeft] =  abs(joystick.joy1_x1); //counterclockwise
		  motor[frontRight] = abs(joystick.joy1_x1); //clockwise
		  motor[rearLeft]  = -abs(joystick.joy1_x1); //counterclockwise
		  motor[rearRight] = -abs(joystick.joy1_x1); //clockwise
		}

	  //***STRAFE RIGHT***//
	  if (joystick.joy1_x1<-10 && abs(joystick.joy1_x1)<10 && abs(joystick.joy1_x2)<10)
		{
		  motor[frontLeft] = 	-abs(joystick.joy1_x1); //counterclockwise
		  motor[frontRight] = -abs(joystick.joy1_x1); //clockwise
		  motor[rearLeft] 	=  abs(joystick.joy1_x1); //counterclockwise
		  motor[rearRight] = 	 abs(joystick.joy1_x1); //clockwise
		}

		//====LEFT JOYSTICK====//

		//***TURN LEFT***//
		if (joystick.joy1_x2>10 && abs(joystick.joy1_x1)<10 && abs(joystick.joy1_y1)<10)
		{
		  motor[frontLeft] =  abs(joystick.joy1_x2); //clockwise
		  motor[frontRight] = abs(joystick.joy1_x2); //clockwise
		  motor[rearLeft]  =  abs(joystick.joy1_x2); //clockwise
		  motor[rearRight] =  abs(joystick.joy1_x2); //clockwise
		}

	  //***TURN RIGHT***//
	  if (joystick.joy1_x2<-10 && abs(joystick.joy1_x1)<10 && abs(joystick.joy1_y1)<10)
		{
		  motor[frontLeft] = 	-abs(joystick.joy1_x2); //counterclockwise
		  motor[frontRight] = -abs(joystick.joy1_x2); //counterclockwise
		  motor[rearLeft]  =  -abs(joystick.joy1_x2); //counterclockwise
		  motor[rearRight] = 	-abs(joystick.joy1_x2); //counterclockwise
		}



	  //--------------LIFT CONTROL----------------//
	  if (joystick.joy1_TopHat == 0) motor[lift] = 40; //move up with D-pad up
	  else if (joystick.joy1_TopHat == 4) motor[lift] = -40; //move down with D-pad down

	  //--------------CLAW CONTROL----------------//
	  if (joy1Btn(5)==1) servo[claw] = 140; //open on pressing 5
	  else if (joy1Btn(6)==1) servo[claw] = 220; //close on pressing 6

		//--------------LIGHTS ON/OFF---------------//
	  if (joy1Btn(2)==1) motor[light] = 50; //press 2 to turn on lights
	 	if (joy1Btn(4)==1) motor[light] = 0; //press 4 to turn off lights

  }
}
