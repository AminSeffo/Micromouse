#include "led.h"
#include "IOconfig.h"
#include "xc.h"

void setLed1(int on){
    if (on)
        LED1 = LEDON;
    else
        LED1 = LEDOFF;
}

void setLed2(int on){
    if (on)
        LED2 = LEDON;
    else
        LED2 = LEDOFF;
}

void setLed3(int on){
    if (on)
        LED3 = LEDON;
    else
        LED3 = LEDOFF;
}
