/*
 * pipe-cutting-machine.c
 *
 * Created: 5/8/2022 6:59:49 PM
 * Author : Dasith Rathnasinghe
 * Atmega32-1
 */
//TODO casting
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <math.h>
#include <stdio.h>

static volatile int pulse1 = 0; // integer  to access all though the program
static volatile int i = 0;
static volatile int pulse2 = 0; // integer  to access all though the program
static volatile int j = 0;
static volatile int pulse3 = 0; // integer  to access all though the program
int ult1_count = NULL;
int ult2_count = NULL;
int ult3_count = NULL;
int wasteBinDistance1 = 20;
int wasteBinDistance2 = 10;
int minLen=4;
int maxRadius=25;
char* receivedData;
int isInputDataRecevied;

void initUSART(){
	
	DDRD |= 1 << PIND1;//pin1 of portD as OUTPUT

	DDRD &= ~(1 << PIND0);//pin0 of portD as INPUT
	
	int UBBRValue = 25;//AS described before setting baud rate

	//Put the upper part of the baud number here (bits 8 to 11)

	UBRRH = (unsigned char) (UBBRValue >> 8);

	//Put the remaining part of the baud number here

	UBRRL = (unsigned char) UBBRValue;

	//Enable the receiver, transmitter and receiver interrupt
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);

	//Set 2 stop bits and data bit length is 8-bit

	UCSRC = (1 << USBS) | (3 << UCSZ0);
	
}

void sendData(uint8_t byte){
	while (! (UCSRA & (1 << UDRE)) );

	{
		UDR = byte;//once transmitter is ready sent eight bit data
	}
	// Get that data out here!
	_delay_ms(5);
}

void rotateDCMotors(int direction)
{
	if (direction != 0)
	{
		// Rotate DC motor Clockwise ?
		PORTC &= ~(1 << PB0);
		PORTC |= (1 << PB1);
	}
	else
	{
		// Else rotate DC motor Counterclockwise
		PORTC |= (1 << PB0);
		PORTC &= ~(1 << PB1);
	}
}

void stopDCMotors()
{
	// stop Rotation DC motor
	PORTC &= ~(1 << PB0);
	PORTC &= ~(1 << PB1);
}

