/*
 1/6/2022 Drive library For moving the mouse via cordinating the Motors
 All the function return a int 
 Return 0 function exectution was successfull
 Return anything else Error must be thrown via error LED
 Clock wise is forward
*/
#ifndef Drive.h
#define Drive_h

#include "Arduino.h"

class Drive_h {
  public:
  /*
  steps relates the to amount of steps on the motor (set by hardware)
  diameter is the diameter of the wheel
  Pin array corresponds to the shield pinout 
      EXAMPLE Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); ~ Pin = {8,9,10,11}
  side can be left or right dependent upon motor initialization
  */
    int setUp(int steps, int diameter, int pin[4], String side);
  //Functions used to drive the mouse
    int Left();
    int Right();
    int turnAround();
    int forward();
  //Orientation used for calculations (Valid strings are x or y)
    int Locations(String Z); //just returns the locations
    int calculateLoc();

  private:
    //Pins for the motors, can add more once we see the motors
    int _leftMotorPin;
    int _rightMotorPin;
    //WheelDiamiter used to calculate distance
    int _diameter;
    //Distance traveled
    int _x;
    int _y;
    //Orientation 
    String _orientation;
};

#endif