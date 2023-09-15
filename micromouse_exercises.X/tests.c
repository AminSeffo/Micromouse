#include <stdio.h>
#include <string.h>

#include <xc.h>
#include "tests.h"
#include "IOconfig.h"
#include "serialComms.h"
#include "motorEncoders.h"


void runLedTest()
{	
	setupIO();

	LED1 = LEDOFF;

    LED2 = LEDON;

    LED3 = LEDOFF;
}


void runEncoderTest(float pos){
    setupIO();
    LED1 = LEDOFF;
    LED2 = LEDOFF;
     
    if (getPositionInCounts_1()>pos){
        LED1 = LEDON;
    }
    if (getPositionInCounts_2()>pos){
        LED2 = LEDON;
    }
    
}

void plotEncoderValuesUART(void){
    setupIO();
    setupUART1();
    for(int i=0; i<1000;i++){
        char buffer[16];
        sprintf(buffer, "%ld %ld\n\r\0", getPositionInCounts_1(), getPositionInCounts_2());
        putsUART1(buffer);
    }
}