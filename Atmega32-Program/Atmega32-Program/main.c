/*
   4x4 Keypad Interfacing with ATmega16/32
   http://www.electronicwings.com
 */ 
#include <avr/io.h>
#include <util/delay.h>


#define KEY_PRT 	PORTA
#define KEY_DDR		DDRA
#define KEY_PIN		PINA

void LCD_Command(unsigned char cmnd)
{
	LCD_DPRT = (LCD_DPRT & 0x0f)|(cmnd & 0xf0);		/* SEND COMMAND TO DATA PORT */
	LCD_DPRT &= ~ (1<<LCD_RS);						/* RS = 0 FOR COMMAND */
	LCD_DPRT |= (1<<LCD_EN);						/* EN = 1 FOR H TO L PULSE */
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE */
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE */
	_delay_us(100);									/* WAIT FOR MAKE ENABLE WIDE */
	
	LCD_DPRT = (LCD_DPRT & 0x0f)|(cmnd << 4);		/* SEND COMMAND TO DATA PORT */
	LCD_DPRT |= (1<<LCD_EN);						/* EN = 1 FOR H TO L PULSE */
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE */
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE */
	_delay_us(2000);								/* WAIT FOR MAKE ENABLE WIDE */
}

void LCD_Char(unsigned char data)
{
	LCD_DPRT = (LCD_DPRT & 0x0f)|(data & 0xf0);		/* SEND DATA TO DATA PORT */
	LCD_DPRT |= (1<<LCD_RS);						/* MAKE RS = 1 FOR DATA */
	LCD_DPRT |= (1<<LCD_EN);						/* EN=0 FOR H TO L PULSE */
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE */
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE */
	_delay_us(100);									/* WAIT FOR MAKE ENABLE WIDE */
	
	LCD_DPRT = (LCD_DPRT & 0x0f)|(data << 4);		/*  */
	LCD_DPRT |= (1<<LCD_EN);						/* EN=0 FOR H TO L PULSE*/
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE*/
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE*/
	_delay_us(2000);								/* WAIT FOR MAKE ENABLE WIDE*/
}

void LCD_Init()
{
	LCD_DDDR = 0xFF;
	_delay_ms(20);									/* WAIT FOR SOME TIME */
	LCD_Command(0x02);								/* SEND $32 FOR INIT OT 0X02 */
	LCD_Command(0x28);								/* INIT. LCD 2 LINE, 5 X 7 MATRIX */
	LCD_Command(0x0C);								/* DISPLAY ON CURSOR ON */
	LCD_Command(0x01);								/* LCD CLEAR */
	LCD_Command(0x82);								/* SHIFT CURSOR TO WRITE */
}

void LCD_String_xy(unsigned char row, unsigned char pos, char *str)
{
	if (row == 1)
	LCD_Command((pos & 0x0F)|0x80);				/* Command of first row and required position<16 */
	else if (row == 2)
	LCD_Command((pos & 0x0F)|0xC0);				/* Command of Second row and required position<16 */
	
	LCD_String(str);								/* Call LCD string function */
}

void LCD_String(char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)							/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);							/* Call LCD data write */
	}
}

void lcd_clear()
{
	LCD_Command(0x01);
	_delay_ms(3);
	LCD_Command(0x80);
}

unsigned char keypad[4][4] = {	{'7','8','9','/'},
								{'4','5','6','*'},
								{'1','2','3','-'},
								{' ','0','=','+'}};

unsigned char colloc, rowloc;


char keyfind()
{
	while(1)
	{
		KEY_DDR = 0xF0;                /* set port direction as input-output */
		KEY_PRT = 0xFF;

		do
		{
			KEY_PRT &= 0x0F;           /* mask PORT for column read only */
			asm("NOP");
			colloc = (KEY_PIN & 0x0F); /* read status of column */
		}while(colloc != 0x0F);
		
		do
		{
			do
			{
				_delay_ms(20);			   /* 20ms key debounce time */
				colloc = (KEY_PIN & 0x0F); /* read status of column */
			}while(colloc == 0x0F);        /* check for any key press */
			
			_delay_ms (40);				   /* 20 ms key debounce time */
			colloc = (KEY_PIN & 0x0F);
		}while(colloc == 0x0F);

	/* now check for rows */
		KEY_PRT = 0xEF;            /* check for pressed key in 1st row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 0;
			break;
		}

		KEY_PRT = 0xDF;			  /* check for pressed key in 2nd row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 1;
			break;
		}
		
		KEY_PRT = 0xBF;			  /* check for pressed key in 3rd row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 2;
			break;
		}

		KEY_PRT = 0x7F;			  /* check for pressed key in 4th row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 3;
			break;
		}
	}

	if(colloc == 0x0E)
		return(keypad[rowloc][0]);
	else if(colloc == 0x0D)
		return(keypad[rowloc][1]);
	else if(colloc == 0x0B)
		return(keypad[rowloc][2]);
	else
		return(keypad[rowloc][3]);
}

int main(void)
{
	LCD_Init();
	LCD_String_xy(1,0,"Press a key");
    while(1)
	{
		LCD_Command(0xc0);
		LCD_Char(keyfind());             /* Display which key is pressed */
	}
}