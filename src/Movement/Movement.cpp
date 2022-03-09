
#include <Arduino.h>
#include <AFMotor.h>
#include <inttypes.h>

#include "Movement.h"

Movement::Movement(uint16_t stepsPerRev, uint8_t lMotorNum, uint8_t rMotorNum) {
  AF_Stepper rMotor(stepsPerRev, rMotorNum);
  AF_Stepper lMotor(stepsPerRev, lMotorNum);
  _rMotor = rMotor;
  _lMotor = lMotor;
}

void Movement::moveForward() {
  /*
   *  This group of doubles does math to determine how many counts we need so we can travel one exactly coordinate
   */
  double distancePerCoordinate = 10; // This is a placeholder number, will need to change when we get measurements, it's in cm
  double wheelDiameter = 2.5 * 2.54; // convert's wheel diameter from inches to cm
  double wheelCircumference = PI * (wheelDiameter / 2) * (wheelDiameter / 2);
  double travelDistance = distancePerCoordinate / wheelCircumference;
  double turnCounts = 60 * travelDistance;

  for(uint8_t i = 0; i < (int)turnCounts; ++i){
    _rMotor.step(1, FORWARD, SINGLE);
    _lMotor.step(1, FORWARD, SINGLE);
  }
    switch(ori){
      case NORTH:
        y = y+1;
        break;
      case EAST:
        x = x+1;
        break;
      case SOUTH:
        y = y-1;
        break;
      case WEST:
        x = x-1;
        break;
    }
}

void Movement::setMotorSpeeds(uint8_t speed) {
  _lMotor.setSpeed(speed);
  _rMotor.setSpeed(speed);
}

void Movement::turnRight() {
    for(uint8_t i = 0; i < 86; ++i){
      _lMotor.step(1, FORWARD, SINGLE); 
      _rMotor.step(1, BACKWARD, SINGLE);
    }
    ori = (ori+1) % 4;
}

void Movement::turnLeft() {
    for(uint8_t i = 0; i < 86; ++i){
      _rMotor.step(1, FORWARD, SINGLE); 
      _lMotor.step(1, BACKWARD, SINGLE); 
    }
    ori = (ori-1) % 4;
}

void Movement::turnAround() {
  for(uint8_t i = 0; i < 170; ++i){
      _rMotor.step(1, BACKWARD, SINGLE); 
      _lMotor.step(1, FORWARD, SINGLE);
    } 
  switch(ori){
    // this could just be:  ori = (ori + 2) % 4  - Alex
    // fuck off alex
    case NORTH: 
      ori = SOUTH;
      break;
    case EAST:
      ori = WEST;
      break;
    case SOUTH:
      ori = NORTH;
      break;
    case WEST:
      ori = EAST;
      break;
  }
}
