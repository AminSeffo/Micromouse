#include "pathPlanner.h"
#include "config.h"
#include "drive.h"
#include "serialComms.h"
#include <xc.h>
#include "stdio.h"


void goDir(int newDir, int currentDir){
    int turn = (newDir - currentDir + 4) % 4;
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
    newDriveDistance(17.5);
}