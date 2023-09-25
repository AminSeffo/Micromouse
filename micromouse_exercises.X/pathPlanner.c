#include "pathPlanner.h"
#include "config.h"
#include "drive.h"

int currentDir = TOP;

void goDir(int dir){
    int turn = (dir - currentDir) % 4;
    switch (turn) {
        case 0:
            break;
        case 1:
            //rotate left
            rotateDegree(-90+8);
            break;
        case 2:
            rotateDegree(-90+8);
            rotateDegree(-90+8);
            break;
        case 3:
            rotateDegree(90-8);
            break;
    }
    currentDir = dir;
    
    newDriveDistance(17.5);
}