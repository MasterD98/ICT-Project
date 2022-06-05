#include <avr/io.h>

//header to enable data flow control over pins

#define F_CPU 16000000UL
#define START 1
#define STOP 0
#define HIGH_SPEED 2
#define LOW_SPEED 3

#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"


int main(void){
	initUSART(9600);
	
	while (1){
		
		if (PINA & (1<<PA0)){
			sendData(START);
		}
		if (PINA & (1<<PA1))
		{
			sendData(STOP);
		}
		if (PINA & (1<<PA2))
		{
			sendData(HIGH_SPEED);
		}
		if (PINA & (1<<PA3))
		{
			sendData(LOW_SPEED);
		}
	}
}

