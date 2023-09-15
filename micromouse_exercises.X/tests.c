#include "tests.h"
#include "xc.h"
#include "IOconfig.h"


void runLedTest()
{	
    setupIO();
    
    
	LED1 = LEDON;

    LED2 = LEDOFF;

    LED3 = LEDON;
    
    //for (i = 0; i < 300000; i++); // short dirty delay for changes to take effect,

    
    
}


void runEncoderTest(float pos){
    setupIO();
//    LED1 = LEDOFF;
//    LED2 = LEDOFF;
     
//    if (getPositionInCounts_1()>pos){
//        LED1 = LEDON;
//    }
//    if (getPositionInCounts_2()>pos){
//        LED2 = LEDON;
//    }
    
}