#ifndef Move_h
#define Move_h

#include <Arduino.h>
#include <AFMotor.h>
#include <inttypes.h>

class Movement
{
	public:
		Movement(uint16_t stepsPerRev, uint8_t lMotorNum, uint8_t rMotorNum);

		void moveForward();
		void turnLeft();
		void turnRight();
		void turnAround();
		void setMotorSpeeds(uint8_t speed);

		uint8_t x = 0;     // X position of the robot
		uint8_t y = 0;     // Y position of the robot
		uint8_t ori = 0;   // Orientation of the robot
				
		// Constants for orientation. N=0, E=1, S=2, W=3
		enum directions { NORTH, EAST, SOUTH, WEST };

	private:
		AF_Stepper _lMotor;
		AF_Stepper _rMotor;
};

#endif //Move_h
