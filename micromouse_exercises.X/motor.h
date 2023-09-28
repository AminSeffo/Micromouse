//
// Created by marius on 8/21/23.
//

#ifndef MICROMOUSE_MOTOR_H
#define MICROMOUSE_MOTOR_H

//#define MYPWM_MAX (2*26666L)
#define MYPWM_MAX (1333L)

void setupMotor();
void setMotorBreak(void);
void unsetMotorBreak(void);
void setMotor1Dir(int fwd);
void setMotor2Dir(int fwd);

void setMotor1Speed(float speed);
void setMotor2Speed(float speed);


void setLeftMotorSpeed(float speed);
void setRightMotorSpeed(float speed);
void motorStop();

void setupMotorSpeedController();

void controlLeftMotorSpeed();
void controlRightMotorSpeed();

void controlMotorSpeed();

void startSpeedControllerTimer();
void setupSpeedControllerTimer(int periodInMS);

#endif //MICROMOUSE_MOTOR_H
