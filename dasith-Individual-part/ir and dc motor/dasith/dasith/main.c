/*
 * dasith.c
 *
 * Created: 5/24/2022 2:56:44 AM
 * Author : Dasith
 */ 

#include <avr/io.h>

#include "dcmotor.h"

int main(void)
{
    initDCMotors();
	while (1) 
    {
		
		if ((PIND & 1 << PD5) && (PIND & 1 << PD6)){ // if both Ir sensor-2,3 are detected pipe
			rotateDCMotors(1);
			while (PIND & (1 << PD6));
		}
		else if (!(PIND & 1 << PD5) && !(PIND & 1 << PD6)){ // else if both Ir sensor-2,3 are not detected pipe
			rotateDCMotors(0);
			while (!(PIND & (1 << PD5)));
		}
		stopDCMotors();
    }
}

