//
// Created by marius on 8/21/23.
//

#ifndef MICROMOUSE_MOTOR_H
#define MICROMOUSE_MOTOR_H

#define MYPWM_MAX (2*26666L)
void setupMotor();
void setMotor1Dir(int fwd);
void setMotor2Dir(int fwd);

void setMotor1Speed(float speed);
void setMotor2Speed(float speed);

#endif //MICROMOUSE_MOTOR_H
