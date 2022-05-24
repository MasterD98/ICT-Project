/*
 * stepper.c
 *
 * Created: 5/22/2022 4:50:59 AM
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

void rotateStepper_2(int direction, float distance){
	// clockwise-1
	// Counterclockwise-0
	// 1 distance unit = 1 rotating

	int period;
	period = 100;
	if (direction == 1)
	{
		/* Rotate  clockwise */
		for (int i = 0; i < round(distance); i++)
		{
			PORTA = 0x30;
			_delay_ms(period);
			PORTA = 0x60;
			_delay_ms(period);
			PORTA = 0xc0;
			_delay_ms(period);
			PORTA = 0x90;
			_delay_ms(period);
			PORTA = 0x30;
			_delay_ms(period);
		}

		_delay_ms(10);
	}
	else
	{
		/* Rotate  Counterclockwise  */
		for (int i = 0; i < round(distance); i++)
		{
			PORTA = 0x30;
			_delay_ms(period);
			PORTA = 0x90;
			_delay_ms(period);
			PORTA = 0xc0;
			_delay_ms(period);
			PORTA = 0x60;
			_delay_ms(period);
			PORTA = 0x30;
			_delay_ms(period);
		}

		_delay_ms(10);
	}
}

void rotateStepper_3(int direction, float distance){
	// clockwise-1
	// Counterclockwise-0
	// 1 distance unit = 1 rotating

	int period;
	period = 100;
	if (direction == 1)
	{
		/* Rotate  clockwise */
		for(int i=0;i<distance;i++)
		{
			PORTC = 0x03;
			_delay_ms(period);
			PORTC = 0x06;
			_delay_ms(period);
			PORTC = 0x0c;
			_delay_ms(period);
			PORTC = 0x09;
			_delay_ms(period);
			PORTC = 0x03;
			_delay_ms(period);
		}

		_delay_ms(10);
	}
	else
	{
		/* Rotate  Counterclockwise  */
		for (int i = 0; i < distance; i++)
		{
			PORTC = 0x03;
			_delay_ms(period);
			PORTC = 0x09;
			_delay_ms(period);
			PORTC = 0x0c;
			_delay_ms(period);
			PORTC = 0x06;
			_delay_ms(period);
			PORTC = 0x03;
			_delay_ms(period);
		}

		_delay_ms(10);
	}
}

void rotateStepper_4(int direction){
	// clockwise-1
	// Counterclockwise-0
	// 1 distance unit = 1 rotating

	int period;
	period = 100;
	if (direction == 1)
	{
		/* Rotate  clockwise */
		PORTC = 0x30;
		_delay_ms(period);
		PORTC = 0x60;
		_delay_ms(period);
	}
	else
	{
		/* Rotate  Counterclockwise  */
		PORTC = 0x60;
		_delay_ms(period);
		PORTC = 0x30;
		_delay_ms(period);
	}
}