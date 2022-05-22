/*
 * dcmotor.c
 *
 * Created: 5/22/2022 4:47:15 AM
 *  Author: Dasith
 */ 

#include "dcmotor.h"

void rotateDCMotors(int direction)
{
	if (direction != 0)
	{
		// Rotate DC motor Clockwise ?
		PORTC &= ~(1 << PB0);
		PORTC |= (1 << PB1);
	}
	else
	{
		// Else rotate DC motor Counterclockwise
		PORTC |= (1 << PB0);
		PORTC &= ~(1 << PB1);
	}
}

void stopDCMotors()
{
	// stop Rotation DC motor
	PORTC &= ~(1 << PB0);
	PORTC &= ~(1 << PB1);
}