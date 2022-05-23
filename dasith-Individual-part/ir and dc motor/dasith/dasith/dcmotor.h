/*
 * dcmotor.h
 *
 * Created: 5/24/2022 2:59:24 AM
 *  Author: Dasith
 */ 


#ifndef DCMOTOR_H_
#define DCMOTOR_H_
#define F_CPU 16000000UL
#include <avr/io.h>

void rotateDCMotors(int direction);
void stopDCMotors();
void initDCMotors();

#endif /* DCMOTOR_H_ */