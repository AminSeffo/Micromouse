/* 
 * File:   tests.h
 * Author: marius, yara
 *
 * Created on August 25, 2023, 4:03 PM
 */

#ifndef TESTS_H
#define	TESTS_H

#include "control.h"

    
void runLedTest();
void runEncoderTest(float pos);
void plotEncoderValuesUART(void);

void motorFullSpeed();
void stopSpeed();
void testSpeedControl();
void testForward();
void plotSensorValues();
void lineFollowTest();
void driveDistanceTest();

#endif	/* TESTS_H */

