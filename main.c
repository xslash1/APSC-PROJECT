#include <stdio.h>
#include <xc.h>
#include "..\Robot\sumovore.h"
#include "..\Robot\motor_control.h"
#include "..\Robot\interrupts.h"
#include "..\Robot\osc.h"
#include <p18f4525.h>

// main acts as a cyclical task sequencer
void main(void)
{
   set_osc_32MHz();       // select 32 MHz oscillator speed
   
    initialization(); // function from sumovore.c
                      // it sets up pwm (using timer2),
                      // IO pins, the ADC, the 
                      // USART and the default
                      // threshold
    printf("\n\rKwantlen APSC1299 simple curve follower -- with error codes\n\r"); 
    ClrWdt();         // defined in <p18f4525.h>

	threshold = 450u; // to change from default value
                     // uncomment and change to any unsigned int <1024u -- most usually <512u
	
	OpenTimer0(TIMER_INT_OFF & T0_SOURCE_INT & T0_16BIT & T0_PS_1_1);
	
    while(1)
    {
        check_sensors();    // from sumovore.c
        set_leds();         // function from sumovore.c
	                    // each LED indicates a sensor
	                    // value. If you need to use the LED's for
	                    // a different purpose change this line
	                    // and make your own LED setting function
        motor_control();    // function from motor_control.c 
        ClrWdt();           // defined in <p18f4525.h>
        if(lvd_flag_set())  LVtrap();
    }
}
 
