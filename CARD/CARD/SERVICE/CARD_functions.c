#include "../LIB/STD_types.h"
#include "../MCAL/USART/UART_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "CARD_interface.h"


extern struct gstr_USART_Config_t gstr_USART_Config;

void CARD_init(void)
{
	Ru8_DDRD &= ~(0x04);
	Ru8_MCUCR |= 0x03;
	Ru8_SREG |= 0x80;
	Ru8_GICR |= 0x40; 
	
	SPI_init();
	TERMINAL_init();
	EEPROM_voidInit();
}

void TERMINAL_init(void)
{
	USART_voidInit(&gstr_USART_Config);
}

void TERMINAL_display(uint8_t* pu8_stream)
{
	if (pu8_stream != NULL_POINTER)
	{
		USART_voidSendString(pu8_stream);
	}
}

void TERMINAL_command(uint8_t* pu8_buffer, uint8_t u8_arrSize)
{
	USART_voidRecievePacket(pu8_buffer, u8_arrSize, '\r');
}

void CARD_voidCheckPanValidity(uint8_t* pu8_cardPAN, uint8_t* u8_panSize)
{
	uint8_t u8_arrIndex    = u8_INTIAL_VAL;
	TERMINAL_display(PAN_REQ_STR);
	TERMINAL_command(pu8_cardPAN, u8_PAN_MAX_SIZE);
	do
	{
		if((pu8_cardPAN[u8_arrIndex] >= '0') && (pu8_cardPAN[u8_arrIndex] <= '9'))
		{
			u8_arrIndex++;
		}
		else
		{
			TERMINAL_display(WRONG_PAN_STR);
			TERMINAL_display(PAN_REQ_STR);
			TERMINAL_command(pu8_cardPAN, u8_PAN_MAX_SIZE);
			u8_arrIndex = u8_INTIAL_VAL;
		}
		if(((pu8_cardPAN[u8_arrIndex] == NULL_CHAR)) && ((u8_arrIndex < u8_PAN_MIN_SIZE)))
		{
			TERMINAL_display(WRONG_PAN_STR);
			TERMINAL_display(PAN_REQ_STR);
			TERMINAL_command(pu8_cardPAN, u8_PAN_MAX_SIZE);
			u8_arrIndex = u8_INTIAL_VAL;
		}
	}while((pu8_cardPAN[u8_arrIndex] != NULL_CHAR));
	
	*(u8_panSize) = u8_arrIndex;
}

void CARD_voidCheckPinValidity(uint8_t* pu8_cardPIN)
{
	uint8_t u8_arrIndex    = u8_INTIAL_VAL;
	TERMINAL_display(PIN_REQ_STR);
	TERMINAL_command(pu8_cardPIN,u8_PIN_SIZE);
	
	do
	{
		if((pu8_cardPIN[u8_arrIndex] >= '0') && (pu8_cardPIN[u8_arrIndex] <= '9'))
		{
			u8_arrIndex++ ;
		}
		else
		{
			TERMINAL_display(WRONG_PIN_STR);
			TERMINAL_display(PIN_REQ_STR);
			TERMINAL_command(pu8_cardPIN,u8_PIN_SIZE);
			u8_arrIndex = u8_INTIAL_VAL;
		}
		if(((pu8_cardPIN[u8_arrIndex] == NULL_CHAR)) && ((u8_arrIndex != (u8_PIN_SIZE-1))))
		{
			TERMINAL_display(WRONG_PIN_STR);
			TERMINAL_display(PIN_REQ_STR);
			TERMINAL_command(pu8_cardPIN,u8_PIN_SIZE);
			u8_arrIndex = u8_INTIAL_VAL;
		}
	}while((pu8_cardPIN[u8_arrIndex] != NULL_CHAR));
}

uint8_t CARD_u8ModeSelection(void)
{
	uint8_t u8_noChoice = TRUE;
	uint8_t u8_choice   = u8_INTIAL_VAL;
	uint8_t u8_mode     = u8_INTIAL_VAL;
	
	TERMINAL_display("Choose mode\r");
	TERMINAL_display("1- Programming mode\r");
	TERMINAL_display("2- User mode\r");
	
	while(u8_noChoice)
	{
		TERMINAL_display("Choice: ");
		u8_choice = USART_u8Receive();
		
		if(u8_choice == PROGRAMMING_MODE)
		{
			u8_noChoice = FALSE;
			u8_mode = ADMIN;
		}
		else if (u8_choice == USER_MODE)
		{
			u8_noChoice = FALSE;
			u8_mode = USER;
		}
		else
		{
			TERMINAL_display("WRONG CHOICE!!!\r");
		}
	}
	return u8_mode;
}