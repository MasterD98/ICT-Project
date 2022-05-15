/*
 * pipe-cutting-machine.c
 *
 * Created: 5/8/2022 6:59:49 PM
 * Author : Dasith Rathnasinghe
 * Atmega32-1
 */ 

#include <avr/io.h>


static volatile int pulse1 = 0; // interger  to access all though the program
static volatile int i = 0;
static volatile int pulse2 = 0; // interger  to access all though the program
static volatile int j = 0;
static volatile int pulse3 = 0; // interger  to access all though the program
int ult1_count=NULL;
int ult2_count=NULL;
int ult3_count=NULL;
int wasteBinDistance=10;


void rotateDCMotors(int direction){
	if (direction !=0){
		// Rotate DC motor Clockwise ?
		PORTC &= ~(1<<PB0);
		PORTC |= (1<<PB1);?

	}else{
		// Else rotate DC motor Counterclockwise
		PORTC |= (1<<PB0);
		PORTC &= ~(1<<PB1);?
	}?
}
void stopDCMotors(){
		//stop Rotation DC motor
		PORTC &= ~(1<<PB0);
		PORTC &= ~(1<<PB1);?
	}?
}

void rotateStepper1(int direction , float distance){
	//clockwise-1
	//Counterclockwise-0
	//1 distance unit = 1 rotating
	
	int period;	DDRA = 0xF;	period = 10;
	if(direction==1){
		for(int i=0;i<round(distance);i++){
			PORTA = 0x03;
			_delay_ms(period);
			PORTA = 0x02;
			_delay_ms(period);
			PORTA = 0x06;
			_delay_ms(period);
			PORTA = 0x04;
			_delay_ms(period);
			PORTA = 0x0c;
			_delay_ms(period);
			PORTA = 0x08;
			_delay_ms(period);
			PORTA = 0x09;
			_delay_ms(period);
			PORTA = 0x01;
			_delay_ms(period);
			PORTA = 0x03;
			_delay_ms(period);
		}
	}else{
		for(int i=0;i<round(distance);i++){
			PORTA = 0x03;
			_delay_ms(period);
			PORTA = 0x09;
			_delay_ms(period);
			PORTA = 0x0c;
			_delay_ms(period);
			PORTA = 0x06;
			_delay_ms(period);
			PORTA = 0x03;
			_delay_ms(period);
		}
	}
}

void rotateStepper2(int direction , float distance){//TODO
	//clockwise-1
	//Counterclockwise-0
	//1 distance unit = 1 rotating
	
	int period;
	DDRA = 0xf0;
	period = 10;
	if(direction==1){
		/* Rotate  clockwise */
		for(int i=0;i<50;i++)
		{
			PORTA = 0x30;
			_delay_ms(period);
			PORTA = 0x20;
			_delay_ms(period);
			PORTA = 0x60;
			_delay_ms(period);
			PORTA = 0x40;
			_delay_ms(period);
			PORTA = 0xc0;
			_delay_ms(period);
			PORTA = 0x80;
			_delay_ms(period);
			PORTA = 0x90;
			_delay_ms(period);
			PORTA = 0x10;
			_delay_ms(period);
			PORTA = 0x30;
			_delay_ms(period);
		}
		
		_delay_ms(10);
	}else{
		/* Rotate  Counterclockwise  */
		for(int i=0;i<50;i++)
		{
			PORTA = 0x30;
			_delay_ms(period);
			PORTA = 0x90;
			_delay_ms(period);
			PORTA = 0xc0;
			_delay_ms(period);
			PORTA = 0x60;
			_delay_ms(period);
			PORTA = 0x30;
			_delay_ms(period);
		}
		
		_delay_ms(10);	
	}
}

