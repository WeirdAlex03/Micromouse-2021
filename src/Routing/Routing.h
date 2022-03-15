#ifndef Routing_h
#define Routing_h

#include <Arduino.h>
#include <Movement.h>
#include <main.ino>


class Routing
{
    public:
        Routing(uint8_t *mazePtr, int mazeX, int mazeY);
        enum determineDirection(Movement *movPtr);
        void storePath();
    private:
        uint8_t * mazePtr;
        int mazeX;
        int mazeY;
        //Movement::Movement *movPtr;
        //std::vector<int, int> path;

    


};
#endif