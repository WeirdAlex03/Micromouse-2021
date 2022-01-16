/*
Defines the node struct, with the initaliaztion NodeCreation class.
In this situation I do not need diagnol sensors since we are only dropping a node at the current location then storing it. Possibly use determine node location class for that part.
*/

#ifndef Node_h
#define Node_h

#include "Arduino.h"
#include "SharpIR.h"

struct node{
    int x;
    int y;
    int North;
    int South;
    int East;
    int West;
};

//SharpIR sensor( SharpIR::GP2Y0A41SK0F, A0 );


class NodeCreation
{
    public:
    NodeCreation(int leftPort, int rightPort, int frontPort, int ori, int x, int y);
    node returnStruct(int ori);
    void setHistorisa(int lowerBound, int UpperBound);
    bool historisa(int dis);
    private:
    node _struct;
    SharpIR&& _front;
    SharpIR&& _left;
    SharpIR&& _right;
    SharpIR&& _frontLeft;
    SharpIR&& _frontRight;
    int _lower;
    int _upper;
};

#endif