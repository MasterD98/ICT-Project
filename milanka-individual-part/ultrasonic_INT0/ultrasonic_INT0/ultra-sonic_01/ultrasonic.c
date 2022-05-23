/*
 * CFile1.c
 *
 * Created: 5/23/2022 8:55:10 PM
 *  Author: Dasith
 */ 

#include "ultrasonic.h"

static volatile int pulse = 0; // interger  to access all though the program
static volatile int i = 0;
int timerOverFlow=0;
static volatile int ult_count=NULL;

void initUltrasonic(){
	GICR |= (1<<INT0); //enabling interupt 0
	//General Interrupt Control Register
	MCUCR|= (1<<ISC00); //setting interrupt triggering logic change
	// MCU control Register
	TIMSK|=(1<<TOIE0);
	
	TCCR0 = 0;
}

int getUltrasonic_1_distance(){
	int pulse;
	PORTD |= (1<<PIND7);
	_delay_us(15); //triggering the sensor for 15usec
	PORTD &= (~(1<<PIND7));
	
	while(ult_count==NULL);
	
	pulse=ult_count;
	ult_count=NULL;
	return (pulse/58)+1;
}

ISR(INT0_vect) //interrupt service routine when there is a change in logic level

{

	if (i==1)//when logic from HIGH to LOW

	{

		TCCR0=0; //disabling counter

		ult_count=TCNT0+timerOverFlow;//count memory is updated to intege
		
		TCNT0=0;//resetting the counter memory

		i=0;

	}

	if (i==0)//when logic change from LOW to HIGH

	{

		TCCR0|=(1<<CS10);//enabling counter

		i=1;

	}
	timerOverFlow=0;

}

ISR(TIMER0_OVF_vect)
{
	timerOverFlow+=256;
}