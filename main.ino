#include <SharpIR.h>
#include <AFMotor.h>
#include <math.h>
#include <inttypes.h>

// To fix this import issue, look up the library and import it into the project file
// -- i was too lazy to do that, commenting was easier in the moment
// Copy paste time


// Constants for orientation. N=0, E=1, S=2, W=3
enum directions { NORTH, EAST, SOUTH, WEST };

//Path remembering datastructure
std::Map<*int,

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

/* each node is an 8 bit int, representing the state of the walls.
 * 
 * 4 least significant are binary representation of the N/E/S/W walls (1  = wall, 0 = no wall)
 * 0b1111 (15) signifies that the tile hasn't been explored yet
 * The top 4 bits are unused
 * 
 * ---- NESW
 */
uint8_t maze[16][16];

//set speed of motor and Initialize all nodes in the maze
void setup() {
  Serial.begin(9600);
  rMotor.setSpeed(160);
  lMotor.setSpeed(160);   
  for(x = 0; x < 16; ++x){
    for(y = 0; y < 16; ++y){
      maze [x][y] = 15 //1111
    }
  } //Determines the walls around starting corner
  if(F > 5 && R > 5){
    maze[0][0] = 3; //0011
  }
  if(F>5 && R<5){
    maze[0][0] = 7; //0111
  }
  if(F<5 && R>5){
    maze[0][0] = 11; //1011
  }
  x = 0;//sets 
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
void forward(){
  /*
   *  This group of doubles does math to determine how many counts we need so we can travel one exactly coordinate
   */
  double distancePerCoordinate = 10; // This is a placeholder number, will need to change when we get measurements, it's in cm
  double wheelDiameter = 2.5 * 2.54; // convert's wheel diameter from inches to cm
  double wheelCircumference = M_PI * (wheelDiameter / 2) * (wheelDiameter / 2);
  double travelDistance = distancePerCoordinate / wheelCircumference;
  double turnCounts = 60 * travelDistance;

  for(uint8_t i = 0; i < (int)turnCounts; ++i){
    rMotor.step(1, FORWARD, SINGLE);
    lMotor.step(1, FORWARD, SINGLE);
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
void rightTurn(){
    for(uint8_t i = 0; i < 86; ++i){
      lMotor.step(1, FORWARD, SINGLE); 
      rMotor.step(1, BACKWARD, SINGLE);
    }
    ori = (ori+1) % 4;
}
void leftTurn(){
    for(uint8_t i = 0; i < 86; ++i){
      rMotor.step(1, FORWARD, SINGLE); 
      lMotor.step(1, BACKWARD, SINGLE); 
    }
    ori = (ori-1) % 4;
}

void straightCheck(){// also check if these values are good, not sure if 3 is good enough wiggle room -> potentially not working because range is 10 to 80 cm. left in just in case
  int RU = sensorR.getDistance() + 1;
  int RL = sensorR.getDistance() - 1;
  int LU = sensorL.getDistance() + 1;
  int LL = sensorL.getDistance() - 1;

    if(RU < LL){ //This section could have a bug when after the loop executes
      while(RU < LL){
        RU = sensorR.getDistance() + 1;
        LL = sensorL.getDistance() - 1;
        rMotor.step(1, FORWARD, SINGLE); 
        lMotor.step(1, BACKWARD, SINGLE);
      }
      return; //prevent accidently turning the wrong direction
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
  maze[x][y] = 0;

  switch(ori){

    // Facing True North
    case NORTH:
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
    case EAST:      
    
      if(F < 6 && maze[x][y] / 4 % 2 == 0) {
          maze[x][y] += 8;
        }
      if(R < 6 && maze[x][y] / 2 % 2 == 0) {
          maze[x][y] += 4;
        }
      if(L < 6 && maze[x][y] / 8 % 2 == 0) {
          maze[x][y] += 1;
        }

      break;

    case SOUTH:

      if(F < 6 && maze[x][y] / 2 % 2 == 0) {
          maze[x][y] += 8;
        }
      if(R < 6 && maze[x][y] % 2 == 0) {
          maze[x][y] += 4;
        }
      if(L < 6 && maze[x][y] / 4 % 2 == 0) {
          maze[x][y] += 1;
        }

      break;

    case WEST:

      if(F < 6 && maze[x][y] % 2 == 0) {
          maze[x][y] += 8;
        }
      if(R < 6 && maze[x][y] / 8 % 2 == 0) {
          maze[x][y] += 4;
        }
      if(L < 6 && maze[x][y] / 2 % 2 == 0) {
          maze[x][y] += 1;
        }

      break;

  }
}

//-----------------DECISION MAKING BELOW------------------------------------------------------------------------
uint8_t bestFit(){// 0=forward, 1=right, 2=backward, 3=left
  double fCalc;
  double rCalc;
  double lCalc;
  double bCalc;
  uint8_t quad; // for quadrant
  
  if(x < 7.5){
    if(y < 7.5){
      quad = 0;
    }else if(y > 7.5){
      quad = 1;
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
      bCalc = (7.5 - x)/(7.5 - Math.abs(y));
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
    default:
      return 5;
  }
}

/*
 * Main control function, called every time a new maze
 * cell is entered.
 * 
 * Params:
 *   uint8_t curWallNum - The binary wall state number of the current cell
 *   uint8_t lastWallNum - The binary wall state number of the previous cell (the cell behind the robot)
 */
void mazeDecision(uint8_t curWallNum, uint8_t lastWallNum){
  if (curWallNum != lastWallNum) {
    uint8_t openings = getOpeningsFromWallNumber(curWallNum);

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
        bestFit();// to do decide between 2 openings need best fit in conjuction with avaliable openingsi
        break;
    }
  } else {
    // No wall change, continue straight
    forward();
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
 *   uint8_t wallNum - The binary wall state number of the current cell
 */
void turnTowardsOpening(uint8_t wallNum) {
  for (uint8_t i = 0; i < 4; i++) {
    if (i == (ori + 2) % 4) {
      // Skip the direction we just came from
      continue;
    }
    if (bitRead(wallNum, i) == 0) {
      // Found the direction to go, figure out which way to turn
      if (i == (ori - 1) % 4) {
        // Turn left
        leftTurn();
        forward();
      } else if (i == (ori + 1) % 4) {
        // Turn right
        rightTurn();
        forward();
      } else if (i == ori) {
        // Don't have to turn; continue straight
        forward();
      } else {
        // Should never happen
      }
    }
  }
}

/*
 * Returns the number of openings based on the wall number,
 * which is a count of the 0s in the binary representation number
 * 
 * Params:
 *   uint8_t wallNum - The binary wall state number of the current cell
 *
 * Returns:
 *   uint8_t - The number of openings in the current cell
 */
uint8_t getOpeningsFromWallNumber(uint8_t wallNum) {
  // TODO
  uint8_t numopenings = 0;
  
  for(uint8_t bit = 0; bit < 4; bit++){
    if(bitRead(wallNum, bit)==0){
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

  Serial.print('R');
}
