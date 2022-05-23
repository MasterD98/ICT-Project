/*
 * stepper.h
 *
 * Created: 5/23/2022 10:21:12 PM
 *  Author: Dasith
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initSteppers();
void rotateStepper_3(int direction, float distance);

#endif /* STEPPER_H_ */