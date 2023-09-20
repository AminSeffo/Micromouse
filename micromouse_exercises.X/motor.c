//
// Created by marius on 8/21/23.
//

#include "motor.h"
#include <xc.h>

void setupMotor()
{
    /* PWM1H1 *, configured to 1kHz, based on fcyc = 26.666 MIPS, Tcycle=37.5nsec/
     * 1ms/37.5nsec = 26666.666 ==> 26666 (fits in 15 bits)
     * of course, we could use a pre-scaler and end up somewhere else
     */
    P1TCONbits.PTEN = 0; // Switch off PWM generator
    P1TCONbits.PTCKPS = 0b00; // Sets prescaler, available are 1(00),4(01),16(10) or 64(11)
    P1TPER = MYPWM_MAX/2; //15 bit register
    PWM1CON1bits.PMOD1 = 1; // set PWM unit 1 to independent mode
    PWM1CON1bits.PMOD2 = 1; // set PWM unit 2 to independent mode
    PWM1CON1bits.PEN1H = 1; // enable PWM driver
    PWM1CON1bits.PEN2H = 1; // enable PWM driver
    PWM1CON1bits.PEN3H = 0; // disable PWM driver
    PWM1CON1bits.PEN1L = 1; // enable PWM driver
    PWM1CON1bits.PEN2L = 1; // enable PWM driver
    PWM1CON1bits.PEN3L = 0; // disable PWM driver
    
    P1OVDCONbits.POUT1H = 0;
    P1OVDCONbits.POUT1L = 0;
    P1OVDCONbits.POUT2H = 0;
    P1OVDCONbits.POUT2L = 0;
    
    // Default direction forward
    P1OVDCONbits.POVD1H = 1;
    P1OVDCONbits.POVD1L = 0;
    P1OVDCONbits.POVD2H = 0;
    P1OVDCONbits.POVD2L = 1;

    P1TCONbits.PTEN = 1; // Switch on PWM generator
    P1DC1 = 0;
    P1DC2 = 0;
    P1DC3 = 0;
}

void setMotorBreak(void){
    P1OVDCONbits.POVD1H = 1;
    P1OVDCONbits.POVD1L = 1;
    P1OVDCONbits.POVD2H = 1;
    P1OVDCONbits.POVD2L = 1;
    
    P1OVDCONbits.POUT1H = 1;
    P1OVDCONbits.POUT1L = 1;
    P1OVDCONbits.POUT2H = 1;
    P1OVDCONbits.POUT2L = 1;
}

void unsetMotorBreak(void){
    P1OVDCONbits.POUT1H = 0;
    P1OVDCONbits.POUT1L = 0;
    P1OVDCONbits.POUT2H = 0;
    P1OVDCONbits.POUT2L = 0;
}

void setMotor1Dir(int fwd){
    P1OVDCONbits.POVD1H = fwd != 0;
    P1OVDCONbits.POVD1L = fwd == 0;
}
void setMotor2Dir(int fwd){
    P1OVDCONbits.POVD2H = fwd == 0;
    P1OVDCONbits.POVD2L = fwd != 0;
}

void setMotor1Speed(float speed){
    //this function sets the duty cycle of PWM1 H1 and L1
    if (speed>1.0)
        speed=1.0;

    if (speed<0.0)
        speed=0.0;
    
    speed = speed *1.075;
    P1DC1 = speed*MYPWM_MAX* 0.6;

}
void setMotor2Speed(float speed){
    //this function sets the duty cycle of PWM1 H2 and L2
    if (speed>1.0)
        speed=1.0;

    if (speed<0.0)
        speed=0.0;

    P1DC2 = speed*MYPWM_MAX* 0.6;
}

