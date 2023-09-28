/* 
 * File:   mapping.h
 * Author: yara
 *
 * Created on September 25, 2023, 11:37 AM
 */

#ifndef MAPPING_H
#define	MAPPING_H

typedef struct {
    int value;
    int topWall;
    int rightWall;
}Cell;

typedef struct {
    int x;
    int y;
}Position;

typedef struct{
    Position pos;
    int orientation;
}MousePos;

int isEmpty();
void push(Position pos);
Position pop();

void updateMouse(Position pos, int dir);
void initMapping();
void initMousePos();
Position getNeighborPosition(Position pos, int dir);
void getNeighbors(Position pos);
int minNeighbor(Position currentPos);
void floodfill(Position pos);
void goalReached();
void updateMap();
void runMapping();

#endif	/* MAPPING_H */

