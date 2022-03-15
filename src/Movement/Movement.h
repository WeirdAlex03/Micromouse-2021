#ifndef Move_h
#define Move_h

#include <Arduino.h>
#include <AFMotor.h>
#include <inttypes.h>

class Movement
{
	public:
		Movement(AF_Stepper *lMotor, AF_Stepper *rMotor);

		// Moves the robot forward one grid tile
		void moveForward();
		// Rotates the robot in place, 90 deg left
		void turnLeft();
		// Rotates the robot in place, 90 deg right
		void turnRight();
		// Rotates the robot in place, 180 deg around
		void turnAround();

		uint8_t x = 0;     // X position of the robot
		uint8_t y = 0;     // Y position of the robot
		uint8_t ori = 0;   // Orientation of the robot
				
		// Constants for orientation. N=0, E=1, S=2, W=3
		enum directions { NORTH, EAST, SOUTH, WEST };

	private:
		AF_Stepper *_lMotor;
		AF_Stepper *_rMotor;
		uint16_t _stepsPerRev = 60;
		uint8_t _motorSpeed = 160;
};

#endif //Move_h
