# To Do List

## DONE

- Orientation
  - Keeps track of the orientation of Jerry with respect to where we started
- x/y coordinates
  - Initialized X/Y coordinate system to keep track of where we are in the maze
- Straight function
  - Function to have Jerry go straight
- overall decision making function

## DOING

- Maze Initialization - Change from 16x16x6 to 16x16
  - x/y/N/E/S/W -> x/y/walls
  - walls is decimal equivlant of binary status of wall status
    - ie `walls = 5` means `0101` means walls to S/W
    - `walls = 15` (`1111`) signifies unexplored
- Turning Function
  - Functions for spinning jerry
- Fill Node Fucnction
  - Fills the current grid space to figure out the walls around it
- NEW CHASIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

## NOT STARTED

- Automated testing
  - to be run on computer; shouldn't be sent to robot
- Array Check function
  - Checks the coordinates around Jerry to make decisions
- Add comments to code
- Give Jerry a pin :)
- Making sure jerry goes forward. This realistically has been started, but it is not good rn tbh
- Some function to make sure we have the maze solved
- give googly eyes
- split functions into separate files
  - figure out libraries or whatever goes into that
