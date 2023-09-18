#include <xc.h>
#include "button.h"


void (*buttonFun)()=0;

void initButton(void (*func)()){
   //map interrupflag to pin
   
   buttonFun = func;
//   RPINR0bits.INT1R = 8; //INT1 mapped to RP8
   IEC1bits.INT1IE = 0; //disable interrupt
   INTCON2bits.INT1EP = 1; //interrupt on falling edge
   IFS1bits.INT1IF = 0; //clear interrupt flag
   IPC5bits.INT1IP = 6; //set interrupt priority
   IEC1bits.INT1IE = 1; //enable interrupt
   
   //we need  to decide what kind of funcion we want to use with the button
}

void __attribute__((__interrupt__, auto_psv)) _INT1Interrupt(void){
   IFS1bits.INT1IF = 0; //clear interrupt flag
   buttonFun();
}

