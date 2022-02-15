
#include "../../LIB/STD_types.h"
#include "../../MCAL/I2C/I2C_interface.h"
#include "../../LIB/ATMEGA32_registers.h"
#include "EEPROM_interface.h"
#include "EEPROM_private.h"

void EEPROM_voidInit(void) 
{
	I2C_masterInit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t EEPROM_u8WriteNeededPartBlock(uint16_t u16_PageNum,uint8_t u8_ByteNum,uint8_t* pu8_ArrWantedToWrite,uint8_t u8_ArrSize ) 
{
	uint8_t u8_PageAdd = u8_EEPROM_INTIAL_VAL ; 
	uint8_t u8_ArrIndex = u8_EEPROM_INTIAL_VAL ;
	uint8_t u8_ErrorInArg = u8_EEPROM_NO_ARG_ERROR ; 
	if((u8_ByteNum+u8_ArrSize)<u8_EEPROM_MAX_BYTE_ADDRESS && u16_PageNum<u16_EEPROM_MAX_PAGE_ADDRESS  && pu8_ArrWantedToWrite!=NULL_POINTER )
	{
		I2C_masterStart();
		I2C_masterWriteToAddress(u8_EEPROM_DEVICE_ADD); 
		u8_PageAdd = (uint8_t)(u16_PageNum>>u8_EEPROM_TAKE_7HSB_OF_PAGE_ADD) ; 
		I2C_masterWriteData(u8_PageAdd) ;
		u8_PageAdd = (uint8_t)((u16_PageNum<<u8_EEPROM_REMOVE_SENT_PAGE_ADD)>>u8_EEPROM_MAKE_REMAIN_ADD_PART_IN_HSB);
		u8_ByteNum|=u8_PageAdd ; 
		I2C_masterWriteData(u8_ByteNum) ;
		for(u8_ArrIndex=u8_EEPROM_INTIAL_VAL;u8_ArrIndex<u8_ArrSize;u8_ArrIndex++)
		{
			if(pu8_ArrWantedToWrite[u8_ArrIndex] != NULL_CHAR )
			{
				I2C_masterWriteData((pu8_ArrWantedToWrite[u8_ArrIndex]));	
			}
			else break;
		}
		I2C_masterStop();
	}
	else 
	{
		u8_ErrorInArg = u8_EEPROM_ARG_ERROR ; 
	}
	return u8_ErrorInArg ; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t EEPROM_u8WriteWantedByte(uint16_t u16_PageNum,uint8_t u8_ByteNum,uint8_t u8_WantedToWrite)
{
	uint8_t u8_PageAdd = u8_EEPROM_INTIAL_VAL ; 
	uint8_t u8_ErrorInArg = u8_EEPROM_NO_ARG_ERROR ; 
	if(u8_ByteNum<u8_EEPROM_MAX_BYTE_ADDRESS && u16_PageNum<u16_EEPROM_MAX_PAGE_ADDRESS  )
	{
		I2C_masterStart();
		I2C_masterWriteToAddress(u8_EEPROM_DEVICE_ADD); 
		u8_PageAdd = (uint8_t)(u16_PageNum>>u8_EEPROM_TAKE_7HSB_OF_PAGE_ADD);
		I2C_masterWriteData(u8_PageAdd);
		u8_PageAdd = (uint8_t)((u16_PageNum<<u8_EEPROM_REMOVE_SENT_PAGE_ADD)>>u8_EEPROM_MAKE_REMAIN_ADD_PART_IN_HSB);
		u8_ByteNum|=u8_PageAdd ; 
		I2C_masterWriteData(u8_ByteNum);
		I2C_masterWriteData(u8_WantedToWrite);
		I2C_masterStop();
	}
	else 
	{
		u8_ErrorInArg = u8_EEPROM_ARG_ERROR ; 
	}
	return u8_ErrorInArg ; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t EEPROM_u8ReadNeededPartBlock(uint16_t u16_PageNum,uint8_t u8_ByteNum,uint8_t* pu8_ArrWantedToRead,uint8_t u8_ArrSize)
{
   
	uint8_t u8_PageAdd = u8_EEPROM_INTIAL_VAL ; 
	uint8_t u8_ArrIndex = u8_EEPROM_INTIAL_VAL ;
	uint8_t u8_ErrorInArg = u8_EEPROM_NO_ARG_ERROR ; 
	if(((u8_EEPROM_MAX_BYTE_ADDRESS-u8_ByteNum)>=u8_ArrSize)  && u16_PageNum<u16_EEPROM_MAX_PAGE_ADDRESS && pu8_ArrWantedToRead!=NULL_POINTER )
	{
		
		I2C_masterStart();
		I2C_masterWriteToAddress(u8_EEPROM_DEVICE_ADD); 
		u8_PageAdd = (uint8_t)(u16_PageNum>>u8_EEPROM_TAKE_7HSB_OF_PAGE_ADD) ; 
		I2C_masterWriteData(u8_PageAdd) ;
		u8_PageAdd = (uint8_t)((u16_PageNum<<u8_EEPROM_REMOVE_SENT_PAGE_ADD)>>u8_EEPROM_MAKE_REMAIN_ADD_PART_IN_HSB);
		u8_ByteNum|=u8_PageAdd ; 
		I2C_masterWriteData(u8_ByteNum) ;
		I2C_repeatedStart();
		I2C_masterReadFromAddress(u8_EEPROM_DEVICE_ADD) ;
		for(u8_ArrIndex= u8_EEPROM_INTIAL_VAL;u8_ArrIndex<(u8_ArrSize - u8_EEPROM_LAST);u8_ArrIndex++)
		{
			
			pu8_ArrWantedToRead[u8_ArrIndex] = I2C_masterReadData();
			if(pu8_ArrWantedToRead[u8_ArrIndex] == NULL_CHAR )
			{
				break;
			}
		}
		pu8_ArrWantedToRead[u8_ArrIndex] = I2C_masterReadFinalData();
		I2C_masterStop();
		
	}
	else 
	{
		u8_ErrorInArg = u8_EEPROM_ARG_ERROR ; 
	}
	return u8_ErrorInArg ; 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t EEPROM_u8ReadWantedByte(uint16_t u16_PageNum,uint8_t u8_ByteNum,uint8_t* u8_WantedToRead)
{
	uint8_t u8_PageAdd = u8_EEPROM_INTIAL_VAL ; 
	uint8_t u8_ErrorInArg = u8_EEPROM_NO_ARG_ERROR ; 
	if((u8_ByteNum<u8_EEPROM_MAX_BYTE_ADDRESS) && u16_PageNum<u16_EEPROM_MAX_PAGE_ADDRESS && u8_WantedToRead!=NULL_POINTER )
	{
		I2C_masterStart();
		I2C_masterWriteToAddress(u8_EEPROM_DEVICE_ADD) ; 
		u8_PageAdd = (uint8_t)(u16_PageNum>>u8_EEPROM_TAKE_7HSB_OF_PAGE_ADD) ; 
		I2C_masterWriteData(u8_PageAdd) ;
		u8_PageAdd = (uint8_t)((u16_PageNum<<u8_EEPROM_REMOVE_SENT_PAGE_ADD)>>u8_EEPROM_MAKE_REMAIN_ADD_PART_IN_HSB);
		u8_ByteNum|=u8_PageAdd ; 
		I2C_masterWriteData(u8_ByteNum) ;
		I2C_repeatedStart();
		I2C_masterReadFromAddress(u8_EEPROM_DEVICE_ADD) ;
		*(u8_WantedToRead) = I2C_masterReadData();
		I2C_masterStop();
	}
	else 
	{
		u8_ErrorInArg = u8_EEPROM_ARG_ERROR ; 
	}
	return u8_ErrorInArg ; 
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t EEPROM_u8ReadCurrentByte(uint8_t* u8_WantedToRead) 
{
	uint8_t u8_ErrorInArg = u8_EEPROM_NO_ARG_ERROR ; 
	if(u8_WantedToRead!=NULL_POINTER )
	{
		I2C_masterStart();
		I2C_masterReadFromAddress(u8_EEPROM_DEVICE_ADD) ;
		*u8_WantedToRead = I2C_masterReadData();
		I2C_masterStop();
	}
	else 
	{
		u8_ErrorInArg = u8_EEPROM_ARG_ERROR ; 
	}
	return u8_ErrorInArg ; 
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////