/* 
 * File:   battery.h
 * Author: Amin
 *
 * Created on August 27, 2023, 5:29 PM
 */
#ifndef BATTERY_H
#define	BATTERY_H

#include <dma.h>

#define BATTERY_DIVIDER_R1 20000.0 
#define BATTERY_DIVIDER_R2 10000.0
#define ADC_REFERENCE_VOLTAGE 3.3   // ADC reference voltage
// Variable to store the ADC reading
uint16_t battery_reading;
float getBatteryVoltage(int adcValue);