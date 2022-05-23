/*
 * ultra-sonic_01.c
 *
 * Created: 12/3/2021 11:21:51 AM
 * Author : milanka
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "LCD.h"
#include "ultrasonic.h"	

int main(void)
{
	LCD_Init();
	initUltrasonic();
 
    int16_t count_a = 0;
    char show_a[16];
	sei();
	
	while(1)
	{
		count_a =getUltrasonic_2_Distance();
		
		LCD_String_xy(0, 0, "Ultrasonic");
        itoa(count_a,show_a,10);
		LCD_String_xy(1, 0, "Distance= ");
		LCD_String_xy(1, 9, show_a);
		LCD_String_xy(1, 13, "cm");
			
		_delay_ms(200);
		
	}
}


















	


