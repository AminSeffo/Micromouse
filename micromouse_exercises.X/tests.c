#include "tests.h"
#include <xc.h>
#include "IOconfig.h"
#include "dma.h"
#include "button.h"
#include "stdio.h"
#include "motorEncoders.h"
#include "serialComms.h"
#include "motor.h"
#include "sensors.h"

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





void motorFullSpeed(){
    setupMotor();
    setMotor1Dir(1);
    setMotor1Speed(0.2);
    setMotor2Dir(0);
    setMotor2Speed(0.2);
}


void plotEncoderValuesUART(void){
    setupIO();
    setupUART1();
    setupMotorEncoders(0,0);
    motorFullSpeed();
    LED1 = LEDON;
    LED2 = LEDON;
    LED3 = LEDON;

    for(;;){
        char buffer[16];
        sprintf(buffer, "%d %d\n\r\0", velocity1, velocity2);
        putsUART1(buffer);
        LED1=~LED1;
        
        for(int i = 0; i < 1000; i++){
            LED3=~LED3;
            for(int j=0; j<1000; j++);
        }
        // LED3=LEDON;
    }
}

void stopSpeed(){  
    setMotor1Speed(0);
    setMotor2Speed(0);
}

void testSpeedControl(){
    setupMotor();
    setupIO();
    setupUART1();
    setupMotorEncoders(0,0);
    initButton(stopSpeed);
    
    LED1 = LEDON;
    LED2 = LEDON;
    LED3 = LEDON;
    
    setMotor1Dir(1);
    setMotor2Dir(0);

    float pControl1 = 1;
    float pControl2 = 1;

    float setpointSpeed = 0.1;

    setMotor1Speed(setpointSpeed*pControl1);
    setMotor2Speed(setpointSpeed*pControl2); 
    
    
    
    for(;;){
        char buffer[16];
        sprintf(buffer, "%d %d\n\r\0", velocity1, velocity2);
        putsUART1(buffer);
        LED1=~LED1;
        
        for(int i = 0; i < 1000; i++){
            LED3=~LED3;
            for(int j=0; j<1000; j++);
        }
        // LED3=LEDON;
    }
    
}

void plotSensorValues(){
	setupIO();
    setupUART1();
	initSensors();
    LED3 = LEDON;
    LED2 =LEDON;
	for (;;){

		char buffer[16];
        sprintf(buffer, "%d %d %d\n\r\0", FRONT_SENSOR_DATA, LEFT_SENSOR_DATA, RIGHT_SENSOR_DATA);
        putsUART1(buffer);
		for(int i = 0; i < 1000; i++){
            LED3=~LED3;
			for(int j=0; j<1000; j++);
        }
    }
}

