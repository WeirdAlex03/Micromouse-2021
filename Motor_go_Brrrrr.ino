// Include the Arduino Stepper Library
#include <Stepper.h>
#include <SharpIR.h>

// Number of steps per output rotation
const int stepsPerRevolution = 200;

// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
SharpIR sensor( SharpIR::GP2Y0A41SK0F, A0 );

//Globally store variable for the distance to access at later sections
int distance = 0;

void setup()
{
  // set the speed at 60 rpm:
  myStepper.setSpeed(230);
  // initialize the serial port:
  Serial.begin(9600);
  Serial.println("It started");
}

void loop() 
{
  
  // step one revolution in one direction:
  distance = sensor.getDistance(); 
  Serial.println(distance);
  myStepper.step(stepsPerRevolution);
  delay(0);

  myStepper.step(stepsPerRevolution);
  delay(0);
}
