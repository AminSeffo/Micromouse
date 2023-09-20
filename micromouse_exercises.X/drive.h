/* 
 * File:   drive.h
 * Author: yara
 *
 * Created on September 20, 2023, 12:14 PM
 */

#ifndef DRIVE_H
#define	DRIVE_H


void controlPosition(long pos, long encoderValue, PIControl *controller);
void driveDistance(float distanceCM);
void driveCells(int nrCells);

#endif	/* DRIVE_H */

