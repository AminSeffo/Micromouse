#include "tests.h"
#include "xc.h"
#include "IOconfig.h"
#include <stdio.h>
#include <string.h>

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