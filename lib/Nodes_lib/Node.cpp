/*
Defines the NodeCreation class
*/
#include "Arduino.h"
#include "Node.h"
#include "SharpIR.h"

NodeCreation::NodeCreation(int leftPort, int rightPort, int frontPort, int ori, int x, int y){
    SharpIR _right(SharpIR::GP2Y0A41SK0F, rightPort);
    SharpIR _left(SharpIR::GP2Y0A41SK0F, leftPort);
    SharpIR _front(SharpIR::GP2Y0A41SK0F, frontPort);
    _lower = 0;
    _upper = 0;
    return;
}

void NodeCreation::setHistorisa(int lowerBound, int upperBound){
    _lower = lowerBound;
    _upper = upperBound;
    return;
}

bool NodeCreation::historisa(int dis){
    bool up = (dis < _upper) ? (true):(false);
    bool low = (dis > _lower) ? (true):(false);
    if(up && low){return true;}else{return false;}
}

node NodeCreation::returnStruct(int ori){
    node retStruct;
    int rightDis = _right.getDistance();
    if (historisa(rightDis)){
        switch(ori){
            case(0):
                retStruct.East = 1;
            break;
            case(1):
                retStruct.South = 1;
            break;
            case(2):
                retStruct.West = 1;
            break;
            case(3):
                retStruct.North = 1;
            break;
        }
    }else{
        
    }
    int leftDis = _left.getDistance();
        if (historisa(leftDis)){
        switch(ori){
            case(0):
                retStruct.West = 1;
            break;
            case(1):
                retStruct.North= 1;
            break;
            case(2):
                retStruct.East = 1;
            break;
            case(3):
                retStruct.South = 1;
            break;
        }
    }
    int front = _front.getDistance();

}