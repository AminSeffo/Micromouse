
#include "mapping.h"
#include <stdio.h>
#include <stdlib.h>
#include "config.h"


#define MAP_SIZE 6
#define CELL_SIZE 18.0

//Walls
#define UNKNOWN 0
#define OPEN 1
#define CLOSED 2

Cell map[MAP_SIZE][MAP_SIZE];

MousePos mousePos;

StackNode allNodes[MAP_SIZE][MAP_SIZE];

StackNode * newNode(Position pos){
    allNodes[pos.x][pos.y].pos = pos;
    allNodes[pos.x][pos.y].next = NULL;
    return &allNodes[pos.x][pos.y];
}

int isEmpty(StackNode *root){
    return !root;
}

void push( StackNode** root, Position pos){
    StackNode* stackNode = newNode(pos);
    stackNode->next = *root;
    *root = stackNode;
}

Position pop(StackNode** root){
    if(isEmpty(*root)){
        Position pos = {-1,-1};
        return pos;
    }
    StackNode* temp = *root;
    *root = (*root)->next;
    Position pos = temp->pos;
    free(temp);
    return pos;
}

/*
returns the position of the neighbor cell in the given direction
*/
Position getNextPosition(Position pos, int dir){
    Position newPos = pos;
    switch(dir){
        case RIGHT:
            newPos.x++;
            break;
        case TOP:
            newPos.y++;
            break;
        case LEFT:
            newPos.x--;
            break;
        case BOTTOM:
            newPos.y--;
            break;
        default:
            break;
    }
    return newPos;
}

/*
Sets up the mapping with all walls closed and the inner circle open,
initalized with floodfill values
*/
void initMapping(){
    //init all walls to unkown
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            map[i][j].value = UNKNOWN;
            map[i][j].topWall = UNKNOWN;
            map[i][j].rightWall = UNKNOWN;
        }
    }
    //init outer walls to closed
    for(int i = 0; i < MAP_SIZE; i++){
        map[MAP_SIZE-1][i].topWall = CLOSED;
        map[i][MAP_SIZE-1].rightWall = CLOSED;
    }
    //init first cell
    map[0][0].topWall = OPEN;
    map[0][0].rightWall = CLOSED;

    //init values according to floodfill
    //inner circle
    for(int i = 2; i <=3; i++){
        for(int j = 2; j <=3; j++){
            map[i][j].value = 0;
        }
        map[i][0].value=2;
        map[0][i].value=2;
        map[i][5].value=2;
        map[5][i].value=2;

        map[i][1].value=1;
        map[1][i].value=1;
        map[i][4].value=1;
        map[4][i].value=1;
    }
    map[1][1].value=2;
    map[1][4].value=2;
    map[4][1].value=2;
    map[4][4].value=2;

    map[0][1].value=3;
    map[0][4].value=3;
    map[1][0].value=3;
    map[1][5].value=3;
    map[4][0].value=3;
    map[4][5].value=3;
    map[5][1].value=3;
    map[5][4].value=3;

    map[0][0].value=4;
    map[0][5].value=4;
    map[5][0].value=4;
    map[5][5].value=4;
}

/*
Sets the mouse position to the given position and orientation
*/
void initMousePos(){
    mousePos.pos.x = 0;
    mousePos.pos.y = 0;
    mousePos.orientation = TOP;
}

/*
Gets the neighbors of the given position, given the current state of the map
*/
Cell * getNeighbors(Position pos){
    Cell neighbors[4];
    Cell none = {-1,-1,100};

    //wall to the left?
    if (pos.x == 0 || map[pos.x-1][pos.y].rightWall == CLOSED){
        neighbors[LEFT] = none;
    }else{
        neighbors[LEFT] = map[pos.x-1][pos.y];
    }
    //wall to the right?
    if (pos.x == MAP_SIZE-1 || map[pos.x][pos.y].rightWall == CLOSED){
        neighbors[RIGHT] = none;
    }else{
        neighbors[RIGHT] = map[pos.x+1][pos.y];
    }
    //wall to the top?
    if (pos.y == MAP_SIZE-1 || map[pos.x][pos.y].topWall == CLOSED){
        neighbors[TOP] = none;
    }else{
        neighbors[TOP] = map[pos.x][pos.y+1];
    }
    //wall to the bottom?
    if (pos.y == 0 || map[pos.x][pos.y-1].topWall == CLOSED){
        neighbors[BOTTOM] = none;
    }else{
        neighbors[BOTTOM] = map[pos.x][pos.y-1];
    }

    return neighbors;
}



/*
returns the direction of the neighbor with the lowest value
*/
int minNeighbor(Position currentPos){
    int currentVal = map[currentPos.x][currentPos.y].value;
    Position minPos = currentPos;
    int minVal = currentVal;
    int minDir = -1;
    Position * neighbors= getNeighbors(currentPos);
    for (int i = 0; i < 4; i++){
        if (map[neighbors[i].x][neighbors[i].y].value < minVal){
            minVal = map[neighbors[i].x][neighbors[i].y].value;
            minDir = i;
        }
    }
    return minDir;
}

