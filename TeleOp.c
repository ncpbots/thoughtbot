#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rearRight,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     frontRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     lift1,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     lift2,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     frontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     rearLeft,      tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    claw,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
#pragma config(Motor,  mtr_S2_C1_1,     light1,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     light2,     tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                    - FTC Team 5359 [SolinNoids] -                                      *|
|*                                           Tele-Op Program                                              *|
|*                                                                                                         *|
|*  This program is for the holonomic drive setup for the Team 5359's 2012-13 FTC Robot.                  *|
|*  This setup uses four omniwheels positions at 45 degree angles at the corners of the robot.            *|
|*  ____________________________________________________________________________________________________  *|
|*                                                                                                        *|
|*                                              CONTROLS                                                  *|
|*     Main Robot Movement:                                                                               *|
|*         Left Joystick:                                                                                 *|
|*            - Up -------------> Foward                                                                  *|
|*            - Down -----------> Backward                                                                *|
|*            - Left -----------> Strafe Left                                                             *|
|*            - Right ----------> Strafe Right                                                            *|
|*            - Left+Up --------> Strafe Forward-Left                                                     *|
|*            - Right+Up -------> Strafe Forward-Right                                                    *|
|*            - Left+Down ------> Strafe Back-Left                                                        *|
|*            - Right+Down -----> Strafe Back-Right                                                       *|
|*         Right Joystick:                                                                                *|
|*            - Left -----------> Rotate Left/Anti-Clockwise                                              *|
|*            - Right ----------> Rotate Right/Clockwise                                                  *|
|*                                                                                                        *|
|*     Lift Movement:                                                                                     *|
|*            - D-Pad Up -------> Move lift up                                                            *|
|*            - D-Pad Down -----> Move lift down                                                          *|
|*                                                                                                        *|
|*     Claw Controls                                                                                      *|
|*            - Num-Button 5 ---> Claw open                                                               *|
|*            - Num-Button 6 ---> Claw close                                                              *|
|*            - Num-Button 2 ---> Lights on                                                               *|
|*            - Num-Button 4 ---> Lights off                                                              *|
|*                                                                                                        *|
\*---------------------------------------------------------------------------------------------------5359-*/

float joyToMotor = 100.0/128.0;                       // Conversion ratio for joystick values
//------------------------------------------ ULTILITY METHODS --------------------------------------------//
bool noLeftX() {return abs(joystick.joy1_x1) < 30;}   // True if left stick x value is below threshold
bool noLeftY() {return abs(joystick.joy1_y1) < 30;}   // True if left stick y value is below threshold
bool noRightX(){return abs(joystick.joy1_x2) < 30;}   // True if right stick x value is below threshold
int xClock()   {return abs(joystick.joy1_x1);}	      // Left stick x value; clockwise
int xAClock()  {return -abs(joystick.joy1_x1);}	      // Left stick x value; anti-clockwise
int yClock()   {return abs(joystick.joy1_y1);}	      // Left stick y value; clockwise
int yAClock()  {return -abs(joystick.joy1_y1);}	      // Left stick y value; anti-clockwise
int joyAvg()   {return (joystick.joy1_x1 + joystick.joy1_y1) / 2;}   // Averages x and y joystick values

/* Moves wheel motors.
 * @param:
 * 	- fl: Joystick value for frontLeft motor
 * 	- fr: Joystick value for frontRight motor
 * 	- rl: Joystick value for rearLeft motor
 * 	- rr: Joystick value for rearRight motor
 */
void move(int fl, int fr, int rl, int rr)
{
   motor[frontLeft]  = fl * joyToMotor;
   motor[frontRight] = fr * joyToMotor;
   motor[rearLeft]   = rl * joyToMotor;
   motor[rearRight]  = rr * joyToMotor;
}

/* Moves all wheel motors.
 * @param joyValue: Joystick value for all motors
 */
void move(int joyValue)
{
   motor[frontLeft] = motor[frontRight] = motor[rearLeft] = motor[rearRight] = joyValue * joyToMotor;
}

/* Moves lift motors.
 * @param power: Power input to lift motors
 */
void lift(int power)   {motor[lift1] = motor[lift2] = power;}
//------------------------------------------ END ULTILITY METHODS ----------------------------------------//


