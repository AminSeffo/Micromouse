/* 
 * File:   button.h
 * Author: yara
 *
 * Created on September 9, 2023, 2:04 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H


#include <xc.h>




void initButton(void (*func)());

#define BUTTON_STATE PORTBbits.RB8;


#endif	/* BUTTON_H */

