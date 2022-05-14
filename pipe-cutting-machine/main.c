/*
 * pipe-cutting-machine.c
 *
 * Created: 5/8/2022 6:59:49 PM
 * Author : Dasith
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		//Wait until IRsensor-1 output
			//if Ir sensor-1 true (when pipe was placed clutch 1 & 2 move towards the pipe)
				//check for proximity sensor output
					//if metal
						//set motor speed to metal speed
					//else
						//set motor speed to PVC speed

					//tight clutches1&2
					//move moth clutches forward until ultrasonic output zero
					//Check ultrasonic sensor output
					//While ultrasonic sensor output distance == some value(0)
						//rotate stepper motors (forward)
					
					//move clutches through rail to align
					//if both Ir sensor-2,3 are detected pipe
						//move clutches through rail backwards while senser3 true
							//while sensor3 true
								//rotate DC motor backward
					//else if both Ir sensor-2,3 are not detected pipe
						//move clutches through rail forward
							//move clutches through rail forward while senser2 false
							//while sensor3 false
							//rotate DC motor forward

			//wait for user keypad input
				//get user input
				//display input
				//ask for need quantity save that
				//ask for unit save that
				//calculate length
				//calculate rounds

			//repeat cutting process
			//while rounds==0
				//rotate stepper motor3 forward 
				//move pipe forward according to the calculated length
				//get ultrasonic3 output distance (distance1)
					//move clutches though rail until distance1-instantDistance==length
					//float DifferenceOfDistance=0;
					//while(DifferenceOfDistance>=legth)
						//getDifferenceOfDistance
						//rotate DC motor
				//pipe cutting process
				//activate cutting blade
				//start rotating DC motor
				//rotate stepper motor4
				//rotate stepper motor3 backward 
			//rotate stepper motor3 forward

		//check if leftover pipe is waste or not
			//if irsensor1 false
				//move both clutches backward though rail
				//if metal 
					//move clutch1 backward && clutch2 forward
				//else
					//move clutch2 backward && clutch1 forward	
    }
}