//-------------------------------------------- TELE-OP PROGRAM -------------------------------------------//

task main()
{
   waitForStart();   // wait for start of tele-op phase

   while (true)
   {
      getJoystickSettings(joystick);

      //---------------------------- MAIN ROBOT CONTROL ----------------------------//

      //=============== LEFT JOYSTICK ===============//

      //*** FORWARD ***//
      if (joystick.joy1_y1 < -10 && noLeftX() && noRightX())
         move(yAClock(), yAClock(),  yClock(), yClock());
         //move(yAClock(), yClock(),  yAClock(), yClock());

      //*** REVERSE ***//
      if (joystick.joy1_y1 > 10 && noLeftX() && noRightX())
         move(yClock(), yClock(),  yAClock(), yAClock());
         //move(yClock(), yAClock(),  yClock(), yAClock());

      //*** STRAFE LEFT ***//
      if (joystick.joy1_x1 < -10 && noLeftY() && noRightX())
         move(xClock(), xAClock(),  xClock(), xAClock());
         //move(xAClock(), xAClock(),  xClock(), xClock());

      //*** STRAFE RIGHT ***//
      if (joystick.joy1_x1 > 10 && noLeftY() && noRightX())
         move(xAClock(), xClock(),  xAClock(), xClock());
         //move(xClock(), xClock(),  xAClock(), xAClock());


      ////*** STRAFE UP-LEFT ***//
      //if (joystick.joy1_x1 < -30 && joystick.joy1_y1 > 30 && noRightX())
      //   move(0, joyAvg(), -joyAvg(), 0);

      ////*** STRAFE UP-RIGHT ***//
      //if (joystick.joy1_x1 > 30 && joystick.joy1_y1 > 30 && noRightX())
      //   move(-joyAvg(), 0, 0, joyAvg());

      ////*** STRAFE BACK-LEFT ***//
      //if (joystick.joy1_x1 < -30 && joystick.joy1_y1 < -30 && noRightX())
      //   move(joyAvg(), 0, 0, -joyAvg());

      ////*** STRAFE BACK-RIGHT ***//
      //if (joystick.joy1_x1 > 30 && joystick.joy1_y1 < -30 && noRightX())
      //   move(0, -joyAvg(), joyAvg(), 0);

      //============= END LEFT JOYSTICK =============//

      //============== RIGHT JOYSTICK ===============//

      //*** TURN LEFT ***//
      if (joystick.joy1_x2 < -20 && noLeftX() && noLeftY())
         move(-abs(joystick.joy1_x2));

      //*** TURN RIGHT ***//
      if (joystick.joy1_x2 > 20 && noLeftX() && noLeftY())
         move(abs(joystick.joy1_x2));
      //============ END RIGHT JOYSTICK ==============//

      // Stop all wheels if no joystick input
      if (noLeftX() && noLeftY() && noRightX()) move(0);
      //--------------------------- END MAIN ROBOT CONTROL -------------------------//


      //------------------------------- LIFT CONTROL -------------------------------//

      if (joystick.joy1_TopHat == 0) lift(60);                                   // Up
      else if (joystick.joy1_TopHat == 4) lift(-60);                             // Down
      else if (joystick.joy1_TopHat != 0 && joystick.joy1_TopHat != 4) lift(0);  // Stop

      //----------------------------- END LIFT CONTROL -----------------------------//


      //------------------------------- CLAW CONTROL--------------------------------//

      if (joy1Btn(5)==1) servo[claw] = 140; //open on pressing 5
      else if (joy1Btn(6)==1) servo[claw] = 220; //close on pressing 6
      //----------------------------- END CLAW CONTROL -----------------------------//


      //------------------------------ LIGHT CONTROL -------------------------------//

      if (joy1Btn(2)==1) motor[light1] = motor[light2] = 50; // Button 2: Lights on
      if (joy1Btn(4)==1) motor[light1] = motor[light2] = 0; // Button 4: Lights off
      //---------------------------- END LIGHT CONTROL -----------------------------//
   }
}
//------------------------------------------ END TELE-OP PROGRAM -----------------------------------------//
