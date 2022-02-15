#include "../ECUAL/EEPROM/EEPROM_interface.h"
#include "../MCAL/I2C/I2C_interface.h"
#include "../MCAL/USART/UART_interface.h"
#include "../LIB/ATMEGA32_registers.h"
#include "../ECUAL/EEPROM/EEPROM_interface.h"
#include "../SERVICE/CARD_interface.h"
#include "../MCAL/TIMERS/TIMERS.h"
#include "../MCAL/DIO/DIO_interface.h"
#include <string.h>

volatile uint8_t u8_counts        = 0;
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	Ru8_PORTB ^= 0x01;
	u8_counts++;
}
int main(void)
{
	
	uint8_t u8_noChoice               = TRUE; 
	uint8_t u8_panNotValid            = TRUE;
	uint8_t u8_pinNotValid            = TRUE;
	uint8_t u8_noResponse             = TRUE;
	uint8_t u8_adminAccessed          = FALSE; 
	uint8_t u8_arrIndex               = u8_INTIAL_VAL;
	uint8_t u8_panSize                = u8_INTIAL_VAL;
	uint8_t u8_requestCode            = u8_INTIAL_VAL;
	uint8_t u8_statusCode             = u8_INTIAL_VAL;
	uint8_t u8_cardState              = u8_CARD_INTIAL_VAL; 
	uint8_t pu8_cardPIN[u8_PIN_SIZE];
	uint8_t pu8_command[10];
	uint8_t pu8_neededData[15];
	uint8_t pu8_cardHolderName[10];
	uint8_t pu8_cardPAN[u8_PAN_MAX_SIZE];
	Ru8_DDRB |= 0x01;
	CARD_init();
	
	cardMode_t u8_mode = ADMIN;

	while(1)
	{
		
		switch(u8_mode)
		{
			case ADMIN :
			TERMINAL_display(PROG_MODE_STR);
			CARD_voidCheckPanValidity(pu8_cardPAN, &u8_panSize);	
			EEPROM_u8WriteNeededPartBlock(u8_PAN_PAGE_NUM,u8_PAN_BYTE_NUM,pu8_cardPAN,u8_panSize);
			CARD_voidCheckPinValidity(pu8_cardPIN);
			EEPROM_u8WriteNeededPartBlock(u8_PIN_PAGE_NUM,u8_PIN_BYTE_NUM,pu8_cardPIN,u8_PIN_SIZE);
			u8_mode = USER;
			break;
			
			case USER :
			TERMINAL_display("USER MODE\r");
			EEPROM_u8ReadNeededPartBlock(u8_PAN_PAGE_NUM, u8_PAN_BYTE_NUM, pu8_cardPAN, u8_panSize);
			while(DIO_GetPinValue(PORTD,PIN3) != HIGH);
			SPI_masterTransmitString(pu8_cardPAN);
			TERMINAL_display("hi");
			//u8_statusCode = SPI_slaveReceiveByte();
			
			//if(u8_statusCode == u8_PAN_VALID)
			//{ 
				EEPROM_u8ReadNeededPartBlock(u8_PIN_PAGE_NUM, u8_PIN_BYTE_NUM, pu8_cardPIN, u8_PIN_SIZE);
			    while(DIO_GetPinValue(PORTD,PIN3) != HIGH);
				SPI_masterTransmitString(pu8_cardPIN);
				//u8_statusCode = SPI_slaveReceiveByte();
				
				//if(u8_statusCode == u8_PIN_VALID)
				//{
					//u8_statusCode = SPI_slaveReceiveByte();
					u8_counts = u8_INTIAL_VAL;
					u8_mode = CARD_u8ModeSelection();
				//}
				//else if(u8_statusCode == u8_PIN_INVALID)
				//{
					//u8_mode = CARD_u8ModeSelection();
				//}
				
			//}
			//else if (u8_statusCode == u8_PAN_INVALID)
			//{
				//u8_mode = CARD_u8ModeSelection();
			//}
			break;
		}
	}
}