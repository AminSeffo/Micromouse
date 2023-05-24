#include "myTimers.h"
#include "IOconfig.h"
#include "math.h"
#define T_uc 37.5*1e-9

void initTimer1(unsigned int period) 
{
    //unsigned TimerControlValue;
    
    T1CON = 0;              // ensure Timer 1 is in reset state
    //TimerControlValue=T1CON;
 
    T1CONbits.TCKPS = 0b01; // FCY divide by 64: tick = 2.4us (Tcycle=37.5ns)
    T1CONbits.TCS = 0;      // select internal FCY clock source
    T1CONbits.TGATE = 0;    // gated time accumulation disabled
    TMR1 = 0;
    PR1 = period;           // set Timer 1 period register ()
    IFS0bits.T1IF = 0;      // reset Timer 1 interrupt flag
    IPC0bits.T1IP = 4;      // set Timer1 interrupt priority level to 4
    IEC0bits.T1IE = 1;      // enable Timer 1 interrupt
    T1CONbits.TON = 0;      // leave timer disabled initially
}

void initTimer2InMS(unsigned int timeInMS)
{
    
    // set up timer 2
    T2CON = 0;
 
    T2CONbits.TCKPS = 0b01; // FCY divide by 8
    T2CONbits.TCS = 0; // gated time accumulation disabled
    TMR2 = 0; // clear register and resets the timer to 0
    float desired_period = (timeInMS / 1000.0);
    desired_period = desired_period / (T_uc * 8);
    PR2 = ceil(desired_period);
    IFS0bits.T2IF = 0; // reset Timer 2 interrupt flag
    IPC1bits.T2IP = 4; // set Timer 2 interrupt priority level to 4
    IEC0bits.T2IE = 1; // enable Timer 2 interrupt
    T2CONbits.TON = 0; // leave timer  disabled initially
  
    
}

void startTimer1(void) 
{
    T1CONbits.TON = 1; //
 
}

void startTimer2(void)
{
    T2CONbits.TON = 1;
}



void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void)
{
    static int myCount=0;
    IFS0bits.T1IF = 0;           // reset Timer 1 interrupt flag 
    myCount++;
    if (myCount==49)
    {
    LED6=~LED6;
    myCount=0;
    }
    
}
void __attribute__((__interrupt__, auto_psv)) _T2Interrupt(void)
 {
     static int myCount=0;
     IFS0bits.T2IF = 0;
     myCount++;
     
 }

