/*
* Helper Functions for the potentiometer
* Author: Yara 
*/


/*
* switch the LED5 on if the voltage from potentiomenter is higher than 3.5V
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

/*
* dim the LED with the potentiometer
*/
void dim_LED_potentiometer(float voltage)
{
    // setupDC1PWM1(TEST_SENSOR/670);
    setupDC1PWM1(voltage / 3.3);
}

/*
* test the potentiometer by dimming LED
*/
void potentiometer_test()
{
    float voltage = read_potentiometer();
    dim_LED_potentiometer(voltage);
}

/*
* read the voltage from the potentiometer
*/
float read_potentiometer(){
    float refVoltage, voltage;
    refVoltage = 3.3 / 4096;
    voltage = TEST_SENSOR * refVoltage;
    
    return voltage;
}

