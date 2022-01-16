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
    int turns = dis/(_radius * _theta);
    for (int idx = 0; idx < turns; idx++){
        _right.step(1, FORWARD, SINGLE);
        _left.step(1, FORWARD, SINGLE);
    }
    switch ( _ori){
        case 0:
        _y = _y + dis;
        break;
        case 1:
        _x = _x + dis;
        break;
        case 2:
        _y = _y - dis;
        break;
        case 3:
        _x = _x - dis;
        break;
    }
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
    else{_ori--;}
    return 0;
}

int Drive::turnRight(){
    int turns = floor(_theta * 90);
    for (int idx = 0; idx < turns; idx++){
        _left.step(1, FORWARD, SINGLE);
        delayMicroseconds(200);
        _right.step(1, BACKWARD, SINGLE);
        delayMicroseconds(200);
    }
    if(_ori = 3){_ori = 0;}
    else{_ori++;}
    return 0;
}

int Drive::turnAround(){
    int turns = floor(_theta * 180);
    for (int idx = 0; idx < turns; idx++){
        _left.step(1, FORWARD, SINGLE);
        delayMicroseconds(200);
        _right.step(1, BACKWARD, SINGLE);
        delayMicroseconds(200);
    }
    switch(_ori){
        case(0):
            _ori = 2;
            break;
        case(1):
            _ori = 3;
            break;
        case(2):
            _ori = 0;
            break;
        case(3):
            _ori = 1;
            break;
    }
    return 0;
}

int Drive::setSpeed(int speed){
    _left.setSpeed(speed);
    _right.setSpeed(speed);
    return 0;
}