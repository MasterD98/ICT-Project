/*
 * dcmotor.h
 *
 * Created: 5/22/2022 4:47:29 AM
 *  Author: Dasith
 */ 


#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include <avr/io.h>

void rotateDCMotors(int direction);
void stopDCMotors();

#endif /* DCMOTOR_H_ */