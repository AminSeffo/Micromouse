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

#define MAX_V 70

typedef struct {
    float kp;   // Proportional gain  (P-controller)
    float ki;   // Integral gain      (I-controller)
    float setpoint;  // Setpoint for the control system (desired value)
    float integral;  // Accumulated error for integral control 
} PIControl;

void PIControl_Init(PIControl* control, float kp, float ki, float setpoint);
float PIControl_Update(PIControl* control, float measured_value);
float p_control(PIControl* control, long pos, long measure);
float pi_control(PIControl* controller, float pos, float measure);
float fpi_control(PIControl* controller, float pos, float measure);

#endif /* CONTROL_H */
