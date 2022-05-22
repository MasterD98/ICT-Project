/*
 * Motor controller.c
 *
 * Created: 5/22/2022 3:43:10 AM
 * Author : Dasith Rathnasinghe
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include <stdio.h>
#include "ultrasonic.h"
#include "usart.h"
#include "dcmotor.h"
#include "stepper.h"


int wasteBinDistance1 = 20;
int wasteBinDistance2 = 10;
int minLen=4;
int maxRadius=25;
char* receivedData;
int isInputDataRecevied;




ISR(USART_RXC_vect){
	receivedData=UDR;
	isInputDataRecevied=1;
}

int main(void)
{
	int ult1_distance;
	int ult2_distance;
	int ult3_distance;
	int rounds;
	int length;
	int isMetal;
	isInputDataRecevied=0;
	initUltrasonic();
	initUSART();
	initSteppers();
	sei(); //enable global interrupts
	while (1)
	{
		while (!(PIND & 1 << PD4)); // Wait until pipe place

		if (PINB & 1 << PB5){ // Change DC motor speed
			// metal
			isMetal = 1;
			sendData("HIGH");
			
			}else{
			// PVC
			isMetal = 0;
			sendData("LOW");
		}

		// TODO USART send message

		// tight clutches1&2
		// Check ultrasonic sensor output
		ult2_distance = getUltrasonic_2_Distance();
		ult3_distance = getUltrasonic_3_Distance();
		// move both clutches forward until ultrasonic output smallest number
		rotateStepper_1(1, ult2_distance);
		rotateStepper_2(1, ult3_distance);
		while ((getUltrasonic_2_Distance() >= 3) && (getUltrasonic_3_Distance() >= 3));

		// move clutches through rail to align

		if ((PIND & 1 << PD5) && (PIND && 1 << PD6)){ // if both Ir sensor-2,3 are detected pipe
			rotateDCMotors(1);
			while (PIND && 1 << PD6);
			stopDCMotors();
		}
		else if (!(PIND & 1 << PD5) && !(PIND && 1 << PD6)){ // else if both Ir sensor-2,3 are not detected pipe
			rotateDCMotors(0);
			while (!(PIND & 1 << PD5));
			stopDCMotors();
		}

		while(!isInputDataRecevied);
		length=receivedData;
		isInputDataRecevied=0;
		while(!isInputDataRecevied);
		rounds=receivedData;
		isInputDataRecevied=0;

		// repeat cutting process(loop rounds time)
		for (int i = 0; i < rounds; i++)
		{
			//rotate stepper motor2 and 1 backwards
			rotateStepper_1(0,maxRadius);
			rotateStepper_2(0,maxRadius);
			while ((getUltrasonic_2_Distance() < maxRadius) && (getUltrasonic_3_Distance() < maxRadius));
			// move pipe forward according to the calculated length
			rotateDCMotors(0);
			while(getUltrasonic_1_Distance()>3);
			// Check ultrasonic sensor output
			ult2_distance = getUltrasonic_2_Distance();
			ult3_distance = getUltrasonic_3_Distance();
			//rotate stepper motor2 and 1 forward
			rotateStepper_1(1, ult2_distance);
			rotateStepper_2(1, ult3_distance);

			// get ultrasonic1 output distance (distance1)
			ult1_distance=getUltrasonic_1_Distance();
			// move clutches though rail until ult1_distance-instantDistance==length
			rotateDCMotors(1);
			while((getUltrasonic_1_Distance()-ult1_distance)<length)
			stopDCMotors();
			// rotate stepper motor3 forward
			rotateStepper_3(1,maxRadius);
			// pipe cutting process
			// start rotating cutting blade DC motor
			sendData("START");
			// rotate stepper motor4
			rotateStepper_4(1);
			rotateStepper_4(0);
			rotateStepper_3(0,maxRadius);
		}

		// check if leftover pipe is waste or not
		if (!(PIND & 1 << PD4)){
			// move both clutches backward though rail
			rotateDCMotors(0);
			while (getUltrasonic_1_Distance() == wasteBinDistance1)
			;
			stopDCMotors();
			if (isMetal){
				// move clutch1 backward && clutch2 forward
				rotateStepper_1(0,wasteBinDistance2);
				rotateStepper_2(1,wasteBinDistance2);
				// when position correctly, drop wastage
				rotateStepper_2(0,wasteBinDistance2);
				_delay_ms(100);
				rotateStepper_1(1,wasteBinDistance2);
				}else{
				// move clutch2 backward && clutch1 forward
				rotateStepper_1(1,wasteBinDistance2);
				rotateStepper_2(0,wasteBinDistance2);
				// when position correctly, drop wastage
				rotateStepper_1(0,wasteBinDistance2);
				_delay_ms(100);
				rotateStepper_2(1,wasteBinDistance2);
			}
		}
	}
}


