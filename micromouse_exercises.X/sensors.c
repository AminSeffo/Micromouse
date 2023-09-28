#include "sensors.h"
#include "adc.h"
#include "dma.h"
#include "math.h"

void initSensors(){
	setupADC1();
	initDmaChannel4();
	startADC1();
}

float convert_sensor_data_to_distance(int sensor_data){
	float distance = pow(sensor_data/5743.9,(-1/0.958));
    
    if (distance < 2)
        distance = 2;
    else if (distance > 14)
        distance = 14;
	return distance;
}

float get_front_distance_in_cm(){
	return convert_sensor_data_to_distance(FRONT_SENSOR_DATA);
}

float get_left_distance_in_cm(){
	return convert_sensor_data_to_distance(LEFT_SENSOR_DATA);
}

float get_right_distance_in_cm(){
	return convert_sensor_data_to_distance(RIGHT_SENSOR_DATA);
}

float getBatteryVoltage(int adcValue)
{
    //read the voltage from voltage divider
    float voltage = (float)adcValue * ADC_REFERENCE_VOLTAGE / 4095.0;
    //calculate the battery voltage
    float batteryVoltage = (voltage * (BATTERY_DIVIDER_R1 + BATTERY_DIVIDER_R2)) / BATTERY_DIVIDER_R2;
    return batteryVoltage;
} 