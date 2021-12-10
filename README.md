# Micromouse-2021

[Micromouse Website](http://micromouseusa.com/) | [Wikipedia article](https://en.wikipedia.org/wiki/Micromouse)

## Implementation plans


### Graph API


### Node API

- Graph of nodes
- Each intersection is a node

### Node Functions

- retrieval functions (to get the global variables)
- Add node
- Add adjacencies

### Node Global variables

- searching state (explore vs retrace)
- Position (x,y) as separate variables (unless we run out of memory)
- Adjacency List (list of nodes)
  - this can contain to be explored references to other nodes. Or to be explored references that represent intersections which have yet to be explored. The dead ends are represented by a node that has no adjacencies

### Drive API Functions

#### Drive function

This includes sub functions called from the drive functions. Such as turn, calculate distance, orientation

- Orientation, reads in the distances from the IR sensors, calculates the proximity of the walls, judges it's location in the hallway i.e whether it's in a 2split, 3split, nonsplit
- CalculateDistance, keeps track of the distance traveled from the last node (x,y) this is then saved by instantiation of a node object  when the next node is determined i.e 2split or 3split.
- Turn function, In charge of turning left right or reverse, in order to traverse between nodes
- Adjustments, Must be called between movements to verify that mouse is still in the middle of the hallway

### Drive Global variables

- Orientation (number)
  - 0-3 representing front/left/back/right relative to map front
  - When turning, +/- 1 and mod 4
