/*
 * ATmega16_LED_Blinking.c
 * http://www.electronicwings.com
 * Created: Created Date & Created Time
 * Author : Author Name
 */ 

#define F_CPU 8000000UL	/* Define CPU frequency here 8MHz */
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB = 0xFF;	/* Make all pins of PORTB as output pins */
    
    while (1)		/* Blink PORTB infinitely */
    {
	PORTB = 0x00;
	_delay_ms(500);	/* Delay of 500 milli second */
	PORTB = 0xFF;
	_delay_ms(500);
    }
}