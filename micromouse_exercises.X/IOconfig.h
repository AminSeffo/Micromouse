/* 
 * File:   IOconfig.h
 * Author: adamp
 *
 * Created on 13 December 2019, 09:38
 */

#ifndef IOCONFIG_H
#define	IOCONFIG_H


#define LED1 LATBbits.LATB11
#define LED2 LATBbits.LATB10
#define LED3 LATBbits.LATB9

#define SW1 !PORTBbits.RB8 //todo: this is not used??


#define LEDON 0
#define LEDOFF 1

void setupIO();

#endif	/* IOCONFIG_H */

