#include "tests.h"
#include "xc.h"
#include "IOconfig.h"
#include "motor.h"


void runLedTest()
{	
	setupIO();

	LED1 = LEDOFF;

    LED2 = LEDON;

    LED3 = LEDON;
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

void moterFullSpeed(){
    setupMotor();
    setMotor1Dir(1);
    setMotor1Speed(0.2);
    setMotor2Dir(0);
    setMotor2Speed(0.2);
}