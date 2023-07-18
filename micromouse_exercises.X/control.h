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
#include "serialComms.h"
#include "myTimers.h"
#include "myPWM.h"

#define MAX_V 70

typedef struct {
    float kp;   // Proportional gain  (P-controller)
    float ki;   // Integral gain      (I-controller)
} PIControl;

float output_limiter(float signal, float max, float min);
float p_control(PIControl* control, long pos, long measure);
float pi_control(PIControl* controller, long pos, long measure);
float dc_converter(float speed);
void set_Motor_velocity(float speed);
void controlMotorPosition(long pos, char *outBuffer, PIControl *controller);
void velocity_control(PIControl* controller, float speed, char* buffer);

#endif /* CONTROL_H */
