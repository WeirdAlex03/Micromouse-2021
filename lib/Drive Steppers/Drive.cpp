#include "Drive.h"
#include "AFMotor.h"
using namespace std;

//Note all the Stepper stuff has to be replaced with AFMotor Library stuff

//Global Variables
double X;
double Y;
Stepper right;
Stepper left;
int step;
double theta;
double rad;

//Orientations we assume that 
/*
            North (0)
              ^
              |
West (3) <----------> East (1)
              |
            South (2)
*/
int orientation = 0;

// Connect a stepper motor with 48 steps per revolution (7.5 degree)
// to motor port #2 (M3 and M4)
// AF_Stepper motor(48, 2);

//For each wheel, Pin the wheel is on, side of the wheel,
//and diameter of the wheel
int Drive_h::setUp(int steps, int diameter, int port, String side){
    //Initialize the stepper motor
    if (side == "right"){
        AF_ Stepper r(steps, port);
        right = r;
    }
    if (side == "left"){
        AF_Stepper l(steps, port);
        left = l;
    }
    if (side != "left" || side != "right"){
        //initalization code 10
        return 1;
    }
    rad = diameter/2;
    theta = steps/360;
    return 0;
}

//turning left, -90 deg
int Drive_h::Left(){
     int turns = floor(theta * 90);
     for (int idx = 0; idx < turns; idx++){
         right.step(1, FORWARD, SINGLE);
         delayMicroseconds(200);
         left.step(1, BACKWARD, SINGLE);
         delayMicroseconds(200);
     }
     orientation = orientation - 1;
    return 0;
}

//turning left, 90 deg
int Drive_h::Right(){
     int turns = floor(theta * 90);
     //Delay of 200ms is arbitrary can be changed 
     for (int idx = 0; idx < turns; idx++){
         left.step(1, FORWARD, SINGLE);
         delayMicroseconds(200);
         right.step(1, BACKWARD, SINGLE);
         delayMicroseconds(200);
     }
    return 0;
}

//turning 180 deg
int Drive_h::turnAround(){
    int turns = floor(theta * 180);
     //Delay of 200ms is arbitrary can be changed 
     for (int idx = 0; idx < turns; idx++){
         left.step(1, FORWARD, SINGLE);
         delayMicroseconds(200);
         right.step(1, BACKWARD, SINGLE);
         delayMicroseconds(200);
     }
    return 0;
}

//moving forward 
void Drive_h::forward(double len){
    int turns = len/theta;
    for (int i=0; i < turns; i++){  
         left.step(1, FORWARD, SINGLE);
         right.step(1, FORWARD, SINGLE);
    }
    return 0;
}

//Returns location
void Locations(String Z){

}

//calculate where to go next
void calculateLoc(int steps){
  // s = theta (rad)
  double loc  =  

}