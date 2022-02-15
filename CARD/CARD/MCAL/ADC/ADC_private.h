#ifndef __ADC__PRIVATE__
#define __ADC__PRIVATE__



//BITS IN ADMUX (ADC Multiplexer Selection Register)
#define u8_ADC_REFS1								7					
#define u8_ADC_REFS0 								6
#define u8_ADC_ADLAR								5
#define u8_ADC_MUX4									4
#define u8_ADC_MUX3									3
#define u8_ADC_MUX2									2
#define u8_ADC_MUX1									1
#define u8_ADC_MUX0									0

//BITS IN ADCSRA (ADC Control and Status Register A)
#define u8_ADC_ADEN									7
#define u8_ADC_ADSC                                 6
#define u8_ADC_ADATE                                5
#define u8_ADC_ADIF									4
#define u8_ADC_ADIE                                 3
#define u8_ADC_ADPS2                                2
#define u8_ADC_ADPS1                                1
#define u8_ADC_ADPS0                                0

//BITS IN Special FunctionIO Register– SFIOR
#define u8_ADC_ADTS2								7                                    
#define u8_ADC_ADTS1								6
#define u8_ADC_ADTS0								5






#define u8_ADC_NO_INTERNAL_REF     					10
#define u8_ADC_VCC_INTERNAL_REF   					11 
#define u8_ADC_2560mV_INTERNAL_REF  				12
#define u8_ADC_SINGLE_ENDED_IN						13
#define u8_ADC_POS_DIFFERENTIAL_IN					14
#define u8_ADC_NEG_DIFFERENTIAL_IN					15

#define u8_ADC_CH0									16
#define u8_ADC_CH1									17
#define u8_ADC_CH2									18
#define u8_ADC_CH3									19
#define u8_ADC_CH4									20
#define u8_ADC_CH5									21
#define u8_ADC_CH6									22
#define u8_ADC_CH7									23

#define u8_ADC_ENABLE								24
#define u8_ADC_DISABLE								25

#define u8_ADC_INT_EN								26
#define u8_ADC_INT_DIS								27

#define u8_AUTO_TRIG_EN 							28 
#define u8_AUTO_TRIG_DIS							29

#define u8_ADC_FREE_RUNNING_MODE					30
#define u8_ADC_ANALOG_COMP							31
#define u8_ADC_EXT_INT_REQ							32
#define u8_ADC_TIMER0_COMPARE_MATCH					33
#define u8_ADC_TIMER0_OV							34
#define u8_ADC_TIMER_COMPARE_MATCH_B				35
#define u8_ADC_TIMER1_OV							36
#define u8_ADC_TIMER1_CAPTURE_EVENT					37



#define u8_ADC_PRE_2								38
#define u8_ADC_PRE_4								39
#define u8_ADC_PRE_8								40
#define u8_ADC_PRE_16								41
#define u8_ADC_PRE_32								42
#define u8_ADC_PRE_64								43
#define u8_ADC_PRE_128								44


#define u8_ADC_NOK									45
#define u8_ADC_OK									46










#endif
