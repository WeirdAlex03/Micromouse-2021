#include <AFMotor.h>
#include <SharpIR.h>

// Constants for orientation
#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

// global variables, altepper motors and sensors are defined here
const int stepsPerRevolution = 60;
AF_Stepper rMotor(stepsPerRevolution, 2);
AF_Stepper lMotor(stepsPerRevolution, 1);
SharpIR sensorR( SharpIR::GP2Y0A41SK0F, A5 );
SharpIR sensorFR( SharpIR::GP2Y0A41SK0F, A4 );
SharpIR sensorF( SharpIR::GP2Y0A41SK0F, A3 );
SharpIR sensorFL( SharpIR::GP2Y0A41SK0F, A2 );
SharpIR sensorL( SharpIR::GP2Y0A41SK0F, A1 );
//Below initializes values for distance, orientation, as well as the maze array. uint is to minimize storage.
uint8_t R  = 0;    // Value of the right sensor
uint8_t FR = 0;    // Value of the front right sensor
uint8_t F  = 0;    // Value of the front sensor
uint8_t FL = 0;    // Value of the front left sensor
uint8_t L  = 0;    // Value of the left sensor
uint8_t x = 0;     // X position of the robot
uint8_t y = 0;     // Y position of the robot
uint8_t ori = 0;   // Orientation of the robot
uint8_t maze[16][16]; // each node has [x,y,N,E,S,W], x and y are the coords and NESW is walls on the orientation

//set speed of motor and Initialize all nodes in the maze
void setup() {
  Serial.begin(9600);
  rMotor.setSpeed(160);
  lMotor.setSpeed(160);   
  for(x = 0; x < 16; ++x){
    for(y = 0; y < 16; ++y){
      maze [x][y] = 15;
    }
  }
  if(F > 5 && R > 5){
    maze[0][0] = 3;
  }
  if(F>5 && R<5){
    maze[0][0] = 7;
  }
  if(F<5 && R>5){
    maze[0][0] = 11;
  }
  x = 0;
  y = 0;
}

// basic turning/going functions **NEED TO ADJUST THE FOR LOOPS IN EACH TURN GO FUNCTION< AND ADD FOR LOOP IN FORWARD**
void turnAround(){
  for(uint8_t i = 0; i < 170; ++i){
      rMotor.step(1, BACKWARD, SINGLE); 
      lMotor.step(1, FORWARD, SINGLE);
    } 
  switch(ori){
    // this could just be:  ori = (ori + 2) % 4  - Alex
    // fuck off alex
    case 0: 
    ori = 2;
    break;
    case 1:
    ori = 3;
    break;
    case 2:
    ori = 0;
    break;
    case 3:
    ori = 1;
    break;
  }
}
void forward(){
  for(uint8_t i = 0; i < 100; ++i){
    rMotor.step(1, FORWARD, SINGLE);
    lMotor.step(1, FORWARD, SINGLE);
  }
    switch(ori){
      case 0:
      y = y+1;
      break;
      case 1:
      x = x+1;
      break;
      case 2:
      y = y-1;
      break;
      case 3:
      x = x-1;
      break;
    }
}
void rightTurn(){
    for(uint8_t i = 0; i < 86; ++i){
      lMotor.step(1, FORWARD, SINGLE); 
      rMotor.step(1, BACKWARD, SINGLE);
    }
    if(ori == 3){
      ori = 0;
    }else{
      ori = ori + 1;
    }
}
void leftTurn(){
    for(uint8_t i = 0; i < 86; ++i){
      rMotor.step(1, FORWARD, SINGLE); 
      lMotor.step(1, BACKWARD, SINGLE); 
    }
    if(ori == 0){
      ori = 3;
    }else{
      ori = ori - 1;
    }
}

void straightCheck(){// also check if these values are good, not sure if 3 is good enough wiggle room -> potentially not working because range is 10 to 80 cm. left in just in case
  int RU = sensorR.getDistance() + 1;
  int RL = sensorR.getDistance() - 1;
  int LU = sensorL.getDistance() + 1;
  int LL = sensorL.getDistance() - 1;

    if(RU < LL){
      while(RU < LL){
        RU = sensorR.getDistance() + 1;
        LL = sensorL.getDistance() - 1;
        rMotor.step(1, FORWARD, SINGLE); 
        lMotor.step(1, BACKWARD, SINGLE);
      }
    }
    else if(LU < RL){
      while(LU < RL){
        RL = sensorR.getDistance() - 1;
        LU = sensorL.getDistance() + 1;
         lMotor.step(1, FORWARD, SINGLE);
         rMotor.step(1, BACKWARD, SINGLE);
      }
    }
}