void rotateStepper3(int direction , float distance){//TODO
	//clockwise-1
	//Counterclockwise-0
	//1 distance unit = 1 rotating
	
	int period;
	DDRC = 0x0F;
	period = 10;
	if(direction==1){
		/* Rotate  clockwise */
		for(int i=0;i<50;i++)
		{
		PORTC = 0x03;
		_delay_ms(period);
		PORTC = 0x02;
		_delay_ms(period);
		PORTC = 0x06;
		_delay_ms(period);
		PORTC = 0x04;
		_delay_ms(period);
		PORTC = 0x0c;
		_delay_ms(period);
		PORTC = 0x08;
		_delay_ms(period);
		PORTC = 0x09;
		_delay_ms(period);
		PORTC = 0x01;
		_delay_ms(period);
		PORTC = 0x03;
		_delay_ms(period);
		}
		
		_delay_ms(10);
	}else{
		/* Rotate  Counterclockwise  */
		for(int i=0;i<50;i++)
		{
			PORTC = 0x03;
			_delay_ms(period);
			PORTC = 0x09;
			_delay_ms(period);
			PORTC = 0x0c;
			_delay_ms(period);
			PORTC = 0x06;
			_delay_ms(period);
			PORTC = 0x03;
			_delay_ms(period);
		}
		
		_delay_ms(10);
	}
}

void rotateStepper4(int direction , float distance){//TODO
	//clockwise-1
	//Counterclockwise-0
	//1 distance unit = 1 rotating
	
	int period;
	DDRC = 0xF0;
	period = 10;
	if(direction==1){
		/* Rotate  clockwise */
		for(int i=0;i<15;i++) //108 degree cutting arm
		{
			PORTC = 0x30;
			_delay_ms(period);
			PORTC = 0x20;
			_delay_ms(period);
			PORTC = 0x60;
			_delay_ms(period);
			PORTC = 0x40;
			_delay_ms(period);
			PORTC = 0xc0;
			_delay_ms(period);
			PORTC = 0x80;
			_delay_ms(period);
			PORTC = 0x90;
			_delay_ms(period);
			PORTC = 0x10;
			_delay_ms(period);
			PORTC = 0x30;
			_delay_ms(period);
		}
		
		_delay_ms(10);
		}else{
		/* Rotate  Counterclockwise  */
		for(int i=0;i<15;i++)
		{
			PORTC = 0x30;
			_delay_ms(period);
			PORTC = 0x90;
			_delay_ms(period);
			PORTC = 0xc0;
			_delay_ms(period);
			PORTC = 0x60;
			_delay_ms(period);
			PORTC = 0x30;
			_delay_ms(period);
		}
		
		_delay_ms(10);
	}
}



void initUltrasonic1(){
	DDRD |= 1<<PIND7;//set PD7 output
	DDRD &= ~(1<<PD2);//set PD2 Input
	GICR |= (1<<INT0); //enabling interupt 0
	//General Interrupt Control Register
	MCUCR|= (1<<ISC00); //setting interrupt triggering logic change
	// MCU control Register
	TCCR1A = 0;
}

int getUltrasonic1Distance(){
	int temp;
	PORTD |= (1<<PIND7);
	_delay_us(15); //triggering the sensor for 15usec
	PORTD &= (~(1<<PIND7));
	
	while (ult1_count==NULL);
	temp=ult1_count;
	ult1_count=NULL;
	return temp;
}

ISR(INT0_vect) //interrupt service routine when there is a change in logic level

{
	
	if (i==0){//when logic change from LOW to HIGH

		TCCR1B|=(1<<CS10);//enabling counter

		i=1;

	}
	if(i==1){
		TCCR1B=0; //disabling counter

		pulse1=TCNT1;//count memory is updated to intege

		TCNT1=0;//resetting the counter memory
		ult1_count =(pulse1/58)+1;
		i=0;
	}
}

void initUltrasonic2(){
	DDRB |= 1<<PB6;//set PB6 output
	DDRB &= ~(1<<PB3);//set PB3 Input
	GICR |= (1<<INT1); //enabling interupt 1
	//General Interrupt Control Register
	MCUCR|= (1<<ISC10); //setting interrupt triggering logic change
	// MCU control Register
	TCCR1A = 0;
}

int getUltrasonic2Distance(){
	int temp;
	
	PORTB |= (1<<PB6);
	_delay_us(15); //triggering the sensor for 15usec
	PORTB &= (~(1<<PB6));
	
	while (ult2_count==NULL);
	temp=ult2_count;
	ult2_count=NULL;
	return temp;
}

