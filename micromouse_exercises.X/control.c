#include "control.h"

void PIControl_Init(PIControl* control, float kp, float ki, float setpoint) {
    control->kp = kp;
    control->ki = ki;
    control->setpoint = setpoint;
    control->error_sum = 0.0f;
    control->prev_error = 0.0f;
}

float PIControl_Update(PIControl* control, float measured_value, float dt) {
    // Calculate the error
    float error = control->setpoint - measured_value;

    // Calculate the proportional term
    float p_term = control->kp * error;

    // Calculate the integral term
    control->error_sum += error * dt;
    float i_term = control->ki * control->error_sum;

    // Calculate the control signal
    float control_signal = p_term + i_term;

    // Update the previous error
    control->prev_error = error;

    return control_signal;
}
