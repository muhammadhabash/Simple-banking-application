#ifndef __EEPROM__INTERFACE__
#define __EEPROM__INTERFACE__

#include "../../LIB/STD_types.h"


void EEPROM_voidInit(void) ;
uint8_t EEPROM_u8WriteNeededPartBlock(uint16_t u16_PageNum,uint8_t u8_ByteNum,uint8_t* pu8_ArrWantedToWrite,uint8_t u8_ArrSize ) ;
uint8_t EEPROM_u8WriteWantedByte(uint16_t u16_PageNum,uint8_t u8_ByteNum,uint8_t u8_WantedToWrite) ;
uint8_t EEPROM_u8ReadNeededPartBlock(uint16_t u16_PageNum,uint8_t u8_ByteNum,uint8_t* pu8_ArrWantedToRead,uint8_t u8_ArrSize) ;
uint8_t EEPROM_u8ReadWantedByte(uint16_t u16_PageNum,uint8_t u8_ByteNum,uint8_t* u8_WantedToRead) ;
uint8_t EEPROM_u8ReadCurrentByte(uint8_t* u8_WantedToRead) ;



#endif 
