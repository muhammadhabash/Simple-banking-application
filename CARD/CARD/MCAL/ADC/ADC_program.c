#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/atmega32_registers.h"
#include "adc_private.h"
#include "adc_interface.h"


static void (*ADCSetCallBackISR)(void) = NULL_POINTER; 

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ADC_voidInit(void)
{
	//set VREF as internal (with Vref = Vcc or 2.56) or external Vref source
	#if u8_ADC_VREF==u8_ADC_NO_INTERNAL_REF
		CLR_BIT(Ru8_ADMUX,u8_ADC_REFS1) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_REFS0) ;
	#elif u8_ADC_VREF==u8_ADC_VCC_INTERNAL_REF
		CLR_BIT(Ru8_ADMUX,u8_ADC_REFS1) ; 
		SET_BIT(Ru8_ADMUX,u8_ADC_REFS0) ;		
	#elif u8_ADC_VREF==u8_ADC_2560mV_INTERNAL_REF
		SET_BIT(Ru8_ADMUX,u8_ADC_REFS1) ; 
		SET_BIT(Ru8_ADMUX,u8_ADC_REFS0) ;	
	#else 
		#error "ADC VREF prebuild config error"
	#endif
	
	// Adjust the adc result to the right 
	//CLR_BIT(Ru8_ADMUX,u8_ADC_ADLAR);
	
	//set the wanted channel for the ADC single mode 
	#if u8_ADC_CH_SELECT==u8_ADC_CH0
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX4) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX3) ;
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX2) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX1) ;
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX0) ;
	#elif u8_ADC_CH_SELECT==u8_ADC_CH1
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX4) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX3) ;
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX2) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX1) ;
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX0) ;
	#elif u8_ADC_CH_SELECT==u8_ADC_CH2
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX4) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX3) ;
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX2) ; 
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX1) ;
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX0) ;
	#elif u8_ADC_CH_SELECT==u8_ADC_CH3
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX4) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX3) ;
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX2) ; 
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX1) ;
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX0) ;
	#elif u8_ADC_CH_SELECT==u8_ADC_CH4
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX4) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX3) ;
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX2) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX1) ;
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX0) ;
	#elif u8_ADC_CH_SELECT==u8_ADC_CH5
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX4) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX3) ;
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX2) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX1) ;
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX0) ;	
	#elif u8_ADC_CH_SELECT==u8_ADC_CH6
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX4) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX3) ;
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX2) ; 
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX1) ;
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX0) ;
	#elif u8_ADC_CH_SELECT==u8_ADC_CH7
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX4) ; 
		CLR_BIT(Ru8_ADMUX,u8_ADC_MUX3) ;
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX2) ; 
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX1) ;
		SET_BIT(Ru8_ADMUX,u8_ADC_MUX0) ;
	#else 
		#error "ADC prebuild single mode channel select config error"
	#endif 


	//set ADC EN or DIS 
	#if u8_ADC_STATE==u8_ADC_ENABLE
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADEN) ;
	#elif u8_ADC_STATE==u8_ADC_DISABLE
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADEN) ;
	#else
		#error "ADC prebuild ADC state config error"
	#endif	

	//set ADC interrupt after finishing ADC conversion
	#if u8_ADC_INT_STATE==u8_ADC_INT_EN 
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADIE) ;               
	#elif u8_ADC_INT_STATE==u8_ADC_INT_DIS
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADIE) ;
	#else
		#error "ADC prebuild ADC interrupt state config error"
	#endif	

	//set state of auto trigger EN or DIS and if EN set the trigger source 
	#if u8_ADC_AUTO_TRIG_STATE==u8_AUTO_TRIG_EN  
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADATE) ;
		#if u8_ADC_TRIG_SOURCE==u8_ADC_FREE_RUNNING_MODE
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		#elif u8_ADC_TRIG_SOURCE==u8_ADC_ANALOG_COMP			
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		#elif u8_ADC_TRIG_SOURCE==u8_ADC_EXT_INT_REQ			
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		#elif u8_ADC_TRIG_SOURCE==u8_ADC_TIMER0_COMPARE_MATCH
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		#elif u8_ADC_TRIG_SOURCE==u8_ADC_TIMER0_OV			
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		#elif u8_ADC_TRIG_SOURCE==u8_ADC_TIMER_COMPARE_MATCH_B
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		#elif u8_ADC_TRIG_SOURCE==u8_ADC_TIMER1_OV			
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		#elif u8_ADC_TRIG_SOURCE==u8_ADC_TIMER1_CAPTURE_EVENT
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		#else 
			#error "ADC prebuild ADC Trigger Source config error"
		#endif 
	#elif u8_ADC_AUTO_TRIG_STATE==u8_AUTO_TRIG_DIS
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADATE) ;
	#else
		#error "ADC prebuild ADC AUTO Trig state config error"
	#endif	

	//SET the prescaler time for adc 
	#if u8_PRESCALER_SELECT == u8_ADC_PRE_2
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADPS2) ;
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADPS1) ;
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS0) ;
	#elif u8_PRESCALER_SELECT == u8_ADC_PRE_4	
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADPS2) ;
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS1) ;
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADPS0) ;
	#elif u8_PRESCALER_SELECT == u8_ADC_PRE_8	
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADPS2) ;
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS1) ;
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS0) ;
	#elif u8_PRESCALER_SELECT == u8_ADC_PRE_16	
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS2) ;
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADPS1) ;
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADPS0) ;
	#elif u8_PRESCALER_SELECT == u8_ADC_PRE_32
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS2) ;
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADPS1) ;
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS0) ;
	#elif u8_PRESCALER_SELECT == u8_ADC_PRE_64
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS2) ;
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS1) ;
		CLR_BIT(Ru8_ADCSRA,u8_ADC_ADPS0) ;
	#elif u8_PRESCALER_SELECT == u8_ADC_PRE_128 
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS2) ;
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS1) ;
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADPS0) ;
	#else 
		#error "ADC prebuild ADC PRESCALER value config error"
	#endif
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ADC_voidStartConversion(void) //Make ADC enabled and start conversion 
{
	SET_BIT(Ru8_ADCSRA,u8_ADC_ADEN) ;               
	SET_BIT(Ru8_ADCSRA,u8_ADC_ADSC) ;               
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ADC_voidStop(void) // make ADC Disabled
{
	CLR_BIT(Ru8_ADCSRA,u8_ADC_ADEN) ;               
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t ADC_u8AutoTrigOn(uint8_t u8_TrigSource)  /*Make ADC Auto trigger on and set the trigger source and return error state if trigger
												  *Source sent to argument incorrect */
{
	uint8_t u8_ErrorState = u8_ADC_OK ;
	if(u8_TrigSource>=u8_ADC_FREE_RUNNING_MODE && u8_TrigSource<=u8_ADC_TIMER1_CAPTURE_EVENT)
	{
		SET_BIT(Ru8_ADCSRA,u8_ADC_ADATE) ;
		if (u8_TrigSource==u8_ADC_FREE_RUNNING_MODE)
		{
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		}
		else if (u8_TrigSource==u8_ADC_ANALOG_COMP)		
		{
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		}
		else if (u8_TrigSource==u8_ADC_EXT_INT_REQ)			
		{	CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		}
		else if (u8_TrigSource==u8_ADC_TIMER0_COMPARE_MATCH)
		{
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		}
		else if (u8_TrigSource==u8_ADC_TIMER0_OV)			
		{
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		}
		else if (u8_TrigSource==u8_ADC_TIMER_COMPARE_MATCH_B)
		{
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		}
		else if (u8_TrigSource==u8_ADC_TIMER1_OV)			
		{
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			CLR_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		}
		else
		{
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS2) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS1) ;
			SET_BIT(Ru8_SFIOR,u8_ADC_ADTS0) ;
		}
	}
	else 
	{
		u8_ErrorState = u8_ADC_NOK ; 
	}
	return u8_ErrorState ; 
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ADC_u8AutoTrigOff(void) //Make ADC auto trigger disable
{
	CLR_BIT(Ru8_ADCSRA,u8_ADC_ADATE) ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ADC_voidIntEn(void) //Make ADC periphral interrupt Enable
{
	SET_BIT(Ru8_ADCSRA,u8_ADC_ADIE) ;               
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ADC_voidIntDis(void) //Make ADC periphral interrupt Disable
{
	CLR_BIT(Ru8_ADCSRA,u8_ADC_ADIE) ;               
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t ADC_u8GetFlagInt(uint8_t* pu8_ReturnFlagInt) /*Return error state if the pointer sent is NULL and if not return 
														*ADC Interrupt flag value in pu8_ReturnFlagInt pointer.*/
{
	uint8_t u8_ErrorState = u8_ADC_OK ; 
	if(pu8_ReturnFlagInt!=NULL_POINTER)
	{
		*pu8_ReturnFlagInt = GET_BIT(Ru8_ADCSRA,u8_ADC_ADIF) ; 
	}
	else 
	{
		 u8_ErrorState = u8_ADC_NOK ;
	}
	return u8_ErrorState ; 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

uint8_t ADC_u8GetResult(uint16_t* pu16_ReturnADCResult) //return the result in pu16_ReturnADCResult if pu16_ReturnADCResult != NULL 
{
	uint8_t u8_ErrorState = u8_ADC_OK ;
	if(pu16_ReturnADCResult!=NULL_POINTER)
	{
		*pu16_ReturnADCResult = Ru8_ADCL; 
		(*pu16_ReturnADCResult)|= (Ru8_ADCH<<8); 
	}
	else 
	{
		 u8_ErrorState = u8_ADC_NOK ;
	}
	return u8_ErrorState ; 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ADC_voidSetCallBack(void(*ISRFuncToSet)(void)) 
{
	ADCSetCallBackISR = ISRFuncToSet ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

void __vector_16 (void)      __attribute__((signal));
void __vector_16 (void)
{
	if(ADCSetCallBackISR!=NULL_POINTER)
	{
		ADCSetCallBackISR() ;
	}
	else 
	{
		//do nothing
	}
}