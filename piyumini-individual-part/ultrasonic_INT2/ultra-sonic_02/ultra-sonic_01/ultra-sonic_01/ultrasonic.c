/*
 * ultrasonic.c
 *
 * Created: 5/24/2022 2:35:17 AM
 *  Author: Dasith
 */
#include "ultrasonic.h"
int timerOverFlow=0;
static volatile int ult3_count=NULL; 

void initUltrasonic(){
	DDRB |= (1<<PB7);

	GICR |= (1<<INT2); //enabling interupt 2
	//General Interrupt Control Register
	MCUCSR|= (1<<ISC2) ; //setting interrupt triggering logic LOW to HIGH
	// MCU control Register
	TIMSK|=(1<<TOIE2);
	
	TCCR2 = 0;
}

int getUltrasonic_2_distance(){
	int pulse;
	PORTB |= (1<<PB7);
	_delay_us(15); //triggering the sensor for 15usec
	PORTB &= (~(1<<PB7));
	while(ult3_count==NULL);
	
	pulse=ult3_count;
	ult3_count=NULL;
	return pulse/932.8+1;
}

ISR(INT2_vect) //interrupt service routine when there is a change in logic level

{

	if ((MCUCSR & (1<<ISC2))){//when logic change from LOW to HIGH

		TCCR2|=(1<<CS10);//enabling counter
		//i=1;
		MCUCSR &= ~(1<<ISC2) ; //HIGH to LOW
		}else{//when logic from HIGH to LOW

		TCCR2=0; //disabling counter

		ult3_count=TCNT2+timerOverFlow;//count memory is updated to integer

		TCNT2=0;//resetting the counter memory
		//i=0;
		MCUCSR|= (1<<ISC2) ;
	}
	timerOverFlow=0;

}

ISR(TIMER2_OVF_vect)
{
	timerOverFlow+=256;
}