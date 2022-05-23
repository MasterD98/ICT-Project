/*
 * main.c
 *
 * Created: 5/12/2022 11:28:23 AM
 *  Author: milanka
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

#include "stepper.h"

int main(void){

	initSteppers();
	rotateStepper_3(1,1);
}

