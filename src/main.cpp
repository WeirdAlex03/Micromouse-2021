#include <Arduino.h>
#include "Drive.h"

Drive wheels(60, 10, 1,2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  wheels.setSpeed(160);
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