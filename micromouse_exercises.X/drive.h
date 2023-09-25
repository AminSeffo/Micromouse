/* 
 * File:   drive.h
 * Author: yara
 *
 * Created on September 20, 2023, 12:14 PM
 */

#ifndef DRIVE_H
#define	DRIVE_H

#include "control.h"

void controlPosition(long pos, long encoderValue, PIControl *posController, PIControl *pathController);
void driveDistance(float distanceCM);
void driveCells(int nrCells);

void stopDrive();
void rotateDegree(float deg);
void newDriveDistance(float distanceCM);

void setupLineFollowController();
void lineFollowCotroller();
void setupLineControllerTimer(int periodInMS);
void startLineController();
void stopLineController();



#endif	/* DRIVE_H */

