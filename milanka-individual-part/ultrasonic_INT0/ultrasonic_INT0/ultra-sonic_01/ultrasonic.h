/*
 * ultrasonic.h
 *
 * Created: 5/23/2022 9:11:00 PM
 *  Author: Dasith
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>


void initUltrasonic();
int getUltrasonic_1_distance();


#endif /* ULTRASONIC_H_ */