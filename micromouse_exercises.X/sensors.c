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

