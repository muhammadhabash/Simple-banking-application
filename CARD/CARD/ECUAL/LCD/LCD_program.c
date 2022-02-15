#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMERS/TIMERS.h"
#include "LCD.h"

void LCD_init()
{
	TIMER0_msdelay(100);
	/*******************************************************/
	/* Configuring LCD Control and Data pins to be outputs */
	/*******************************************************/
	DIO_SetPinDirection(PORTA,RS,OUTPUT);
	DIO_SetPinDirection(PORTA,RW,OUTPUT);
	DIO_SetPinDirection(PORTA,EN,OUTPUT);
	DIO_SetPinDirection(PORTA,D4,OUTPUT);
	DIO_SetPinDirection(PORTA,D5,OUTPUT);
	DIO_SetPinDirection(PORTA,D6,OUTPUT);
	DIO_SetPinDirection(PORTA,D7,OUTPUT);
	//TIMER0_msdelay(100);
	
	/********************/
	/* Initial Commands */
	/********************/    
	LCD_command(0x3);
	TIMER0_msdelay(10);
	LCD_command(0x3);
	TIMER0_msdelay(10);
	LCD_command(0x3);
	TIMER0_msdelay(10);
	LCD_command(0x2);
	TIMER0_msdelay(10);
	LCD_command(0x28);
	TIMER0_msdelay(10);
	LCD_command(0x08);
	TIMER0_msdelay(10);
	LCD_command(0x01);
	TIMER0_msdelay(10);
	LCD_command(0x06);
	TIMER0_msdelay(10);
	LCD_command(0x0C);
	TIMER0_msdelay(10);                                    
}

void LCD_command(uint8_t u8_command)
{	
	/**************************************************************/
	/* Since we are using 4-bit mode, we are only allowed         */
	/* to send 4 bits of data at a time. Therefore, we will       */
	/* partition the 8 bit data into 2 partitions; Higher nipple  */
	/* and Lower nipple and then send each of them respectively   */
	/**************************************************************/ 
	
	/*************************/
	/* Sending higher nipple */
	/*************************/
	DATA_REGISTER =  (DATA_REGISTER & (0x0F)) |  (u8_command & (0xF0));
	DIO_SetPinValue(PORTA,RS,LOW);
	DIO_SetPinValue(PORTA,EN,HIGH);
	TIMER0_msdelay(10);
	DIO_SetPinValue(PORTA,EN,LOW);
	TIMER0_msdelay(10);
	
	/************************/
	/* Sending lower nipple */
	/************************/
	DATA_REGISTER = (DATA_REGISTER & (0x0F)) |  (u8_command << 4);
	DIO_SetPinValue(PORTA,EN,HIGH);  /**********************************************************/
	TIMER0_msdelay(10);              /*  Here we set EN pin to high when reading               */
	DIO_SetPinValue(PORTA,EN,LOW);   /*  and then set it low to latch the input data.          */
	TIMER0_msdelay(10);              /*  Delays are used to give the LCD needed processing time*/     
}                                    /**********************************************************/

void LCD_data(uint8_t u8_data)
{	
	/*************************/
	/* Sending higher nipple */
	/*************************/
	DATA_REGISTER = (DATA_REGISTER & (0x0F)) |  (u8_data & (0xF0));
	DIO_SetPinValue(PORTA,RS,HIGH);
	DIO_SetPinValue(PORTA,EN,HIGH);
	TIMER0_msdelay(10);
	DIO_SetPinValue(PORTA,EN,LOW);
	TIMER0_msdelay(10);
	
	/************************/
	/* Sending lower nipple */
	/************************/
	DATA_REGISTER = (DATA_REGISTER & (0x0F)) |  (u8_data << 4);
	DIO_SetPinValue(PORTA,EN,HIGH);
	TIMER0_msdelay(10);
	DIO_SetPinValue(PORTA,EN,LOW);
	TIMER0_msdelay(10); 
}

void LCD_printString(uint8_t* stream)
{
	uint8_t u8_index;
	
	for (u8_index = 0 ; stream[u8_index] != 0 ; u8_index++)
	{
		LCD_data(stream[u8_index]);
	}
}

void LCD_printDigits(uint32_t u32_number)
{	volatile uint8_t  u8_temp;
	volatile uint8_t  u8_weight;
	volatile uint8_t  u8_data;
	volatile uint8_t  u8_digits;
	volatile float    f32_temp;
	
	u8_weight = log10(u32_number);
	u8_digits = (u8_weight + 1);
	u8_temp   = (u32_number / pow(10,u8_weight));
	f32_temp  = ((u32_number*1.0) / pow(10,u8_weight));
	do
	{
		u8_data  = (u8_temp | (3 << 4));
		LCD_data(u8_data);
		u8_digits--;
		f32_temp = f32_temp - u8_temp;
		u8_temp  = (f32_temp * 10);
		f32_temp = (f32_temp *(10*1.0));
	} while (u8_digits);
}

void LCD_cursorMove(uint8_t u8_direction, uint8_t u8_numOfMoves){
uint8_t u8_counterMoveCursor = u8_LCD_INTIAL_VAL ;
for(u8_counterMoveCursor = u8_LCD_INTIAL_VAL ;u8_counterMoveCursor<=u8_numOfMoves;u8_counterMoveCursor++)
{
	if(LEFT == u8_direction){
		LCD_command(LEFT);
		TIMER0_msdelay(5);
	}
	else if(RIGHT == u8_direction){
		LCD_command(RIGHT);
		TIMER0_msdelay(5);
	}
}
}

void LCD_newLine(void)
{
	LCD_command(0xC0);
}