void rotateStepper1(int direction, float distance)
{
	// clockwise-1
	// Counterclockwise-0
	// 1 distance unit = 1 rotating

	int period;
	DDRA = 0xF;
	period = 10;
	if (direction == 1)
	{
		for (int i = 0; i < round(distance); i++)
		{
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
	}
	else
	{
		for (int i = 0; i < round(distance); i++)
		{
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

void rotateStepper2(int direction, float distance){
	// clockwise-1
	// Counterclockwise-0
	// 1 distance unit = 1 rotating

	int period;
	DDRA = 0xf0;
	period = 10;
	if (direction == 1)
	{
		/* Rotate  clockwise */
		for (int i = 0; i < 50; i++)
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
	}
	else
	{
		/* Rotate  Counterclockwise  */
		for (int i = 0; i < 50; i++)
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

void rotateStepper3(int direction, float distance){
	// clockwise-1
	// Counterclockwise-0
	// 1 distance unit = 1 rotating

	int period;
	DDRC = 0x0F;
	period = 10;
	if (direction == 1)
	{
		/* Rotate  clockwise */
		for (int i = 0; i < 50; i++)
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
	}
	else
	{
		/* Rotate  Counterclockwise  */
		for (int i = 0; i < 50; i++)
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

void rotateStepper4(int direction){
	// clockwise-1
	// Counterclockwise-0
	// 1 distance unit = 1 rotating

	int period;
	DDRC = 0xF0;
	period = 10;
	if (direction == 1)
	{
		/* Rotate  clockwise */
		for (int i = 0; i < 15; i++) // 108 degree cutting arm
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
	}
	else
	{
		/* Rotate  Counterclockwise  */
		for (int i = 0; i < 15; i++)
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

void initUltrasonic1()
{
	DDRD |= 1 << PIND7;	 // set PD7 output
	DDRD &= ~(1 << PD2); // set PD2 Input
	GICR |= (1 << INT0); // enabling interupt 0
	// General Interrupt Control Register
	MCUCR |= (1 << ISC00); // setting interrupt triggering logic change
	// MCU control Register
	TCCR1A = 0;
}

int getUltrasonic1Distance()
{
	int temp;
	PORTD |= (1 << PIND7);
	_delay_us(15); // triggering the sensor for 15usec
	PORTD &= (~(1 << PIND7));

	while (ult1_count == NULL)
		;
	temp = ult1_count;
	ult1_count = NULL;
	return temp;
}



void initUltrasonic2()
{
	DDRB |= 1 << PB6;	 // set PB6 output
	DDRB &= ~(1 << PB3); // set PB3 Input
	GICR |= (1 << INT1); // enabling interupt 1
	// General Interrupt Control Register
	MCUCR |= (1 << ISC10); // setting interrupt triggering logic change
	// MCU control Register
	TCCR1A = 0;
}

int getUltrasonic2Distance()
{
	int temp;

	PORTB |= (1 << PB6);
	_delay_us(15); // triggering the sensor for 15usec
	PORTB &= (~(1 << PB6));

	while (ult2_count == NULL)
		;
	temp = ult2_count;
	ult2_count = NULL;
	return temp;
}

void initUltrasonic3()
{
	DDRB |= 1 << PB7;	 // set PB7 output
	DDRB &= ~(1 << PB2); // set PB2 Input
	GICR |= (1 << INT2); // enabling interupt 2
	// General Interrupt Control Register
	MCUCSR |= (1 << ISC2); // setting interrupt triggering logic LOW to HIGH
	// MCU control Register
	TCCR1A = 0;
}

int getUltrasonic3Distance()
{
	int temp;

	PORTB |= (1 << PB7);
	_delay_us(15); // triggering the sensor for 15usec
	PORTB &= (~(1 << PB7));

	while (ult3_count == NULL)
		;
	temp = ult3_count;
	ult3_count = NULL;
	return temp;
}

ISR(INT0_vect) // interrupt service routine when there is a change in logic level
{

	if (i == 0)
	{ // when logic change from LOW to HIGH

		TCCR1B |= (1 << CS10); // enabling counter

		i = 1;
	}
	if (i == 1)
	{
		TCCR1B = 0; // disabling counter

		pulse1 = TCNT1; // count memory is updated to intege

		TCNT1 = 0; // resetting the counter memory
		ult1_count = (pulse1 / 58) + 1;
		i = 0;
	}
}

ISR(INT1_vect) // interrupt service routine when there is a change in logic level
{

	if (j == 0)
	{ // when logic change from LOW to HIGH

		TCCR1B |= (1 << CS10); // enabling counter

		i = 1;
	}
	if (j == 1)
	{
		TCCR1B = 0; // disabling counter

		pulse2 = TCNT1; // count memory is updated to intege

		TCNT1 = 0; // resetting the counter memory
		ult2_count = (pulse2 / 58) + 1;
		j = 0;
	}
}

ISR(INT2_vect) // interrupt service routine when there is a change in logic level
{

	if ((MCUCSR & (1 << ISC2)))
	{ // when logic change from LOW to HIGH

		TCCR1B |= (1 << CS10);	// enabling counter
		MCUCSR &= ~(1 << ISC2); // HIGH to LOW
	}
	else
	{ // when logic from HIGH to LOW

		TCCR1B = 0; // disabling counter

		pulse3 = TCNT1; // count memory is updated to integer
		ult3_count = round(pulse3 / 58.3);
		TCNT1 = 0; // resetting the counter memory
		MCUCSR |= (1 << ISC2);
	}
}

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
	/* Replace with your application code */
	initUltrasonic1();
	initUltrasonic2();
	initUltrasonic3();
	initUSART();
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
		ult2_distance = getUltrasonic2Distance();
		ult3_distance = getUltrasonic3Distance();
		// move both clutches forward until ultrasonic output smallest number
		rotateStepper1(1, ult2_distance);
		rotateStepper2(1, ult3_distance);
		while ((getUltrasonic2Distance() >= 3) && (getUltrasonic3Distance() >= 3));

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
			rotateStepper1(0,maxRadius);
			rotateStepper2(0,maxRadius);
			while ((getUltrasonic2Distance() < maxRadius) && (getUltrasonic3Distance() < maxRadius));
			// move pipe forward according to the calculated length
			rotateDCMotors(0);
			while(getUltrasonic1Distance()>3);
			// Check ultrasonic sensor output
			ult2_distance = getUltrasonic2Distance();
			ult3_distance = getUltrasonic3Distance();
			//rotate stepper motor2 and 1 forward
			rotateStepper1(1, ult2_distance);
			rotateStepper2(1, ult3_distance);

			// get ultrasonic1 output distance (distance1)
			ult1_distance=getUltrasonic1Distance();
			// move clutches though rail until ult1_distance-instantDistance==length
			rotateDCMotors(1);
			while((getUltrasonic1Distance()-ult1_distance)<length)
			stopDCMotors();
			// rotate stepper motor3 forward
			rotateStepper3(1,maxRadius);			
			// pipe cutting process
			// start rotating cutting blade DC motor
			sendData("START");
			// rotate stepper motor4
			rotateStepper4(1);
			rotateStepper4(0);
			rotateStepper3(0,maxRadius);
		}

		// check if leftover pipe is waste or not
		if (!(PIND & 1 << PD4)){
			// move both clutches backward though rail
			rotateDCMotors(0);
			while (getUltrasonic1Distance() == wasteBinDistance1)
				;
			stopDCMotors();
			if (isMetal){
				// move clutch1 backward && clutch2 forward
				rotateStepper1(0,wasteBinDistance2);
				rotateStepper2(1,wasteBinDistance2);
				// when position correctly, drop wastage
				rotateStepper2(0,wasteBinDistance2);
				_delay_ms(100);
				rotateStepper1(1,wasteBinDistance2);
			}else{
				// move clutch2 backward && clutch1 forward
				rotateStepper1(1,wasteBinDistance2);
				rotateStepper2(0,wasteBinDistance2);
				// when position correctly, drop wastage
				rotateStepper1(0,wasteBinDistance2);
				_delay_ms(100);
				rotateStepper2(1,wasteBinDistance2);
			}
		}
	}
}
