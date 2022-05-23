/*
 * stepper.c
 *
 * Created: 5/24/2022 12:18:20 AM
 *  Author: Dasith
 */ 
#include "stepper.h"

void initSteppers(){
	DDRA = 0xFF;
	DDRC = 0xFF;
}

void rotateStepper_1(int direction, float distance)
{
	// clockwise-1
	// Counterclockwise-0
	// 1 distance unit = 1 rotating

	int period;
	period = 100;
	if (direction == 1)
	{
		for (int i = 0; i < round(distance); i++)
		{
			PORTA = 0x03;
			_delay_ms(period);
			PORTA = 0x06;
			_delay_ms(period);
			PORTA = 0x0c;
			_delay_ms(period);
			PORTA = 0x09;
			_delay_ms(period);
			PORTA = 0x03;
			_delay_ms(period);
		}
	}
	else
	{
		for (int i = 0; i < round(distance); i++)
		{
			PORTA = 0x03;
			_delay_ms(period);
			PORTA = 0x09;
			_delay_ms(period);
			PORTA = 0x0c;
			_delay_ms(period);
			PORTA = 0x06;
			_delay_ms(period);
			PORTA = 0x03;
			_delay_ms(period);
		}
	}
}
