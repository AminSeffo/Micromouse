/* 
 * File:   button.h
 * Author: yara
 *
 * Created on September 9, 2023, 2:04 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H


#include <xc.h>




void setupButton(void (*f)(float));

#define BUTTON_STATE PORTBbits.RB8;

#define BUTTONON 0;
#define BUTTONOFF 1;

#endif	/* BUTTON_H */