ISR(INT1_vect) //interrupt service routine when there is a change in logic level

{
	
	if (j==0){//when logic change from LOW to HIGH

		TCCR1B|=(1<<CS10);//enabling counter

		i=1;

	}
	if(j==1){
		TCCR1B=0; //disabling counter

		pulse2=TCNT1;//count memory is updated to intege

		TCNT1=0;//resetting the counter memory
		ult2_count =(pulse2/58)+1;
		j=0;
	}
}


void initUltrasonic3(){
	DDRB |= 1<<PB7;//set PB7 output
	DDRB &= ~(1<<PB2);//set PB2 Input
	GICR |= (1<<INT2); //enabling interupt 2
	//General Interrupt Control Register
	MCUCSR|= (1<<ISC2) ; //setting interrupt triggering logic LOW to HIGH
	// MCU control Register
	TCCR1A = 0;
}

int getUltrasonic3Distance(){
	int temp;
	
	PORTB |= (1<<PB7);
	_delay_us(15); //triggering the sensor for 15usec
	PORTB &= (~(1<<PB7));
	
	while (ult3_count==NULL);
	temp=ult3_count;
	ult3_count=NULL;
	return temp;
}

ISR(INT2_vect) //interrupt service routine when there is a change in logic level

{

	if ((MCUCSR & (1<<ISC2))){//when logic change from LOW to HIGH

		TCCR1B|=(1<<CS10);//enabling counter
		MCUCSR &= ~(1<<ISC2) ; //HIGH to LOW
		}else{//when logic from HIGH to LOW

		TCCR1B=0; //disabling counter

		pulse3=TCNT1;//count memory is updated to integer
		ult3_count =round(pulse3/58.3);
		TCNT1=0;//resetting the counter memory
		MCUCSR|= (1<<ISC2) ;
	}

}

int main(void)
{
	int bladeMotorSpeed;
	int ult1_distance;
	int ult2_distance;
	int ult3_distance;
	int rounds;
	int isMetal;
    /* Replace with your application code */
	initUltrasonic1();
	initUltrasonic2();
	initUltrasonic3();
    while (1) 
    {
		while (!(PIND & 1<<PD4 )); //Wait until pipe place
		
		if (PINB & 1<<PB5){//Change DC motor speed 
			//metal
			isMetal=1;
			bladeMotorSpeed=255;
		}else{
			//PVC
			isMetal=0;
			bladeMotorSpeed=100;
		}
		
		//USART send message TODO

		//tight clutches1&2
		
			//move both clutches forward until ultrasonic output zero
			//Check ultrasonic sensor output
			ult2_distance=getUltrasonic2Distance();
			ult3_distance=getUltrasonic3Distance();
			rotateStepper1(1,ult2_distance);
			rotateStepper2(1,ult3_distance);
			while(!(getUltrasonic2Distance()==3)&&!(getUltrasonic3Distance()==3));
					
			//move clutches through rail to align
			
			if((PIND & 1<<PD5) && (PIND && 1<<PD6)){//if both Ir sensor-2,3 are detected pipe
				rotateDCMotors(1);
				while(PIND && 1<<PD6);
				stopDCMotors();
			}else if(!(PIND & 1<<PD5) && !(PIND && 1<<PD6)){//else if both Ir sensor-2,3 are not detected pipe
				rotateDCMotors(0);
				while(!(PIND & 1<<PD5));
				stopDCMotors();
			}

			//wait for user keypad input
				//get user input
				//display input
				//ask for need quantity save that
				//ask for unit save that
				//calculate length
				//calculate rounds

			//repeat cutting process
			//loop rounds time
				for (int i=0;i<rounds;i++)
				{
					
				}
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
		if (!(PIND & 1<<PD4 )){
			//move both clutches backward though rail
			rotateDCMotors(0);
			while(getUltrasonic1Distance()==wasteBinDistance);
			stopDCMotors();
			//if metal
			//move clutch1 backward && clutch2 forward
			//else
			//move clutch2 backward && clutch1 forward
		}		
    }
}

