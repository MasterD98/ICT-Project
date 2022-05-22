/*
 * CFile1.c
 *
 * Created: 5/22/2022 4:22:36 AM
 *  Author: Dasith
 */ 

#include "ultrasonic.h"

static volatile int pulse1 = 0; // integer  to access all though the program
static volatile int i = 0;
static volatile int pulse2 = 0; // integer  to access all though the program
static volatile int j = 0;
static volatile int pulse3 = 0; // integer  to access all though the program
static volatile int ult1_count = 0;
static volatile int ult2_count = 0;
static volatile int ult3_count = 0;

void initUltrasonic()
{
	//Initialize Ultrasonic-1
	DDRD |= 1 << PIND7;	 // set PD7 output
	DDRD &= ~(1 << PD2); // set PD2 Input
	GICR |= (1 << INT0); // enabling interupt 0
	// General Interrupt Control Register
	MCUCR |= (1 << ISC00); // setting interrupt triggering logic change
	// MCU control Register
	TCCR1A = 0;
	
	//Initialize Ultrasonic-1
	DDRB |= 1 << PB6;	 // set PB6 output
	DDRB &= ~(1 << PB3); // set PB3 Input
	GICR |= (1 << INT1); // enabling interupt 1
	// General Interrupt Control Register
	MCUCR |= (1 << ISC10); // setting interrupt triggering logic change
	// MCU control Register
	TCCR0 = 0;
	
	//Initialize Ultrasonic-1
	DDRB |= 1 << PB7;	 // set PB7 output
	DDRB &= ~(1 << PB2); // set PB2 Input
	GICR |= (1 << INT2); // enabling interupt 2
	// General Interrupt Control Register
	MCUCSR |= (1 << ISC2); // setting interrupt triggering logic LOW to HIGH
	// MCU control Register
	TCCR2 = 0;
}

int getUltrasonic_1_Distance()
{
	PORTD |= (1 << PIND7);
	_delay_us(15); // triggering the sensor for 15usec
	PORTD &= (~(1 << PIND7));
	_delay_ms(1000);
	return ult1_count;
}

int getUltrasonic_2_Distance()
{
	PORTB |= (1 << PB6);
	_delay_us(15); // triggering the sensor for 15usec
	PORTB &= (~(1 << PB6));
	_delay_ms(1000);
	return ult2_count;
}

int getUltrasonic_3_Distance()
{
	PORTB |= (1 << PB7);
	_delay_us(15); // triggering the sensor for 15usec
	PORTB &= (~(1 << PB7));
	_delay_ms(1000);
	return ult3_count;
}

ISR(INT0_vect) // interrupt service routine when there is a change in logic level
{

	if (i == 0)
	{ // when logic change from LOW to HIGH

		TCCR1B |= (1 << CS10); // enabling counter

		i = 1;
	}
	if (i == 1)
	{
		TCCR1B = 0; // disabling counter

		pulse1 = TCNT1; // count memory is updated to intege

		TCNT1 = 0; // resetting the counter memory
		ult1_count = (pulse1 / 58) + 1;
		i = 0;
	}
}

ISR(INT1_vect) // interrupt service routine when there is a change in logic level
{

	if (j == 0)
	{ // when logic change from LOW to HIGH

		TCCR1B |= (1 << CS10); // enabling counter

		i = 1;
	}
	if (j == 1)
	{
		TCCR1B = 0; // disabling counter

		pulse2 = TCNT1; // count memory is updated to intege

		TCNT1 = 0; // resetting the counter memory
		ult2_count = (pulse2 / 58) + 1;
		j = 0;
	}
}

ISR(INT2_vect) // interrupt service routine when there is a change in logic level
{

	if ((MCUCSR & (1 << ISC2)))
	{ // when logic change from LOW to HIGH

		TCCR1B |= (1 << CS10);	// enabling counter
		MCUCSR &= ~(1 << ISC2); // HIGH to LOW
	}
	else
	{ // when logic from HIGH to LOW

		TCCR1B = 0; // disabling counter

		pulse3 = TCNT1; // count memory is updated to integer
		ult3_count = round(pulse3 / 58.3);
		TCNT1 = 0; // resetting the counter memory
		MCUCSR |= (1 << ISC2);
	}
}