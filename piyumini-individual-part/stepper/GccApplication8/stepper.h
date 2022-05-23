/*
 * stepper.h
 *
 * Created: 5/24/2022 12:18:50 AM
 *  Author: Dasith
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void initSteppers();
void rotateStepper_1(int direction, float distance);

#endif /* STEPPER_H_ */