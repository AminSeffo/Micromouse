#include "tests.h"
#include <xc.h>
#include "IOconfig.h"
#include "dma.h"
#include "button.h"


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

void runSensorTest(){
    // Check if this output makes sense with debug first ?
    setupIO();
    LED1 = LEDOFF;
    LED2 = LEDOFF;
    LED3 = LEDOFF;
    
    if (SENSOR_FRONT>100){
        LED1 = LEDON;
    }
    if (SENSOR_LEFT>100){
        LED2 = LEDON;
    }
    if (SENSOR_RIGHT>100){
        LED3 = LEDON;
    }
}

void runButtonTest(){
    setupIO();

    if(BUTTON_STATE == BUTTONON){
        LED1 = LEDON;
        LED2 = LEDOFF;
    }
    else{
        LED1=LEDOFF;
        LED2=LEDON;
    }
}

void runButtonPressTest(int buttonHistory){
    setupIO();
    if(buttonHistory == BUTTON_STATE){
        LED3=LEDOFF;
    }
}




