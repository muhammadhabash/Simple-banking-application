#ifndef __ADC__INTERFACE__
#define __ADC__INTERFACE__

#include "adc_private.h"

/*
 *choose one of the voltage reference sources for ADC :
 *1- u8_ADC_NO_INTERNAL_REF     (AREF, Internal Vref turned off)
 *2- u8_ADC_VCC_INTERNAL_REF    (AVCC with external capacitor at AREF pin)
 *3- u8_ADC_2560mV_INTERNAL_REF (Internal 2.56V Voltage Reference with external capacitor at AREF pin)
 */	
#define u8_ADC_VREF							u8_ADC_2560mV_INTERNAL_REF

/*
 *choose one of input channels for single input Mode of ADC :
 *1- u8_ADC_CH0
 *2- u8_ADC_CH1
 *3- u8_ADC_CH2
 *4- u8_ADC_CH3
 *5- u8_ADC_CH4
 *6- u8_ADC_CH5
 *7- u8_ADC_CH6
 *8- u8_ADC_CH7
 */
#define u8_ADC_CH_SELECT					u8_ADC_CH0		

/*
 *choose the adc state : 
 *1-u8_ADC_ENABLE 
 *2-u8_ADC_DISABLE
 */

#define u8_ADC_STATE						u8_ADC_ENABLE

/*
 *choose the adc interrupt after coversion ended state : 
 *1-u8_ADC_INT_EN 
 *2-u8_ADC_INT_DIS
 */

#define u8_ADC_INT_STATE					u8_ADC_INT_DIS

/*
 *choose the adc interrupt after coversion ended state : 
 *1-u8_AUTO_TRIG_EN 
 *2-u8_AUTO_TRIG_DIS
 */

#define u8_ADC_AUTO_TRIG_STATE				u8_AUTO_TRIG_EN			

/*
 *choose one of the trig source modes if u8_ADC_AUTO_TRIG_STATE is u8_AUTO_TRIG_EN (if not this option will do nothing) :
 *1- u8_ADC_FREE_RUNNING_MODE	
 *2- u8_ADC_ANALOG_COMP			
 *3- u8_ADC_EXT_INT_REQ			
 *4- u8_ADC_TIMER0_COMPARE_MATCH	
 *5- u8_ADC_TIMER0_OV			
 *6- u8_ADC_TIMER_COMPARE_MATCH_B
 *7- u8_ADC_TIMER1_OV			
 *8- u8_ADC_TIMER1_CAPTURE_EVENT	
 */
#define u8_ADC_TRIG_SOURCE					u8_ADC_FREE_RUNNING_MODE

/*
 *choose one of The ADC prescalers (divide clock of cpu by and make it the clock of ADC) :
 *1- u8_ADC_PRE_2	
 *2- u8_ADC_PRE_4	
 *3- u8_ADC_PRE_8	
 *4- u8_ADC_PRE_16	
 *5- u8_ADC_PRE_32
 *6- u8_ADC_PRE_64
 *7- u8_ADC_PRE_128 	
 */

#define u8_PRESCALER_SELECT					u8_ADC_PRE_128

#define u8_ADC_FLAG_RISE					1
#define u8_ADC_STEP_SIZE_IN_VCC_UV			4880
#define u8_ADC_STEP_SIZE_IN_HALF_VCC_UV		2500



void ADC_voidInit(void) ;
void ADC_voidStartConversion(void) ; //Make ADC enabled and start conversion 
void ADC_voidStop(void) ;  // make ADC Disabled
uint8_t ADC_u8AutoTrigOn(uint8_t u8_TrigSource) ; /*Make ADC Auto trigger on and set the trigger source and return error state if trigger
												   *Source sent to argument incorrect */
void ADC_u8AutoTrigOff(void) ; //Make ADC auto trigger disable
void ADC_voidIntEn(void) ; //Make ADC periphral interrupt Enable
void ADC_voidIntDis(void) ; //Make ADC periphral interrupt Disable
uint8_t ADC_u8GetFlagInt(uint8_t* pu8_ReturnFlagInt) ; /*Return error state if the pointer sent is NULL and if not return 
														*ADC Interrupt flag value in pu8_ReturnFlagInt pointer.*/
uint8_t ADC_u8GetResult(uint16_t* pu16_ReturnADCResult) ; //return the result in pu16_ReturnADCResult if pu16_ReturnADCResult != NULL 
void ADC_voidSetCallBack(void(*ISRFuncToSet)(void)); 

#endif
