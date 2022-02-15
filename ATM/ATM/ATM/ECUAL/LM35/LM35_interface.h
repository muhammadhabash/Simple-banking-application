#ifndef __TEMP_SENSOR__LM35__INTERFACE__
#define __TEMP_SENSOR__LM35__INTERFACE__


#define u8_LM35_OK						(60)
#define u8_LM35_NEW_TEMP_OK				(61)
#define u8_LM35_NOK						(62)

#define u8_LM35_INTIALIZE_VAR			(0)
#define u16_LM35_CONVERT_UV_TO_MV		(1000)
#define u8_LM35_SCALE_FACTOR			(10)
#define u8_LM35_NUM_OF_READINGS			(4)

void LM35_voidInit(void) ; 
uint8_t LM35_u8GetTempInC(uint8_t* pu8_ReturnAvgTemp) ; 


#endif