void fillNode(){ //NEED TO CHANGE VALUES FOR IN THE IF STATMENT IT WAS A GUESS ------------------------------------------------------------------------------------------
  switch(ori){

    // Facing True North
    case 0:
      if(F < 6 && maze[x][y] / 8 % 2 == 0) {
        maze[x][y] += 8;
      }
      if(R < 6 && maze[x][y] / 4 % 2 == 0) {
        maze[x][y] += 4;
      }
      if(L < 6 && maze[x][y] % 2 == 0) {
        maze[x][y] += 1;
      }

    break;

    // Facing East
    case 1:      
    
    if(F<6){
      if(maze[x][y] % 2 == 0){
        maze[x][y] += 2;
      }
    }

    break;
    case 2:
    break;
    case 3:
    break;
    default:
    break;
  }
}

//-----------------DECISION MAKING BELOW------------------------------------------------------------------------
int bestFit(){// 0=forward, 1=right, 2=backward, 3=left
  double fCalc;
  double rCalc;
  double lCalc;
  double bCalc;
  int quad; // for quadrant
  
  if(x < 7.5){
    if(y < 7.5){
      quad = 0;
    }else if(y > 7.5){
      quad = 1
  }else if(y < 7.5){
      quad = 3;
    }else{
      quad = 2;
    }
  }
switch(quad){
  case 0:
    fCalc = (7.5 - x)/(7.5 - y);
    rCalc = (7.5 - y)/(7.5 - x);
    if(fCalc < rCalc &&  F  > 4){
        return 0;
      }else if(R > 4){
        return 1;
      }
      break;
    case 1:
      bCalc = (7.5 - x)/(7.5 - abs(y));
      rCalc = (7.5 - abs(y))/(7.5 - x);
      if(bCalc < rCalc){
        return 2;
      }else if(R > 4){
        return 1;
      }
      break;
    case 2:
      bCalc = (7.5 - abs(x))/(7.5 - abs(y));
      lCalc = (7.5 - abs(y))/(7.5 - abs(x));
      if(bCalc < lCalc){
        return 2;
      }else if(L > 4){
        return 3;
      }
      break;
    case 3:
      fCalc = (7.5 - abs(x))/(7.5 - abs(y));
      lCalc = (7.5 - y)/(7.5 - abs(x));
      if(fCalc < lCalc && F > 4){
        return 0;
      }else if(L > 4){
        return 3;
      }
      break;
  }
  default:
  return 5;
}

/*
 * Main control function, called every time a new maze
 * cell is entered.
 * 
 * Params:
 *   u_int8t curWallNum - The binary wall state number of the current cell
 *   u_int8t lastWallNum - The binary wall state number of the previous cell (the cell behind the robot)
 */
void mazeDecision(u_int8t curWallNum, u_int8t lastWallNum){
  if (curWallNum != lastWallNum) {
    int openings = getOpeningsFromWallNumber(curWallNum);

    switch (openings) {
      case 1:
        // Dead end, turn around
        turnAround();
        break;
      case 2:
        // Only one way to go, figure out which way that is
        turnTowardsOpening(curWallNum);
        break;
      default:
        // Intersection, call decision making function to determine which way to go
        bestFitSelection();// to do decide between 2 openings need best fit in conjuction with avaliable openingsi
        break;
    }
  } else {
    // No wall change, continue straight
    moveForward();
  }
}

/*
 * If there are only two openings, this function will
 * determine which way to go.
 *
 * This should only be called when there are two openings,
 * including the direction we just came from.
 * 
 * Params:
 *   u_int8t wallNum - The binary wall state number of the current cell
 */
void turnTowardsOpening(u_int8t wallNum) {
  for (int i = 0; i < 4; i++) {
    if (i == (ori + 2) % 4) {
      // Skip the direction we just came from
      continue;
    }
    if (bitread(wallNum, i) == 0) {
      // Found the direction to go, figure out which way to turn
      switch (i) {
        case ori - 1:
          // Turn left
          leftTurn();
          forward();
          break;
        case ori + 1:
          // Turn right
          rightTurn();
          forward();
          break;
        case ori:
          // Don't have to turn; continue straight
          forward();
          break;
        default:
          // Should never happen
          break;
      }
    }
  }
}

/*
 * Returns the number of openings based on the wall number,
 * which is a count of the 0s in the binary representation number
 * 
 * Params:
 *   int wallNum - The binary wall state number of the current cell
 *
 * Returns:
 *   int - The number of openings in the current cell
 */
int getOpeningsFromWallNumber(unt8t wallNum) {
  // TODO
  int numopenings = 0;
  
  for(int bit=0,bit<4,bit++){
    if( bitread(wallNum, 3)==0){
      numopenings++;
      
    }
}    
return numopenings; 

  
}

void loop() {
  R  =  sensorR.getDistance();
  FR =  sensorFR.getDistance();
  F  =  sensorF.getDistance();
  FL =  sensorFL.getDistance();
  L  =  sensorL.getDistance();

  serial.print('R');
}
