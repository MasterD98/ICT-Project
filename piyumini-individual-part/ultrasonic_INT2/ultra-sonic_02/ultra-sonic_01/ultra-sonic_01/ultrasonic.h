/*
 * ultrasonic.h
 *
 * Created: 5/24/2022 2:39:58 AM
 *  Author: Dasith
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
void initUltrasonic();
int getUltrasonic_2_distance();


#endif /* ULTRASONIC_H_ */