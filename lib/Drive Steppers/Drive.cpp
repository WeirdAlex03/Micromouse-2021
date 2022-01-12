/*
try 2 lol
*/
#include "Arduino.h"
#include "Drive.h"
#include "AFMotor.h"

Drive::Drive(uint16_t steps, int diameter, uint8_t Rport, uint8_t Lport){
    _x = 0; _y = 0; _ori = 0;
    _radius = diameter/2;
    _theta = steps/360;
    AF_Stepper _right(steps, Rport);
    AF_Stepper _left(steps, Lport);
    return;
}

int Drive::forward(int dis){
    return 0;
}

int Drive::turnLeft(){
    int turns = floor(_theta * 90);
    for (int idx = 0; idx < turns; idx++){
        _right.step(1, FORWARD, SINGLE);
        delayMicroseconds(200);
        _left.step(1, BACKWARD, SINGLE);
        delayMicroseconds(200);
    }
    if(_ori = 0){_ori = 3;}

    return 0;
}

int Drive::turnRight(){
    return 0;
}