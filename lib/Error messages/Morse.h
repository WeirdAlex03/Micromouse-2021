/*	2	  Morse.h - Library for flashing Morse code.	3	  Created by David A. Mellis, November 2, 2007.	4	  Released into the public domain.	5	*/	6	#ifndef Morse_h	7	#define Morse_h	8	
#include "Arduino.h"
class Morse	12	{
    public:
        Morse(int pin);
        void dot();
        void dash();
        private:
        int _pin;
        };
    #endif