/* 
 * File:   control.h
 * Author: Amin Seffo
 *
 * Created on June 28, 2023
 */

#ifndef CONTROL_H
#define CONTROL_H
#include <xc.h>
#include "motorEncoders.h"

typedef struct {
    float kp;   // Proportional gain  (P-controller)
    float ki;   // Integral gain      (I-controller)
    float setpoint;  // Setpoint for the control system
    float error_sum;  // Accumulated error for integral control
    float prev_error; // Previous error for derivative control
} PIControl;

void PIControl_Init(PIControl* control, float kp, float ki, float setpoint);
float PIControl_Update(PIControl* control, float measured_value, float dt);

#endif /* CONTROL_H */
