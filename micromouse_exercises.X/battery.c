/* 
 * File:   battery.h
 * Author: Amin
 *
 * Created on August 27, 2023, 5:29 PM
 */

#include <battery.h>

float getBatteryVoltage(int adcValue)
{
    //read the voltage from voltage divider
    float voltage = (float)adcValue * ADC_REFERENCE_VOLTAGE / 4095.0;
    //calculate the battery voltage
    float batteryVoltage = (voltage * (BATTERY_DIVIDER_R1 + BATTERY_DIVIDER_R2)) / BATTERY_DIVIDER_R2;
    return batteryVoltage;
} 