void floodfill(Position pos){
    StackNode* root = NULL;

    push(&root, pos);
    //while stack is not empty
    while(!isEmpty(root)){
        //pop stack
        pos = pop(&root);

        Cell current = map[pos.x][pos.y];
        Cell * neighbors = getNeighbors(pos);

        //get min value of neighbors
        int min = 10;
        int dir = -1;
        for (int i = 0; i < 4; i++){
            if (neighbors[i].value != -1 && neighbors[i].value < min){
                min = neighbors[i].value;
                dir = i;
            }
        }

        //if min value is smaller than current value
        if (min != current.value-1){
            //update value of current cell
            map[pos.x][pos.y].value = min+1;
            //push neighbors to stack
            for(int i = 0; i<4; i++){
                if (neighbors[i].value != 100){
                    Position posNeighbor = getNextPosition(pos, i);
                    push(&root, posNeighbor);
                }
            }
        }
    }
}
void turnToDirection(int direction){
    int diff = direction - mousePos.orientation;
    if (diff == 1 || diff == -3){
        //turn right
        rotateDegree(90.0);
    }else if (diff == -1 || diff == 3){
        //turn left
        rotateDegree(-90.0);
    }else if (diff == 2 || diff == -2){
        //turn around
        rotateDegree(180.0);
    }
    mousePos.orientation = direction;
}
void goToNeighbor(int direction){
    //check if we are facing the right direction
    if (mousePos.orientation != direction){
        //turn to the right direction
        turnToDirection(direction);
    }
    //move forward
    newDriveDistance(CELL_SIZE);
    //update mouse position
    mousePos.pos = getNextPosition(mousePos.pos, direction);
}

void updateMap(){
    //check for walls
    //depending on mouse orientation
    if(mousePos.orientation==TOP){
        //check for walls to the top and right
        if (get_front_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x][mousePos.pos.y].topWall = CLOSED;
        }else{
            map[mousePos.pos.x][mousePos.pos.y].topWall = OPEN;
        }
        if (get_right_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x][mousePos.pos.y].rightWall = CLOSED;
        }else{
            map[mousePos.pos.x][mousePos.pos.y].rightWall = OPEN;
        }
        if (get_left_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x-1][mousePos.pos.y].rightWall = CLOSED;
        }else{
            map[mousePos.pos.x-1][mousePos.pos.y].rightWall = OPEN;
        }
        //bottom wall is open
        if (mousePos.pos.y != 0){
            map[mousePos.pos.x][mousePos.pos.y-1].topWall = OPEN;
        }
    }

    if(mousePos.orientation ==RIGHT){
        if(get_front_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x][mousePos.pos.y].rightWall = CLOSED;
        }else{
            map[mousePos.pos.x][mousePos.pos.y].rightWall = OPEN;
        }
        if(get_right_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x][mousePos.pos.y-1].topWall = CLOSED;
        }else{
            map[mousePos.pos.x][mousePos.pos.y-1].topWall = OPEN;
        }
        if(get_left_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x][mousePos.pos.y].topWall = CLOSED;
        }else{
            map[mousePos.pos.x][mousePos.pos.y].topWall = OPEN;
        }
        map[mousePos.pos.x-1][mousePos.pos.y].rightWall = OPEN;
    }

    if(mousePos.orientation == LEFT){
        if(get_front_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x-1][mousePos.pos.y].rightWall = CLOSED;
        }else{
            map[mousePos.pos.x-1][mousePos.pos.y].rightWall = OPEN;
        }
        if(get_right_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x][mousePos.pos.y].topWall = CLOSED;
        }else{
            map[mousePos.pos.x][mousePos.pos.y].topWall = OPEN;
        }
        if(get_left_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x][mousePos.pos.y-1].topWall = CLOSED;
        }else{
            map[mousePos.pos.x][mousePos.pos.y-1].topWall = OPEN;
        }
        map[mousePos.pos.x][mousePos.pos.y].rightWall = OPEN;
    }

    if(mousePos.orientation == BOTTOM){
        if(get_front_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x][mousePos.pos.y-1].topWall = CLOSED;
        }else{
            map[mousePos.pos.x][mousePos.pos.y-1].topWall = OPEN;
        }
        if(get_right_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x-1][mousePos.pos.y].rightWall = CLOSED;
        }else{
            map[mousePos.pos.x-1][mousePos.pos.y].rightWall = OPEN;
        }
        if(get_left_distance_in_cm() < THRESHOLD_NO_WALL){
            map[mousePos.pos.x][mousePos.pos.y].rightWall = CLOSED;
        }else{
            map[mousePos.pos.x][mousePos.pos.y].rightWall = OPEN;
        }
        map[mousePos.pos.x][mousePos.pos.y].topWall = OPEN;
    }
    
    
}

void runMapping(){
    initMapping();
    initMousePos();
    
    //while there is a cell with lower value than current cell go there
    while (map[mousePos.pos.x][mousePos.pos.y].value > 0){
        //update cell Walls

        //check if there is a neighbor with lower value
        int direction = minNeighbor(mousePos.pos);
        if (direction != -1){
            //go to neighbor
            goToNeighbor(direction);
        }else{
            //there is nowhere to go, do floodfill
            floodfill(mousePos.pos);
        }
    }
}