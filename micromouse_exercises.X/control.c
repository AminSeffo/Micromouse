#include "control.h"

void PIControl_Init(PIControl* controller, float kp, float ki, float setpoint) {
    controller->kp = kp;
    controller->ki = ki;
    controller->setpoint = setpoint;
    controller->integral = 0.0f; 
}

float output_limiter(float signal, float max, float min){
    if(signal > max){
        signal = max;
    }else if(signal < min){
        signal = min;
    }
    return signal;
}

float p_control(PIControl* controller, long pos, long measure){
    long error = pos - measure;
    
    float p_term = controller->kp * (float) error;
    
    float control_signal = p_term;
    
    if (control_signal>1.0){
        control_signal=1.0;
    }else if (control_signal<-1.0){
        control_signal=-1.0;
    }
    return control_signal;
}


float pi_control(PIControl* controller, float pos, float measure){
    float error = pos - measure;
    controller -> integral += error * controller -> ki;
    controller->integral = output_limiter(controller -> integral, 1, -1 );
    
    
    float p_term = controller->kp * (float) error;
    float i_term = controller -> integral;
    
    
    float control_signal = output_limiter(p_term+i_term,1,-1);
    
    
    return control_signal;
    
} 

float fpi_control(PIControl* controller, float pos, float measure){
    float error = pos - measure;
    controller -> integral += error * controller -> ki;
    controller->integral = output_limiter(controller -> integral, 1, -1 );
    
    
    float p_term = controller->kp * (float) error;
    float i_term = controller -> integral;
    
    
    float control_signal = output_limiter(p_term+i_term,1,-1);
    
    
    return control_signal;
    
} 