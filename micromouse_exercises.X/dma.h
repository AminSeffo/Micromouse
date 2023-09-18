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

#define BATTERY_VOLTAGE adcData[3] // AN4





#endif	/* DMA_H */

