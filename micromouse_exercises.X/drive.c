
#include <xc.h>
#include "IOconfig.h"
#include "motor.h"
#include "motorEncoders.h"
#include "control.h"
#include "serialComms.h"


void controlPosition(long pos, long encoderValue, PIControl *controller)
{   
    float speed = pi_control(controller, pos, encoderValue);
    if(speed<0){
        setMotor1Dir(0);
        setMotor2Dir(0);
        speed = - speed;
    }else{
        setMotor1Dir(1);
        setMotor2Dir(1);
    }
    
    setMotor1Speed(speed*0.08);
    setMotor2Speed(speed*0.08);
}

void driveDistance(float distanceCM){
    setupMotor();
    setupIO();
    setupUART1();
    setupMotorEncoders(0,0);
    setMotor1Dir(1);
    setMotor2Dir(1);
    
    PIControl controller;
    PIControl_Init(&controller, 0.005, 0.00, 0.1);

    float setpointSpeed = 0.0;
    setMotor1Speed(setpointSpeed);
    setMotor2Speed(setpointSpeed);
    
    int ticks = distanceCM * (TICKS_PER_WHEELROTATION/(WHEEL_DIAMETER*3.1415)-7.5);

    int position = getPositionInCounts_2();
    while((position<(ticks-10)) || (position>(ticks+10))){
        controlPosition(ticks,position, &controller);
        position = getPositionInCounts_2();
        
    }
    setMotorBreak();
}

void driveCells(int nrCells){
    driveDistance(nrCells*18);
}