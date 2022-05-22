/*
 * stepper.h
 *
 * Created: 5/22/2022 4:53:02 AM
 *  Author: Dasith
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void initSteppers();
void rotateStepper_1(int direction, float distance);
void rotateStepper_2(int direction, float distance);
void rotateStepper_3(int direction, float distance);
void rotateStepper_4(int direction);

#endif /* STEPPER_H_ */