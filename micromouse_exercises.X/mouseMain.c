//
// Created by marius on 9/26/23.
//
#include "IOconfig.h"
#include "serialComms.h"
#include "motor.h"
#include "sensors.h"
#include "motorEncoders.h"
#include "drive.h"
#include "mapping.h"
#include "button.h"
#include "mouseMain.h"

#define INIT_STATE 0
#define FIND_SOLUTION_STATE 1

uint16_t mainMouseState = 0;

void switchState(){
    mainMouseState = (mainMouseState + 1) % 2;
}

void setup(){
    setupIO();
    setupUART1();
    setupMotor();
    initSensors();
    setupMotorEncoders(0, 0);
    setupMotorSpeedController();
    setupLineFollowController();
    
    initButton(switchState);
}

void mouseLoop(){
    LED1 = LEDOFF;

    while (1) {
        switch (mainMouseState) {
            case INIT_STATE:
                LED1 = LEDOFF;
                stopLineController();
                stopDrive();
                break;
            case FIND_SOLUTION_STATE:
                LED1 = LEDON;
                for(int j = 0; j<4000; j++){
                    for(int i = 0; i<4000; i++);
                }
                runMapping();
                mainMouseState = INIT_STATE;
                break;
        }
    }
}

