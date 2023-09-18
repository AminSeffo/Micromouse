#include "xc.h"
#include "IOconfig.h"

/*
 * Microcontroller:
 * DSPIC33FJ64MC804-E/PT
*/


void setupIO()
{

    int i;
    AD1PCFGL=0xFFFF; //all pins are now digital, by default they are analogue
    
   
    // set LEDs as output
    TRISBbits.TRISB11 = 0; //LED 1
    TRISBbits.TRISB10 = 0; //LED 2
    TRISBbits.TRISB9 = 0;  //LED 3

    TRISCbits.TRISC4=0;// UART TX (output)
    TRISCbits.TRISC3=1;// UART RX (input)
    
//    AD1PCFGLbits.PCFG8 = 0; //pin for button is analog
    
    TRISBbits.TRISB8 = 1; // Button 1 is an input
   

    //PIN MAPPING
    
    //before we map, we need to unlock
    __builtin_write_OSCCONL(OSCCON & 0xbf); // clear bit 6 (unlock, they are usually write protected)
    
    RPINR0bits.INT1R = 8; //INT1 mapped to RP8
    
    // PERIPHERAL receives data from which INPUT  
    RPINR18bits.U1RXR = 19; //mapped to RP9 is U1 RX, CHANGE THIS  //TODO: check if this is correct
    RPOR10bits.RP20R = 3;
    
    //PERIPHERAL QEA Encoder 1, receives data from RP25
   RPINR14bits.QEA1R = 25; 
    //PERIPHERAL QEB Encoder 1, receives data from RP24
   RPINR14bits.QEB1R = 24;

    //PERIPHERAL QEA Encoder 2, receives data from RP22
   RPINR16bits.QEA2R = 22; 
    //PERIPHERAL QEB Encoder 2, receives data from RP23
   RPINR16bits.QEB2R = 23;


   //motor input
   //motor 2
   TRISBbits.TRISB12 = 0; 
    TRISBbits.TRISB13 = 0;
    //motor 1
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB15 = 0;

    
    
    
    //OUTPUT PIN receives data from which PERIPHERAL, 
    //see table 11-2 in datasheet to check peripheral codes 
    //PORTAbits.RA7=0b00011; //output pin RA7 gets data from peripheral U1 TX
   
    //after mapping we lock again
     __builtin_write_OSCCONL(OSCCON | 0x40); // Lock PPS registers (lock again!)
     
    for (i = 0; i < 30000; i++); // short dirty delay for changes to take effect,

    
}
