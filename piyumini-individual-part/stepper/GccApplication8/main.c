/*
 * GccApplication8.c
 *
 * Created: 5/23/2022 9:18:48 PM
 * Author : ASUS®
 */ 

#define F_CPU 16000000UL
#include "stepper.h"

int main(void)
{
	initSteppers();
	rotateStepper_1(1,4);
}




