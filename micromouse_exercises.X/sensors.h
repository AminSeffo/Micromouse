/* 
 * File:   sensors.h
 * Author: marius
 *
 * Created on August 21, 2023, 3:41 PM
 */

#ifndef SENSORS_H
#define	SENSORS_H

#include "dma.h"

#define FRONT_SENSOR_DATA DISTANCE_SENSOR1
#define LEFT_SENSOR_DATA DISTANCE_SENSOR2
#define RIGHT_SENSOR_DATA DISTANCE_SENSOR3

void initSensors();

float get_left_distance_in_m(void);
float get_right_distance_in_m(void);
float get_front_distance_in_m(void);


#endif	/* SENSORS_H */

