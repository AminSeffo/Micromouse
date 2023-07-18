#include "control.h"

/* 
* limit the output signal to a maximum and minimum value
*/
float output_limiter(float signal, float max, float min){
    if(signal > max){
        signal = max;
    }else if(signal < min){
        signal = min;
    }
    return signal;
}


/*
* calculate the control signal for a P controller
*/
float p_control(PIControl* controller, long pos, long measure){
    long error = pos - measure;
    
    float p_term = controller->kp * (float) error;
    
    float control_signal = output_limiter(p_term, 1,-1);
    
    return control_signal;
}

/*
* calculate the control signal for a PI controller
* with output limiter for integral and total output
*/
float pi_control(PIControl* controller, long pos, long measure){
    
    long error = pos - measure;
    controller -> integral += error * controller -> ki;
    controller->integral = output_limiter(controller -> integral, 1, -1 );
    
    
    float p_term = controller->kp * (float) error;
    float i_term = controller -> integral;
    
    float control_signal = output_limiter(p_term+i_term,1,-1);
    
    
    return control_signal;
} 

/*
* convert the speed from -1 to 1 to a duty cycle between 0.2 and 0.8
* Input current is [-9V,9V] output is limited to [-6V,6V]
* speed is defined as [-1,1], as max speed forward, backward
*/
float dc_converter(float speed){
//    6 volt are max, we get 9V input
    return speed*0.3 + 0.5;
}

/*
* set the motor velocity via duty cycle
*/
void set_Motor_velocity(float velocity)
{
    float duty_cycle = dc_converter(velocity);
    setupDC1PWM1(duty_cycle);
}


/*
* position control with PI controller
* Input: goal position in ticks 
* function sets the motor velocity and prints the current position and velocity to UART
*/
void controlMotorPosition(long pos, char *outBuffer, PIControl *controller)
{
    // Read encoder value
    long encoderValue = getPositionInCounts_1();
    long error = pos - encoderValue;
    
    float speed = pi_control(controller, pos, encoderValue);
    set_Motor_velocity(speed);

    sprintf(outBuffer, "%ld, %0.3f \n\r\0", encoderValue, speed);
    putsUART1(outBuffer);
}



/*
* velocity control with PI controller
* Input: goal velocity in part of full speed [-1,1]
* function sets the motor velocity and prints the current position and velocity to UART
*/
void velocity_control(PIControl* controller, float speed, char* buffer){
    //speed is in percent of full speed (-1, 1)

    //measure is in ticks (or counts) per 10 ms 
    int measure = getVelocityInCountsPerSample_1()/(MAX_V*10);
    float sample_time = 0.01; // 10 ms
    int control_signal = floor(pi_control(controller, speed, measure);)

    //convert control signal from ticks per 10 ms to percent of full speed
    float corrected_speed = speed - control_signal;
    set_Motor_velocity(corrected_speed);

    // print to UART
    // Baud rate is 57600 (bits/second)
    // 7200 bytes per second -> 72 bytes per 10 ms
    sprintf(outBuffer, "%d %0.3f %0.3f P%0.3f I%0.3f\n\r\0", measure, speed, corrected_speed, controller->kp, controller->ki);
    putsUART1(outBuffer);
}