/*
 * GccApplication1.c
 *
 * Created: 5/15/2022 11:32:38 AM
 * Author : user
 */ 

#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>

#define LCD PORTB
#define EN 7
#define RW 6
#define RS 5
unsigned char keypad();
unsigned char x;
unsigned char y;
int x1=0 ; // variable for length of the pipe
int x2=0; // variable for quantity
int8_t receivedData;
int isInputDataRecevied;
int bladeMotorSpeed=0; 

void lcdcmd(unsigned char cmd) 
{
	PORTC&=~(1<<RS);
	PORTC&=~(1<<RW);
	LCD=cmd & 0xF0;
	PORTD|=(1<<EN);
	_delay_ms(20);
	PORTD&=~(1<<EN);
	
	LCD=cmd<<4;
	PORTD|=(1<<EN);
	_delay_ms(20);
	PORTD&=~(1<<EN);
}

void lcddata(unsigned char data)//function to display input data
{
	PORTC|=(1<<RS);
	PORTC&=~(1<<RW);
	LCD=data & 0xF0;
	PORTD|=(1<<EN);
	_delay_ms(20);
	PORTD&=~(1<<EN);
	
	LCD=data << 4;
	PORTD|=(1<<EN);
	_delay_ms(20);
	PORTD&=~(1<<EN);
}

void lcd_init()//function to LCD initialization
{
	DDRC=0xFF;
	DDRD=0xFF;
	PORTD&=~(1<<EN);
	lcdcmd(0x33);
	lcdcmd(0x32);
	lcdcmd(0x28);
	lcdcmd(0x0E);
	lcdcmd(0x01);
	_delay_ms(20);
}
void lcd_print(char *str)//function to print a given string
{
	unsigned char i=0;
	while(str[i]!=0)
	{
		lcddata(str[i]);
		i++;
	}
}

// to check whether a key is pressed and return that value
unsigned char keypad()
{
	PORTA=0b11111110;//check first row
	if((PINA &(1<<PINA4))==0)
	{
		_delay_ms(3);
		return '7';
	}
	else if((PINA & (1<<PINA5))==0)
	{
		_delay_ms(3);
		return '8';
	}
	else if((PINA & (1<<PINA6))==0)
	{
		_delay_ms(3);
		return '9';
	}
	else if((PINA & (1<<PINA7))==0)
	{
		_delay_ms(3);
		return '/';
	}
	
	PORTA=0b11111101;//check second row
	if((PINA &(1<<PINA4))==0)
	{
		_delay_ms(3);
		return '4';
	}
	else if((PINA & (1<<PINA5))==0)
	{
		_delay_ms(3);
		return '5';
	}
	else if((PINA & (1<<PINA6))==0)
	{
		_delay_ms(3);
		return '6';
	}
	else if((PINA & (1<<PINA7))==0)
	{
		_delay_ms(3);
		return '*';
	}
	
	PORTA=0b11111011;//check third row
	if((PINA &(1<<PINA4))==0)
	{
		_delay_ms(3);
		return '1';
	}
	else if((PINA & (1<<PINA5))==0)
	{
		_delay_ms(3);
		return '2';
	}
	else if((PINA & (1<<PINA6))==0)
	{
		_delay_ms(3);
		return '3';
	}
	else if((PINA & (1<<PINA7))==0)
	{
		_delay_ms(3);
		return '-';
	}
	
	PORTA=0b11110111;//check fourth row
	if((PINA &(1<<PINA4))==0)
	{
		_delay_ms(3);
		return 'C';
	}
	else if((PINA & (1<<PINA5))==0)
	{
		_delay_ms(3);
		return '0';
	}
	else if((PINA & (1<<PINA6))==0)
	{
		_delay_ms(3);
		return 'E';
	}
	else if((PINA & (1<<PINA7))==0)
	{
		_delay_ms(3);
		return '.';
	}
}

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

void initDCMotor(){
	DDRB = 0xFF;	DDRB |= (1 << PB3);	TCCR0  = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00);	OCR0 = bladeMotorSpeed;
}


void sendData(uint8_t byte){
	while (! (UCSRA & (1 << UDRE)) );

	{
		UDR = byte;//once transmitter is ready sent eight bit data
	}
	// Get that data out here!
	_delay_ms(5);
}

void rotateMotor(){
	PORTB |=(1<<PB1);
}
void stopMotor(){
	PORTB &=~(1<<PB1);
}


ISR(USART_RXC_vect){
	receivedData=UDR;
	if(receivedData=="START"){
		rotateMotor();
	}else if("STOP"){
		stopMotor();
	}else if("HIGH"){
		bladeMotorSpeed = 255;
	}else if("LOW"){
		bladeMotorSpeed = 100;
	}
	
	isInputDataRecevied=1;
}

int main(void)
{
	DDRA=0x0F;
	lcd_init();
	initUSART();
	sei();
	lcd_print("  HELLO USER ");
	_delay_ms(100);
	label1:
	lcdcmd(0x01);//clear display
	lcdcmd(0x0E);//blink the cursor
	_delay_ms(100);
	lcd_print("ENTER LENGTH");
	lcdcmd(0xC0);//bring cursor to second row
	
    do
    {
	    PORTA=0xF0;
	    if(PINA!=0xF0)
	    {
		    x=keypad();
			if(x=='/'||x=='*'||x=='-'||x=='C')
			{
				lcdcmd(0x01);
				lcdcmd(0x0E);
				_delay_ms(100);
				lcd_print("INVALID INPUT");
				_delay_ms(100);
				goto label1;
			}
				
			else if(x!='E')//read the input length x1
		    {
			    x1=(x1*10)+(x-'0');        
			    lcddata(x);
		    }
		}
		
    }while(x!='E');
	
	label2:
	lcdcmd(0x01);
	lcdcmd(0x0E);
	_delay_ms(100);
	lcd_print("ENTER QUANTITY :");
	_delay_ms(100);
	lcdcmd(0xC0);
	
	 do
	 {
		 PORTA=0xF0;
		 if(PINA!=0xF0)
		 {
			 y=keypad();
			 if(y=='/'||y=='*'||y=='-')
			 {
				 lcdcmd(0x01);
				 lcdcmd(0x0E);
				 _delay_ms(100);
				 lcd_print("INVALID INPUT");
				 _delay_ms(100);
				 goto label2;
			 }
			 else if(y!='E')//read the input quantity x2
			 {
				 x2=y-'0';
				 lcddata(y);
			 }
		 }
	 }while(y!='E');
	 
	if(y=='E')//completion of inserting relevant inputs
	{
		//send length
		sendData(x1);
		// wait
		_delay_ms(100);
		//send quantity
		sendData(x2);
		
		lcdcmd(0x01);
		lcdcmd(0x0E);
		_delay_ms(100);
		lcd_print("     Done");
		_delay_ms(100);
		lcdcmd(0x01);
		_delay_ms(500);
	}

	return 0;
}










