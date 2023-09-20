
#include <xc.h>
#include "IOconfig.h"
#include "motor.h"
#include "motorEncoders.h"
#include "control.h"
#include "serialComms.h"
#include "sensors.h"
#include "math.h"


void controlLine(PIControl *controller, float speed){
    
    float rightD = get_right_distance_in_cm();
    float leftD = get_left_distance_in_cm();
    float idealD = (leftD+rightD)/2;
    float difD= fabs(rightD-leftD);
    
    float signalLeft = pi_control(controller, idealD, leftD);
    float signalRight = pi_control(controller, idealD, rightD);
    
    if(difD<0.5 || 1){
       setMotor1Speed(0.0);
       setMotor2Speed(speed);
    }
    else if(leftD>rightD){
        //correct course towards left
        //slow down left wheel
        setMotor2Speed(speed*(1+0.2*difD/6));
        setMotor1Speed(speed);
    }
    else{
        //correct course towards right
        //speed up left wheel
        setMotor2Speed(speed*(1-0.2*difD/6));
        setMotor1Speed(speed);
    }
}

void controlPosition(long pos, long encoderValue, PIControl *posController, PIControl *pathController)
{   
    float speed = pi_control(posController, pos, encoderValue);
    if(speed<0){
        setMotor1Dir(0);
        setMotor2Dir(0);
        speed = - speed;
    }else{
        setMotor1Dir(1);
        setMotor2Dir(1);
    }
    controlLine(posController, speed*0.08);
}

void driveDistance(float distanceCM){
    setupMotor();
    setupIO();
    setupUART1();
    setupMotorEncoders(0,0);
    setMotor1Dir(1);
    setMotor2Dir(1);
    
    PIControl position_pi;
    PIControl_Init(&position_pi, 0.005, 0.00, 0.1);
    PIControl lane_pi;
    PIControl_Init(&lane_pi, 0.5, 0.1, 0.1);

    float setpointSpeed = 0.0;
    setMotor1Speed(setpointSpeed);
    setMotor2Speed(setpointSpeed);
    
    int ticks = distanceCM * (TICKS_PER_WHEELROTATION/(WHEEL_DIAMETER*3.1415)-7.5);

    int position = getPositionInCounts_2();
    while((position<(ticks-10)) || (position>(ticks+10))){
        controlPosition(ticks,position, &position_pi, &lane_pi);
        position = getPositionInCounts_2();
        
    }
    setMotorBreak();
}

void driveCells(int nrCells){
    driveDistance(nrCells*18);
}