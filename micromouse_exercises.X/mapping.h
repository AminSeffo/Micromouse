/* 
 * File:   mapping.h
 * Author: zeehondje
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
    struct Stack *next;
}StackNode;

typedef struct{
    Position pos;
    int orientation;
}MousePos;

StackNode* newNode(Position pos);
int isEmpty( StackNode *root);
void push( StackNode** root, Position pos);
Position pop( StackNode** root);

void updateMouse(Position pos, int dir);
void initMapping();
void initMousePos();
Position getNeighborPosition(Position pos, int dir);
void getNeighbors(Position pos);
int minNeighbor(Position currentPos);
void floodfill(Position pos);
void updateMap();
void runMapping();

#endif	/* MAPPING_H */

