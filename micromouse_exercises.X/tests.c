#include "tests.h"
#include <xc.h>
#include "IOconfig.h"
#include "dma.h"
#include "button.h"
#include "stdio.h"
#include "motorEncoders.h"
#include "serialComms.h"
#include "motor.h"
#include "drive.h"
#include "sensors.h"
#include "control.h"
#include "mapping.h"
#include "pathPlanner.h"

void runLedTest() {
    setupIO();


    LED1 = LEDON;

    LED2 = LEDOFF;

    LED3 = LEDON;

    //for (i = 0; i < 300000; i++); // short dirty delay for changes to take effect,

}

void runEncoderTest(float pos) {
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

void motorFullSpeed() {
    setupMotor();
    setMotor1Dir(1);
    setMotor1Speed(1.0);
    setMotor2Dir(1);
    setMotor2Speed(1.0);
}

void plotEncoderValuesUART(void) {
    setupIO();
    setupUART1();
    setupMotorEncoders(0, 0);
    motorFullSpeed();
    LED1 = LEDON;
    LED2 = LEDON;
    LED3 = LEDON;

    for (;;) {
        char buffer[16];
        sprintf(buffer, "%d %d\n\r\0", velocity1, velocity2);
        putsUART1(buffer);
        LED1 = ~LED1;

        for (int i = 0; i < 1000; i++) {
            LED3 = ~LED3;
            for (int j = 0; j < 1000; j++);
        }
        // LED3=LEDON;
    }
}

void stopSpeed() {
    setMotor1Speed(0);
    setMotor2Speed(0);
}

void testSpeedControl() {
    setupMotor();
    setupIO();
    setupUART1();
    setupMotorEncoders(0, 0);
    initButton(stopSpeed);

    LED1 = LEDON;
    LED2 = LEDON;
    LED3 = LEDON;

    setMotor1Dir(1);
    setMotor2Dir(0);

    float pControl1 = 1;
    float pControl2 = 1;

    float setpointSpeed = 0.1;

    setMotor1Speed(setpointSpeed * pControl1);
    setMotor2Speed(setpointSpeed * pControl2);



    for (;;) {
        char buffer[16];
        sprintf(buffer, "%d %d\n\r\0", velocity1, velocity2);
        putsUART1(buffer);
        LED1 = ~LED1;

        for (int i = 0; i < 1000; i++) {
            LED3 = ~LED3;
            for (int j = 0; j < 1000; j++);
        }
        // LED3=LEDON;
    }

}

void testForward() {
    driveCells(5);
}

void plotSensorValues() {
    setupIO();
    setupUART1();
    initSensors();
    LED3 = LEDON;
    LED2 = LEDON;
    for (;;) {

        char buffer[16];
        sprintf(buffer, "%d %d %d\n\r\0", FRONT_SENSOR_DATA, LEFT_SENSOR_DATA, RIGHT_SENSOR_DATA);
        putsUART1(buffer);
        for (int i = 0; i < 1000; i++) {
            LED3 = ~LED3;
            for (int j = 0; j < 1000; j++);
        }
    }
}

void plotBatteryVoltage(){
    setupIO();
    setupUART1();
    initSensors();
    
    setupMotor();
    setupMotorEncoders(0, 0);
    setupMotorSpeedController();
    //putsUART1("Start Measurements:\n\r\0");

    setLeftMotorSpeed(1);
    setRightMotorSpeed(1);
    
    LED3 = LEDON;
    LED2 =LEDON;
    for (;;){

        char buffer[16];
        sprintf(buffer, "%.3f\n\r\0", getBatteryVoltage(BATTERY_SENSOR_DATA));
        putsUART1(buffer);
        for(int i = 0; i < 1000; i++){
            LED3=~LED3;
            for(int j=0; j<1000; j++);
        }
    }
}

void followLaneController() {
    setupIO();
    setupUART1();
    initSensors();
    setupMotor();
    setupMotorEncoders(0, 0);
    initButton(stopSpeed);
    setMotor1Dir(1);
    setMotor2Dir(0);

    setMotor2Speed(0.1);
    setMotor1Speed(0.1);

    PIControl contoller;
    PIControl_Init(&contoller, 5.0, 1.0, 0.1);


    for (;;) {
        float signal = pi_control(&contoller, get_right_distance_in_cm(), get_left_distance_in_cm());
        float newspeed1 = (signal / 2 + 1)*0.05;
        float newspeed2 = (1 - signal / 2)*0.05;
        setMotor2Speed(newspeed1);
        setMotor1Speed(newspeed2);

        char buffer[16];
        sprintf(buffer, "%.2f %.2f %.2f\n\r\0", signal, get_right_distance_in_cm(), get_left_distance_in_cm());
        putsUART1(buffer);
        //
    }
}

void speedControllerTest() {
    setupIO();
    setupUART1();
    setupMotor();
    setupMotorEncoders(0, 0);
    setupMotorSpeedController();

    for (int i = 0; i < 3000; i++) {
        for (int j = 0; j < 10000; j++);
    }

    //putsUART1("Start Measurements:\n\r\0");

    setLeftMotorSpeed(0.4);
    setRightMotorSpeed(0.4);

    for (;;) {
        char buffer[16];
        sprintf(buffer, "%d, %d\n\r\0", velocity1, velocity2);
        //sprintf(buffer, "%d \n\r\0", velocity2);

        putsUART1(buffer);

        //for(int i = 0; i < 1000; i++){
        //    for(int j=0; j<1000; j++);
        //}
    }

}

void lineFollowTest(){
    setupIO();
    setupUART1();
    setupMotor();
    initSensors();
    setupMotorEncoders(0, 0);
    setupMotorSpeedController();
    
    for (int i = 0; i < 4000; i++) {
        for (int j = 0; j < 10000; j++);
    }
    
    setupLineFollowController();
    startLineController();
    
   for (;;) {
        char buffer[64];
        sprintf(buffer, "ML: %d, MR: %d, SL: %.2f, SR: %.2f\n\r\0", velocity2, velocity1, get_left_distance_in_cm(), get_right_distance_in_cm());
        //sprintf(buffer, "%d \n\r\0", velocity2);

        putsUART1(buffer);

        //for(int i = 0; i < 1000; i++){
        //    for(int j=0; j<1000; j++);
        //}
    }
}

void driveDistanceTest(){
    setupIO();
    setupUART1();
    setupMotor();
    initSensors();
    setupMotorEncoders(0, 0);
    setupMotorSpeedController();
    
    for (int i = 0; i < 4000; i++) {
        for (int j = 0; j < 10000; j++);
    }
    
    setupLineFollowController();
    
    newDriveDistance(18.0);
    
    for (;;) {
        char buffer[64];
        sprintf(buffer, "SL: %.2f, SR: %.2f, %ld\n\r\0", get_left_distance_in_cm(), get_right_distance_in_cm(), getPositionInCounts_2() );
        //sprintf(buffer, "%d \n\r\0", velocity2);

        putsUART1(buffer);

        for(int i = 0; i < 1000; i++){
            for(int j=0; j<1000; j++);
        }
    }
}

void ledBinary(int number){
    LED1 = number%2;
    LED2 = (number/2)%2;
    LED3 = (number/4)%2;
}

void testDriveCommands(){
    setupMotor();
    setupIO();
    setupUART1();
    setupMotorEncoders(0,0);
    initButton(goalReached);

    setMotor1Dir(1);
    setMotor2Dir(0);

    float speed = 0.05;
    

    for(;;){
        int command = mouse_state;
        ledBinary(command);
        switch(command){
            case START:
                setMotor1Speed(speed);
                setMotor2Speed(speed);
                break;
            case STOP:
                setMotor1Speed(0);
                setMotor2Speed(0);
                break;
            case GO_LEFT:
                setMotor1Speed(speed);
                setMotor2Speed(speed/2);
                break;
            case GO_RIGHT:
                setMotor1Speed(speed/2);
                setMotor2Speed(speed);
                break;
        }


    }
}
void rotationTest(){
    setupIO();
    setupUART1();
    setupMotor();
    initSensors();
    setupMotorEncoders(0, 0);
    setupMotorSpeedController();
    
    for (int i = 0; i < 4000; i++) {
        for (int j = 0; j < 10000; j++);
    }
    
    setupLineFollowController();
    while(1){
        newDriveDistance(18.0 * 5-1);
        rotateDegree(90-10);
    }
}

void mouseCtrlTest(){
    setupIO();
    setupUART1();
    setupMotor();
    initSensors();
    setupMotorEncoders(0, 0);
    setupMotorSpeedController();
    setupLineFollowController();
    
    for(;;){
        if (mouse_state){
            char buffer[64];
            sprintf(buffer, "%d\n\r\0", mouse_state );

            putsUART1(buffer);
        }
        
        switch(mouse_state){
            case START:
                mouse_state = STOP;
                newDriveDistance(17.5);
                break;
            case STOP:
              
                break;
            case GO_LEFT:
                mouse_state = STOP;
                rotateDegree(-90+8);
                break;
            case GO_RIGHT:
                mouse_state = STOP;
                rotateDegree(90-8);
                break;
        }
    }
}

void testMapping(){
    setupIO();
    setupUART1();
    setupMotor();
    initSensors();
    setupMotorEncoders(0, 0);
    setupMotorSpeedController();
    setupLineFollowController();
    
    runMapping();
}

void testTurnDir(){
    setupIO();
    setupUART1();
    setupMotor();
    initButton(stopSpeed);
    initSensors();
    setupMotorEncoders(0, 0);
    setupMotorSpeedController();
    setupLineFollowController();
    
    for(int new=0; new < 4; new++){
        for(int old =0; old < 4; old++){
            for(int i=0; i<4000; i++){
                for(int j= 0; j<1000; j++);
            }
            goDir(new, old);
            char buffer[16];
            sprintf(buffer, "%d %d\n\r\0", new, old );
            putsUART1(buffer);
        }
    }
}
