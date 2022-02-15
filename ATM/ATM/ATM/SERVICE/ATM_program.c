#include "../LIB/STD_types.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "../MCAL/TIMERS/TIMERS.h"
#include "../ECUAL/LM35/LM35_interface.h"
#include "../ECUAL/LCD/LCD.h"
#include "../ECUAL/KEYPAD/KEYPAD_interface.h"
#include "../ECUAL/MOTOR/MOTOR.h"
#include "../ECUAL/EEPROM/EEPROM_interface.h"
#include "../MCAL/USART/UART_interface.h"
#include "ATM_interface.h"
#include "../ECUAL/BUZZER/BUZZER.h"
#include <string.h>

extern struct gstr_USART_Config_t gstr_USART_Config;


void ATM_Init(void)
{
	Ru8_DDRD |= 0x80;
	EEPROM_voidInit();
	LM35_voidInit();
	Keyad_VoidINit();
	LCD_init();
	TERMINAL_init();
	BUZZER_en();
	SPI_init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void TERMINAL_init(void)
{
	USART_voidInit(&gstr_USART_Config);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void TERMINAL_display(uint8_t* u8_stream)
{
	if (u8_stream != NULL_POINTER)
	{
		USART_voidSendString(u8_stream);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void TERMINAL_command(uint8_t* u8_buffer, uint8_t u8_arrSize)
{
	USART_voidRecievePacket(u8_buffer, u8_arrSize, '\r');
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t ACCESS_grant(void)
{
	uint8_t u8_passCorrect = ATM_FALSE;
	uint8_t u8_trials      = u8_INTIAL_VAL;
	uint8_t pu8_adminPass[u8_ADMIN_PASS_SIZE];
	
	while(!u8_passCorrect && (u8_trials < u8_MAX_TRIALS))
	{
		u8_trials++;
		TERMINAL_display(REQUIRE_PASS_STR);
		TERMINAL_command(pu8_adminPass,u8_ADMIN_PASS_SIZE);
		
		if(strcmp(pu8_adminPass,ADMIN_PASS) == u8_EQUAL_STR)
		{
			u8_passCorrect = ATM_TRUE;
		}
		else
		{
			TERMINAL_display(WRONG_PASS_STR);
		}
	}
	return u8_passCorrect;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t TERMINAL_u8getInput(uint8_t* pu8_inputBuff, uint8_t u8_maxBuffSize, uint8_t u8_minBuffSize)
{
	uint8_t u8_indexArr = u8_INTIAL_VAL ;
	uint8_t u8_inputValid = ATM_TRUE;
	TERMINAL_command(pu8_inputBuff, u8_maxBuffSize);
	
	do
	{
		if((pu8_inputBuff[u8_indexArr] >= '0') && (pu8_inputBuff[u8_indexArr] <= '9'))
		{
			u8_indexArr++;
		}
		else
		{
			u8_inputValid = ATM_FALSE;
			break;
		}
		if((pu8_inputBuff[u8_indexArr] == NULL_CHAR) && (u8_indexArr < u8_minBuffSize))
		{
			TERMINAL_command(pu8_inputBuff, u8_maxBuffSize);
			u8_indexArr = u8_INTIAL_VAL;
		}
	}while(pu8_inputBuff[u8_indexArr] != NULL_CHAR);
	return u8_inputValid ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t ATM_u8getArrCount(uint8_t* pu8_inputBuff)
{
	uint8_t u8_indexArr = u8_INTIAL_VAL ;
	while(pu8_inputBuff[u8_indexArr] != NULL_CHAR)
	{
		++u8_indexArr ;
	}
	return u8_indexArr ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void ATM_voidstoreBalance(uint8_t* pu8_newRecBal,uint8_t* pu8_tempRecBal,uint8_t u8_digitsCount)
{
	uint8_t u8_indexArr = u8_INTIAL_VAL;
	uint8_t u8_indexArr2 = u8_INTIAL_VAL ;
	uint8_t u8_startingIndex = u8_BALANCE_MAX_SIZE - (u8_digitsCount + 1);
	while(u8_indexArr < u8_BALANCE_MAX_SIZE)
	{
		if(u8_indexArr < u8_startingIndex)
		{
			pu8_newRecBal[u8_indexArr] = '0';
		}
		else
		{
			pu8_newRecBal[u8_indexArr] = pu8_tempRecBal[u8_indexArr2];
			u8_indexArr2++;
		}
		u8_indexArr++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void ATM_voidlcdUserInterface(void)
{
	LCD_command(DISPLAY_CLEAR);
	LCD_printString(LCD_INSERT_CARD_STR);
	LCD_newLine();
	LCD_printString(LCD_SHOW_TEMP_OPTION_STR);
	LCD_cursorMove(RIGHT, 2);
	LCD_printString(LCD_EXIT_OPTION_STR);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

//function take wanted PAN to get and pointer to the PAN if found and return ATM_TRUE if PAN found and false otherwise
uint8_t ATM_panValidity(uint8_t* pu8_panWantedBuffer,uint16_t* pu16_wantedPanRecordnum)
{
	uint8_t u8_PANstate = ATM_FALSE  ;
	uint16_t u16_recordNum = u8_INTIAL_VAL ;
	uint16_t u16_RecCount  = u8_INTIAL_VAL ;
	uint8_t pu8_atmServerPAN[u8_PAN_MAX_SIZE] ;
	
	u16_recordNum = ATM_u16GetRecNum();
	while(u16_RecCount <= u16_recordNum)
	{
		EEPROM_u8ReadNeededPartBlock(u16_RecCount,u8_PAN_BYTE_NUM,pu8_atmServerPAN,u8_PAN_MAX_SIZE) ;

		if(strcmp(pu8_atmServerPAN,pu8_panWantedBuffer) == u8_EQUAL_STR)
		{
			u8_PANstate = ATM_TRUE;
			*pu16_wantedPanRecordnum = u16_RecCount ;
			break;
		}
		u16_RecCount++ ;
	}

	return u8_PANstate ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t ATM_u8PinAccessGrant(uint8_t* pu8_cardPin)
{
	uint8_t u8_pinValidity = ATM_TRUE ;
	uint8_t u8_indexArr = u8_INTIAL_VAL;
	uint8_t u8_keyPadReturnASCII = u8_KEYPAD_NOT_PRESSED ;
	uint8_t u8_countWrongEnteredTimes = u8_INTIAL_VAL ;
	uint8_t pu8_atmPinBuffer[u8_PIN_SIZE] ;
	while((pu8_cardPin[u8_indexArr] != NULL_CHAR) && (u8_countWrongEnteredTimes < u8_MAX_ENTERED_PIN_TIMES))
	{
		u8_keyPadReturnASCII = KeyPad_U8Data();
		if(u8_keyPadReturnASCII!= u8_KEYPAD_NOT_PRESSED)
		{
			if(u8_keyPadReturnASCII<='9' && u8_keyPadReturnASCII>='0')
			{
				LCD_data('*') ;
				pu8_atmPinBuffer[u8_indexArr] = u8_keyPadReturnASCII ;
				if(pu8_atmPinBuffer[u8_indexArr] !=  pu8_cardPin[u8_indexArr])
				{
					u8_pinValidity = ATM_FALSE ;
				}
				u8_indexArr++ ;
			}
			else
			{
				u8_pinValidity = ATM_FALSE ;
			}

			if(u8_pinValidity== ATM_FALSE && u8_indexArr == (u8_PIN_SIZE - 1)) 
			{
				u8_pinValidity = ATM_TRUE ;
				LCD_command(DISPLAY_CLEAR) ;
				LCD_printString(LCD_WRONG_PIN_STR);
				TIMER0_msdelay(1000) ;
				LCD_command(DISPLAY_CLEAR) ;
				LCD_printString(LCD_REQUIRE_PIN_STR);
				LCD_newLine();
				u8_indexArr = u8_INTIAL_VAL ;
				u8_countWrongEnteredTimes++ ;
			}

		}

	}
	return u8_pinValidity ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t ATM_u8checkBalanceValidity(uint8_t* pu8_userInputBal)
{
	uint8_t u8_balanceValidity = u8_BALANCE_VALID ;
	uint8_t pu8_atmMaxBal[u8_MAX_BALANCE_MAX_SIZE] ;
	uint8_t u8_indexArr = u8_INTIAL_VAL ;
	uint8_t u8_countWrongBalInput = u8_INTIAL_VAL ;
	uint8_t u8_keyPadReturnASCII = u8_KEYPAD_NOT_PRESSED ;
	LCD_command(DISPLAY_CLEAR) ;
	LCD_printString(LCD_REQUIRE_USER_BAL_STR) ;
	LCD_newLine() ;
	LCD_printString(LCD_REQUIRED_SAMPLE_BAL_STR) ;
	LCD_cursorMove(LEFT,7) ;

	while((u8_countWrongBalInput<u8_MAX_TIMES_WRONG_AMOUNT) && (u8_indexArr<(u8_MAX_BALANCE_MAX_SIZE-1)))
	{
		u8_keyPadReturnASCII = KeyPad_U8Data();
		if(u8_keyPadReturnASCII != u8_KEYPAD_NOT_PRESSED)
		{
			if(u8_keyPadReturnASCII<='9' && u8_keyPadReturnASCII>='0' )
			{
				pu8_userInputBal[u8_indexArr] = u8_keyPadReturnASCII ;
				if(u8_indexArr == 4)
				{
					LCD_cursorMove(RIGHT,1) ;
				}
				LCD_data(u8_keyPadReturnASCII) ;
				u8_indexArr++ ;
			}
			else
			{
				LCD_command(DISPLAY_CLEAR) ;
				LCD_printString((uint8_t*)"Enter a valid") ;
				LCD_newLine() ;
				LCD_printString((uint8_t*)"number") ;
				TIMER0_msdelay(1000) ;
				LCD_command(DISPLAY_CLEAR) ;
				LCD_printString(LCD_REQUIRE_USER_BAL_STR) ;
				LCD_newLine() ;
				LCD_printString(LCD_REQUIRED_SAMPLE_BAL_STR) ;
				LCD_cursorMove(LEFT,7) ;
				u8_indexArr = u8_INTIAL_VAL;
				++u8_countWrongBalInput;
			}
		}
	}

	pu8_userInputBal[u8_indexArr] = NULL_CHAR ;

	if(u8_countWrongBalInput<u8_MAX_TIMES_WRONG_AMOUNT)
	{

		EEPROM_u8ReadNeededPartBlock(u8_MAX_BALANCE_PAGE_NUM,u8_MAX_BALANCE_BYTE_NUM,pu8_atmMaxBal,u8_MAX_BALANCE_MAX_SIZE) ;
		u8_indexArr = u8_INTIAL_VAL ;

		while( (u8_indexArr<(u8_MAX_BALANCE_MAX_SIZE-1)) && (pu8_userInputBal[u8_indexArr] != NULL_CHAR) )
		{
			if(pu8_atmMaxBal[u8_indexArr]>pu8_userInputBal[u8_indexArr])
			{
				u8_balanceValidity = u8_BALANCE_VALID ;
				break ;
			}
			else if(pu8_atmMaxBal[u8_indexArr]<pu8_userInputBal[u8_indexArr])
			{
				u8_balanceValidity = u8_BALANCE_NOT_VALID ;
				break ;

			}
			else
			{
				u8_indexArr++ ;
			}
		}

	}
	else
	{
		u8_balanceValidity= u8_BALANCE_NOT_VALID ;
	}
	return u8_balanceValidity ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void ATM_voidShowTemp(void)
{
	uint8_t u8_tempNow, u8_keyPadReturnASCII ;
	LCD_command(DISPLAY_CLEAR) ;
	LCD_printString(LCD_EXIT_TO_MAIN_STR);
	LCD_newLine();
	LCD_printString(LCD_SHOW_TEMP_STR);
	u8_keyPadReturnASCII = KeyPad_U8Data() ;
	while (u8_keyPadReturnASCII != '1' )
	{
		u8_keyPadReturnASCII = KeyPad_U8Data() ;
		LM35_u8GetTempInC(&u8_tempNow) ;
		LCD_printDigits(u8_tempNow);
		LCD_cursorMove(LEFT,2);
		if(u8_tempNow>u8_MAX_TEMP)
		{
			BUZZER_on();
		}
		else
		{
			BUZZER_off();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ATM_voidGetCash(void)
{
	LCD_command(DISPLAY_CLEAR) ;
	LCD_printString(LCD_WAIT_CASH_STR);
	LCD_newLine() ;
	motorOn(MOTOR_ID_01,FORWARD) ;
	TIMER0_msdelay(1000) ;
	motorOff(MOTOR_ID_01,FORWARD) ;
	LCD_command(DISPLAY_CLEAR) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t ATM_u8checkAccounBal(uint8_t* pu8_balanceWanted,uint8_t* pu8_returnUserBal,uint16_t u16_RecNum)
{
	
	uint8_t u8_indexReturnUserBal = u8_INTIAL_VAL ;
	uint8_t u8_indexBalWanted = u8_INTIAL_VAL ;
	uint8_t u8_checkAccBalValdity = u8_BALANCE_NOT_VALID ;
	EEPROM_u8ReadNeededPartBlock(u16_RecNum,u8_BALANCE_BYTE_NUM,pu8_returnUserBal,u8_BALANCE_MAX_SIZE) ;

	//cashing first non-zero number in user Account balance
	while(pu8_returnUserBal[u8_indexReturnUserBal]!=NULL_CHAR)
	{
		if(pu8_returnUserBal[u8_indexReturnUserBal]>0)
		{
			break ;
		}
		else
		{
			u8_indexReturnUserBal++ ;
		}
	}

	if(pu8_returnUserBal[u8_indexReturnUserBal]!=NULL_CHAR)
	{
		while(pu8_balanceWanted[u8_indexBalWanted] != NULL_CHAR )
		{
			if(pu8_balanceWanted[u8_indexBalWanted]>0)
			{
				break ;
			}
			else
			{
				++u8_indexBalWanted ;
			}
		}

		if( ((u8_BALANCE_MAX_SIZE - u8_indexReturnUserBal) == (u8_MAX_BALANCE_MAX_SIZE - u8_indexBalWanted)) )
		{
			while((pu8_returnUserBal[u8_indexReturnUserBal]!=NULL_CHAR) && (pu8_balanceWanted[u8_indexBalWanted] != NULL_CHAR ) )
			{
				if(pu8_balanceWanted[u8_indexBalWanted] < pu8_returnUserBal[u8_indexReturnUserBal])
				{
					//user has enough amount rotate the motor for 1 sec, update balance,and terminate process
					u8_checkAccBalValdity = u8_BALANCE_VALID ;
					break;
				}
				else if(pu8_balanceWanted[u8_indexBalWanted] > pu8_returnUserBal[u8_indexReturnUserBal])
				{
					//print user has no enough balance terminate the process
					u8_checkAccBalValdity = u8_BALANCE_NOT_VALID ;
					LCD_command(DISPLAY_CLEAR) ;
					LCD_printString((uint8_t*)"Not Enough");
					LCD_newLine() ;
					LCD_printString((uint8_t*)"Account Bal.");
					TIMER0_msdelay(1000) ;
					LCD_command(DISPLAY_CLEAR) ;
					break ;
				}
				else
				{
					++u8_indexBalWanted ;
					++u8_indexReturnUserBal ;
				}
			}
			if(u8_checkAccBalValdity == u8_BALANCE_VALID)
			{
				//balance of user is exactly as he wanted , rotate the motor for 1 sec, update balance,and terminate process
				ATM_voidGetCash() ;
			}
		}
		else if ( ((u8_BALANCE_MAX_SIZE-u8_indexReturnUserBal) > (u8_MAX_BALANCE_MAX_SIZE-u8_indexBalWanted)) )
		{
			//user has enough amount rotate the motor for 1 sec, update balance,and terminate process
			u8_checkAccBalValdity = u8_BALANCE_VALID ;
			ATM_voidGetCash() ;
		}
		else
		{
			//process termination due to user has no enough balance
			u8_checkAccBalValdity = u8_BALANCE_NOT_VALID ;
			LCD_command(DISPLAY_CLEAR) ;
			LCD_printString((uint8_t*)"Not Enough");
			LCD_newLine() ;
			LCD_printString((uint8_t*)"Account Bal.");
			TIMER0_msdelay(1000) ;
			LCD_command(DISPLAY_CLEAR) ;
		}
	}
	else
	{
		u8_checkAccBalValdity = u8_BALANCE_NOT_VALID ;
	}
	return u8_checkAccBalValdity;
}

void ATM_voidStoreRecNum(uint16_t u16_recNum)
{
	uint8_t u8_highNipple, u8_lowNipple;
	
	u8_lowNipple = (uint8_t)(u16_recNum);
	u8_highNipple = (uint8_t)(u16_recNum >> 8);
	
	EEPROM_u8WriteWantedByte(u8_RECORDS_PAGE_NUM,u8_RECORDS_FIRST_BYTE_NUM, u8_lowNipple);
	EEPROM_u8WriteWantedByte(u8_RECORDS_PAGE_NUM,u8_RECORDS_SECOND_BYTE_NUM, u8_highNipple);
}

uint16_t ATM_u16GetRecNum(void)
{
	uint8_t u8_highNipple, u8_lowNipple;
	uint16_t u16_recNum;
	EEPROM_u8ReadWantedByte(u8_RECORDS_PAGE_NUM,u8_RECORDS_FIRST_BYTE_NUM,&u8_lowNipple);
	EEPROM_u8ReadWantedByte(u8_RECORDS_PAGE_NUM,u8_RECORDS_SECOND_BYTE_NUM,&u8_highNipple);
	
	u16_recNum = (uint16_t)((uint16_t)(u8_highNipple << 8) | (u8_lowNipple));
	return u16_recNum;
}