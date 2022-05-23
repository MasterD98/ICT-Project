/*
 * ultrasonic.c
 *
 * Created: 5/24/2022 1:45:03 AM
 *  Author: Dasith
 */ 

#include "ultrasonic.h"

static volatile int ult2_count = 0; // interger  to access all though the program
static volatile int i = 0;

void initUltrasonic(){
	DDRB |=(1<<PB6);
	_delay_ms(50);

	GICR |= (1<<INT1); //enabling interupt 0
	//General Interrupt Control Register
	MCUCR|= (1<<ISC10); //setting interrupt triggering logic change
	// MCU control Register
	TCCR1A = 0;
}

int getUltrasonic_2_Distance(){
	int pulse;
	PORTB |= (1<<PB6);
	_delay_us(20); //triggering the sensor for 15usec
	PORTB &= (~(1<<PB6));
	
	while(ult2_count==NULL);
	
	pulse=ult2_count;
	ult2_count=NULL;
	return (pulse/928)+1;
}

ISR(INT1_vect) //interrupt service routine when there is a change in logic level

{

	if (i==1)//when logic from HIGH to LOW

	{

		TCCR1B=0; //disabling counter

		ult2_count=TCNT1;//count memory is updated to intege

		TCNT1=0;//resetting the counter memory

		i=0;

	}

	if (i==0)//when logic change from LOW to HIGH

	{

		TCCR1B|=(1<<CS10);//enabling counter

		i=1;

	}

}