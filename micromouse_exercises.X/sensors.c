#include "sensors.h"
#include "adc.h"
#include "dma.h"

void initSensors(){
	setupADC1();
	initSensors();
	startADC1();
}
