#include <avr/io.h>

#define F_CPU 16000000UL
#define START 1
#define STOP 0
#define HIGH_SPEED 2
#define LOW_SPEED 3

#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"
static uint8_t data;

int main(void)
{

	initUSART(9600);
	DDRA =0x0F;
	
	while(1){
		
		data=getReceivedData();
		
		if (data == START){
			PORTA |= (1 << PA0);
		}
		if (data==STOP)
		{
			PORTA |= (1 << PA1);
		}
		if (data==HIGH_SPEED)
		{
			PORTA |= (1 << PA2);
		}
		if (data==LOW_SPEED)
		{
			PORTA |= (1 << PA3);
		}
	}
}