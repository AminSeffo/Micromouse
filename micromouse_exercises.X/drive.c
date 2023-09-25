
#include <xc.h>
#include "IOconfig.h"
#include "motor.h"
#include "motorEncoders.h"
#include "control.h"
#include "serialComms.h"
#include "sensors.h"
#include "math.h"
#include "config.h"

#include "drive.h"


PIControl lineController;


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

void stopDrive(){
    motorStop();
    while(velocity1 || velocity2);
}

void rotateDegree(float deg){
    float distanceCM = deg/360.0 * WHEEL_DISTANCE_CM * M_PI;
    long ticks = distanceCM * (TICKS_PER_WHEELROTATION/(WHEEL_DIAMETER*M_PI));
    long goal = getPositionInCounts_2() + ticks;
    
    if (deg > 0) {
        setLeftMotorSpeed(MOTOR_SPEED);
        setRightMotorSpeed(-MOTOR_SPEED);
        
        while (getPositionInCounts_2() < goal);
    }
    if (deg < 0) {
        setLeftMotorSpeed(-MOTOR_SPEED);
        setRightMotorSpeed(MOTOR_SPEED);
        
        while (getPositionInCounts_2() > goal);
    }
    
    stopDrive();   
}

void newDriveDistance(float distanceCM){
    long ticks = distanceCM * (TICKS_PER_WHEELROTATION/(WHEEL_DIAMETER*M_PI));
    long goal = getPositionInCounts_2() + ticks;
    
    startLineController();
    while(getPositionInCounts_2() < goal);
    
    stopLineController();
    stopDrive();
}

void driveCells(int nrCells){
    newDriveDistance(nrCells*18.0);
}

void setupLineFollowController(){
    
    PIControl_Init(&lineController, 0.13, 0.001, 0);
    
    setupLineControllerTimer(LINE_FOLLOW_CONTROL_INT_IN_MS);
        
}

void lineFollowCotroller(){
    float rightD = get_right_distance_in_cm();
    float leftD = get_left_distance_in_cm();
    float errorSignal;

    int noWallLeft = leftD > THRESHOLD_NO_WALL;
    int noWallRight = rightD > THRESHOLD_NO_WALL;
    
    if (noWallLeft && noWallRight) {
        setLeftMotorSpeed(MOTOR_SPEED);
        setRightMotorSpeed(MOTOR_SPEED);
        return;
    }

    if (noWallLeft) {
        errorSignal =  (rightD - DISTANCE_WHEN_CENTERED)*2;
    }
    else if (noWallRight) {
        errorSignal = (DISTANCE_WHEN_CENTERED - leftD)*2;
    }
    else {
        errorSignal = rightD - leftD;
    }



    float signal = pi_control(&lineController, 0.0, errorSignal);
    
    if (signal>0){
        setLeftMotorSpeed(MOTOR_SPEED * (1-0.5*signal));
        setRightMotorSpeed(MOTOR_SPEED);
    }
    else {
        setLeftMotorSpeed(MOTOR_SPEED);
        setRightMotorSpeed(MOTOR_SPEED * (1-0.5*-signal));
    }
    
    
}


void setupLineControllerTimer(int periodInMS){

    float desired_period = (periodInMS / 1000.0);
    desired_period = desired_period / (T_uc * 64);

    //unsigned TimerControlValue;

    T3CON = 0;              // ensure Timer 3 is in reset state
    //TimerControlValue=T1CON;

    T3CONbits.TCKPS = 0b10; // FCY divide by 64: tick = 2.4us (Tcycle=37.5ns)
    T3CONbits.TCS = 0;      // select internal FCY clock source
    T3CONbits.TGATE = 0;    // gated time accumulation disabled
    TMR3 = 0;
    PR3 = ceil(desired_period);           // set Timer 3 period register ()
    IFS0bits.T3IF = 0;      // reset Timer 3 interrupt flag
    IPC2bits.T3IP = 4;      // set Timer3 interrupt priority level to 4
    IEC0bits.T3IE = 1;      // enable Timer 3 interrupt
    T3CONbits.TON = 0;      // leave timer disabled initially
}

void startLineController(){
    T3CONbits.TON = 1;
}

void stopLineController(){
    T3CONbits.TON = 0;
    resetControl(&lineController);
}

void __attribute__((__interrupt__, auto_psv)) _T3Interrupt(void){
    IFS0bits.T3IF = 0; //clear interrupt flag
    lineFollowCotroller();
}