#include <Arduino.h>
#include "Drive.h"



void setup() {
  Serial.begin(9600);
  Serial.print("initialization started");
  Drive wheels(60, 10, 1,2);
  // put your setup code here, to run once:
  wheels.setSpeed(160);
  wheels.forward(10);
  Serial.print("initialization finished");
  
}

int lpNum = 0;
void loop() {
  // put your main code here, to run repeatedly:
// Serial.print("loop number: ");
// Serial.print(lpNum);
// wheels.forward(10);
// delayMicroseconds(200);
// wheels.turnLeft();
// delayMicroseconds(200);
// wheels.turnRight();
// delayMicroseconds(200);
// wheels.turnAround();
// delayMicroseconds(200);
lpNum++;
}
