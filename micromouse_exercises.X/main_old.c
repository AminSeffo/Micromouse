/*
 * File:   main.c
 * Author: Alexander Lenz
 *
 * Created on 27 Nov 2020, 09:36
 */
// group memebers:

/// Configuration Bits---------------------------

// FBS
#pragma config BWRP = WRPROTECT_OFF // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH       // Boot Segment Program Flash Code Protection (No Boot program Flash segment)

// FGS
#pragma config GWRP = OFF // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF  // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRC // Start with Internal RC Oscillator
#pragma config IESO = OFF  // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = HS    // Primary Oscillator Source (HS Oscillator Mode)
#pragma config OSCIOFNC = OFF // OSC2 Pin Function (OSC2 pin has clock out function)
#pragma config IOL1WAY = OFF  // Peripheral Pin Select Configuration (Allow Multiple Re-configurations)
#pragma config FCKSM = CSECMD // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are enabled)

// FWDT
#pragma config WDTPOST = PS1  // Watchdog Timer Postscaler (1:1)
#pragma config WDTPRE = PR128 // WDT Prescaler (1:128)
#pragma config WINDIS = OFF   // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF   // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128 // POR Timer Value (128ms)
#pragma config ALTI2C = ON    // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON      // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON      // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON    // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1   // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF // JTAG Port Enable (JTAG is Disabled)

/// Include headers-------------------------------
#include "xc.h"
#include "IOconfig.h"
#include "myTimers.h"
#include "myPWM.h"
#include "serialComms.h"
#include "dma.h"
#include "adc.h"
#include "motorEncoders.h"
#include "control.h"
#include <stdio.h>
/// Defines----------------------------
#define SEVEN_MEG_OSC 0 // set to 1 if we use slow (7.3728 MHz) oscillator and not 16 MHz

/*
 *
 */
void potentiometer_LED5_switch(float voltage)
{
    if (voltage > 3.5)
    {
        LED5 = LEDON;
    }
    else
    {
        LED5 = LEDOFF;
        LED6 = LEDON;
    }
}

void dim_LED_potentiometer(float voltage)
{
    // setupDC1PWM1(TEST_SENSOR/670);
    setupDC1PWM1(voltage / 3.3);
}

float read_potentiometer(){
    float refVoltage, voltage;
    refVoltage = 3.3 / 4096;
    voltage = TEST_SENSOR * refVoltage;
    
    return voltage;
}

float dc_converter(float speed){
//    6 volt are max, we get 9V input
    return speed*0.3 + 0.5;
}

void potentiometer_test()
{
    float voltage = read_potentiometer();
    // potentiometer_LED5_switch(voltage);
    dim_LED_potentiometer(voltage);
}

void set_Motor_velocity(float velocity)
{
    float duty_cycle = dc_converter(velocity);
    setupDC1PWM1(duty_cycle);
}

float controlMotorVelocity(float speed, char *outBuffer, PIControl *controller)
{
    set_Motor_velocity(speed);
    // Read encoder value
    float encoderValue = getPositionInCounts_1();
    int velocity = getVelocityInCountsPerSample_1();

    //float controlSignal = PIControl_Update(&controller, (float) velocity);

    sprintf(outBuffer, "Value: %0.3f\n\r\0", velocity);
    putsUART1(outBuffer);
    //        LED5=LEDOFF;
    //    speed -= controlSignal/MAX_V;
    return speed;
}

void controlMotorPosition(long pos, char *outBuffer, PIControl *controller)
{
    
    // Read encoder value
    long encoderValue = getPositionInCounts_1();
    long error = pos - encoderValue;
    
//    float p_term = controller->kp * (float) error;
    float speed = pi_control(controller, pos, encoderValue);
    set_Motor_velocity(speed);
   

    sprintf(outBuffer, "%ld, %0.3f \n\r\0", encoderValue, speed);
    putsUART1(outBuffer);
    //        LED5=LEDOFF;
    //    speed -= controlSignal/MAX_V;
}

void printPosition(char *outBuffer)
{
    float count = getPositionInRad();
    sprintf(outBuffer, "Value: %0.3f\n\0", count);
    putsUART1(outBuffer);
}

float set_velocity_potentiometer(char *outBuffer, PIControl *controller){
    float voltage = read_potentiometer();
    float speed = controlMotorVelocity(voltage/3.3, outBuffer, &controller);
}


int main()
{
//    int pinStatus;
#if (SEVEN_MEG_OSC == 0)
    /*** oscillator setup --------------------------------------------------
    * The external oscillator runs at 16MHz
    * PLL is used to generate 53.3 MHz clock (FOSC)
    * The relationship between oscillator and cycle frequency: FCY = FOSC/2
    * Have a look at "PLL Configuration" paragraph in the mcu manual

    * Result: FCY = 0.5 * (16MHz*20/(3*2)) = 26.666 MIPS, Tcycle=37.5nsec
   ---------------------------------------------------------------------***/
    PLLFBDbits.PLLDIV = 18; // set PPL to M=20 (18+2)
    CLKDIVbits.PLLPRE = 1;  // N1 = input/3
    CLKDIVbits.PLLPOST = 0; // N2 = output/2

#else  // Below the 7.3728 Setup

    /*** oscillator setup --------------------------------------------------
* The external oscillator runs at 7.3728 MHz
* PLL is used to generate 53.3 MHz clock (FOSC)
* The relationship between oscillator and cycle frequency: FCY = FOSC/2
* Have a look at "PLL Configuration" paragraph in the mcu manual

* Result: FCY = 0.5 * (7.3728 MHz*29/(2*2)) = 26.73 MIPS, which is
     * not exactl Tcycle=37.5nsec, but close enough for our purposes
---------------------------------------------------------------------***/
    PLLFBDbits.PLLDIV = 27; // set PPL to M=29 (27+2)
    CLKDIVbits.PLLPRE = 0;  // N1 = input/2
    CLKDIVbits.PLLPOST = 0; // N2 = output/2
#endif // SEVEN_MEG_OSC == 0

    /* Clock switch to incorporate PLL*/
    __builtin_write_OSCCONH(0x03); // Initiate Clock Switch to Primary

    // Oscillator with PLL (NOSC=0b011)
    __builtin_write_OSCCONL(OSCCON || 0x01); // Start clock switching

    while (OSCCONbits.COSC != 0b011)
        ;

    // In reality, give some time to the PLL to lock
    while (OSCCONbits.LOCK != 1)
        ; // Wait for PPL to lock

    setupIO(); // configures inputs and outputs
    initDmaChannel4();
    setupADC1();
    startADC1();
    setupPWM();

    //    initTimer2InMS(100);
    //    startTimer2();

    initQEI1(0); // Set the initial position of encoder 1 to 0
    initQEI2(0);

    setupUART1();
    // initTimer1(33333); //creates a 10ms timer interrupt

    LED4 = 1; // switches off  must be off for pwm

    LED5 = LEDOFF;

    LED6 = LEDOFF;

    LED7 = LEDOFF;

    char outBuffer[32];
    PIControl controller;

    float speed = 0.7; //-1 1
    float speedInTicks = speed * MAX_V;

    PIControl_Init(&controller, 0.01, 0.001, speedInTicks); // K_i and K_p are 0.5

    while (1)
    {
        //speed = set_velocity_potentiometer(outBuffer, &controller);
        //speed = (float)controlMotorVelocity(speed, outBuffer, &controller);
        controlMotorPosition(10000, outBuffer, &controller);
    };

    return 0;
}
