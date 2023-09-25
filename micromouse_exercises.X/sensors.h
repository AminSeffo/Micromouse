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

float convert_sensor_data_to_distance(int sensor_data);
float get_left_distance_in_cm(void);
float get_right_distance_in_cm(void);
float get_front_distance_in_cm(void);


#endif	/* SENSORS_H */

