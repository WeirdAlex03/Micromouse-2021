/*
Welcome to the node testing file, this is meant to replace the main.cpp file
once we get the whole node structure thing working. It holds the 
*/

#include <Arduino.h>
#include "Drive.h"
#include "SharpIR.h"
#include "Node.h"

//Set up the motors
Drive wheels(60, 10, 1,2);


//Ideally I would like to initalize the sensors here as well
// Sensor Ports
int rightPort = 0;
int leftPort = 0;
int frontPort = 0;
int frontRightPort = 0;
int frontLeftPort = 0;
SharpIR right(SharpIR::GP2Y0A02YK0F, rightPort);
SharpIR left(SharpIR::GP2Y0A02YK0F, leftPort);
SharpIR front(SharpIR::GP2Y0A02YK0F,frontPort);
SharpIR frontLeft(SharpIR::GP2Y0A02YK0F,frontLeftPort);
SharpIR frontRight(SharpIR::GP2Y0A02YK0F,frontRightPort);

void setup() {
  // Initializing objects
  Serial.begin(9600);
  wheels.setSpeed(160);
  // Generating Maze Storage Structure
  node Maze[16][16]; //(y,x)
  memset(Maze, 0, sizeof Maze); //Initialize all the struct pointers to zero
}

void loop() {
  // put your main code here, to run repeatedly:
wheels.forward(10);
delayMicroseconds(200);
wheels.turnLeft();
delayMicroseconds(200);
wheels.turnRight();
delayMicroseconds(200);
wheels.turnAround();
delayMicroseconds(200);
}