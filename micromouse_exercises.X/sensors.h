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

#define BATTERY_SENSOR_DATA BATTERY_VOLTAGE

#define BATTERY_DIVIDER_R1 20000.0 
#define BATTERY_DIVIDER_R2 10000.0
#define ADC_REFERENCE_VOLTAGE 3.3   // ADC reference voltage

void initSensors();

float convert_sensor_data_to_distance(int sensor_data);
float get_left_distance_in_m(void);
float get_right_distance_in_m(void);
float get_front_distance_in_m(void);
float getBatteryVoltage(int adcValue);




#endif	/* SENSORS_H */

