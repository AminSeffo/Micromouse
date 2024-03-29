/* 
 * File:   dma.h
 * Author: 
 *
 * Created on June 13, 2019, 11:41 AM
 */

#ifndef DMA_H
#define	DMA_H


#include <xc.h>
    
extern unsigned int adcData[32]__attribute__((space(dma)));

void initDmaChannel4(void);

//add some defines to make accessing data more readable

#define BATTERY_VOLTAGE adcData[0]  //AN4
#define DISTANCE_SENSOR1 adcData[1] //AN6
#define DISTANCE_SENSOR2 adcData[2] //AN7
#define DISTANCE_SENSOR3 adcData[3] //AN8

#endif	/* DMA_H */

