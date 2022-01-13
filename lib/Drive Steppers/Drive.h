/*
try 2 lol
*/

#ifndef Drive_h
#define Drive_h

#include "Arduino.h"
#include "AFMotor.h"

class Drive
{
  public:
    Drive(uint16_t steps, int diameter, uint8_t Rport, uint8_t Lport);
    int forward(int dis);
    int turnLeft();
    int turnRight();
    int turnAround();
    int setSpeed(int speed);
  private:
    int _x;
    int _y;
    int _ori;
    int _radius;
    int _theta;
    //Object&& o2 = Object();
    AF_Stepper&& _right;
    AF_Stepper&& _left;
};
#endif