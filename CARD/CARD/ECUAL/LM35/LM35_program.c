#include "../../LIB/STD_types.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "LM35_interface.h"





void LM35_voidInit(void) 
{
	DIO_SetPinDirection(PORTA,PIN0,INPUT);
	DIO_SetPinValue(PORTA,PIN0,LOW);
	ADC_voidInit(); 
	ADC_voidStartConversion();
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t LM35_u8GetTempInC(uint8_t* pu8_ReturnAvgTemp) 
{
	static uint8_t su8_Temp1= u8_LM35_INTIALIZE_VAR, su8_Temp2=u8_LM35_INTIALIZE_VAR, su8_NewTemp3 = u8_LM35_INTIALIZE_VAR, su8_Temp4 = u8_LM35_INTIALIZE_VAR; 
	uint8_t u8_AdcIntFlag = u8_LM35_INTIALIZE_VAR, u8_ErrorState = u8_LM35_OK ; 
	uint16_t u16_AdcResult = u8_LM35_INTIALIZE_VAR ;
	if(pu8_ReturnAvgTemp!=NULL_POINTER)
	{
		ADC_u8GetFlagInt(&u8_AdcIntFlag); 
		if(u8_AdcIntFlag==u8_ADC_FLAG_RISE )
		{
			ADC_u8GetResult(&u16_AdcResult) ;
			if(u8_ADC_VREF== u8_ADC_VCC_INTERNAL_REF )
			{
				su8_NewTemp3 = (uint8_t)((uint32_t)(u8_ADC_STEP_SIZE_IN_VCC_UV*(uint32_t)(u16_AdcResult))/(uint32_t)(u16_LM35_CONVERT_UV_TO_MV*u8_LM35_SCALE_FACTOR)) ; 
			}
			else if(u8_ADC_VREF== u8_ADC_2560mV_INTERNAL_REF)
			{
				su8_NewTemp3 = (uint8_t)((uint32_t)(u8_ADC_STEP_SIZE_IN_HALF_VCC_UV*(uint32_t)(u16_AdcResult))/(uint32_t)(u16_LM35_CONVERT_UV_TO_MV*u8_LM35_SCALE_FACTOR)) ; 
			}
			u8_ErrorState = u8_LM35_NEW_TEMP_OK ; 
		}
		if(su8_Temp2==0)
		{
			su8_Temp2 = su8_NewTemp3 ; 
		}
		if(su8_Temp1==0)
		{
			su8_Temp1 = su8_Temp2 ; 
		}
		if(su8_Temp4==0)
		{
			su8_Temp4 = su8_Temp1;
		}
		*pu8_ReturnAvgTemp = (su8_Temp1 + su8_Temp2 + su8_Temp4 + su8_NewTemp3) / u8_LM35_NUM_OF_READINGS ; 
		su8_Temp4 = su8_Temp1 ; 
		su8_Temp1 = su8_Temp2 ;
		su8_Temp2 = su8_NewTemp3; 
	}
	else 
	{
		u8_ErrorState = u8_LM35_NOK ;
	}
	return u8_ErrorState ; 
}
