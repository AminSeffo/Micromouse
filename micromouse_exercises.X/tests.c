#include "tests.h"
#include "xc.h"
#include "IOconfig.h"


void runLedTest()
{	
	setupIO();

	LED1 = LEDOFF;

    LED2 = LEDON;

    LED3 = LEDOFF;
}
