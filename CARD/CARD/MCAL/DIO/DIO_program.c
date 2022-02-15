#include "../../LIB/STD_types.h"
#include "../../LIB/BIT_math.h"

#include "DIO_interface.h"
#include "DIO_Error_state.h"

uint8_t DIO_SetPinDirection(uint8_t au8_PORT , uint8_t au8_PIN , uint8_t au8_DIRECTION)
{
	uint8_t au8_errorstate = DIO_SUCCESS ;
	switch (au8_PORT)
	{
		case PORTA: if (au8_DIRECTION==INPUT)
					{
						CLR_BIT(DDRA_REG,au8_PIN);
					}
					else if(au8_DIRECTION==OUTPUT)
					{
						SET_BIT(DDRA_REG,au8_PIN);
					}
					else
					{
						//do noting
					}
					break;
		case PORTB: if (au8_DIRECTION==INPUT)
					{
						CLR_BIT(DDRB_REG,au8_PIN);
					}
					else if(au8_DIRECTION==OUTPUT)
					{
						SET_BIT(DDRB_REG,au8_PIN);
					}
					else
					{
						//do noting
					}
					break;
		case PORTC: if (au8_DIRECTION==INPUT)
					{
						CLR_BIT(DDRC_REG,au8_PIN);
					}
					else if(au8_DIRECTION==OUTPUT)
					{
						SET_BIT(DDRC_REG,au8_PIN);
					}
					else
					{
						//do noting
					}
					break;
		case PORTD: if (au8_DIRECTION==INPUT)
					{
						CLR_BIT(DDRD_REG,au8_PIN);
					}
					else if(au8_DIRECTION==OUTPUT)
					{
						SET_BIT(DDRD_REG,au8_PIN);
					}
					else
					{
						//do noting
					}
					break;
		default:au8_errorstate = DIO_CHOISE_NOT_FOUND;//error
			break;
	}//switch
	return au8_errorstate;
}//function
uint8_t DIO_SetPinValue(uint8_t au8_PORT , uint8_t au8_PIN , uint8_t au8_VALUE)
{
	uint8_t au8_errorstate = DIO_SUCCESS ;
	switch (au8_PORT)
		{
			case PORTA: if (au8_VALUE==LOW)
						{
							CLR_BIT(PORTA_REG,au8_PIN);
						}
						else if(au8_VALUE==HIGH)
						{
							SET_BIT(PORTA_REG,au8_PIN);
						}
						else
						{
							//do noting
						}
						break;
			case PORTB: if (au8_VALUE==LOW)
						{
							CLR_BIT(PORTB_REG,au8_PIN);
						}
						else if(au8_VALUE==HIGH)
						{
							SET_BIT(PORTB_REG,au8_PIN);
						}
						else
						{
							//do noting
						}
						break;
			case PORTC: if (au8_VALUE==LOW)
						{
							CLR_BIT(PORTC_REG,au8_PIN);
						}
						else if(au8_VALUE==HIGH)
						{
							SET_BIT(PORTC_REG,au8_PIN);
						}
						else
						{
							//do noting
						}
						break;
			case PORTD: if (au8_VALUE==LOW)
						{
							CLR_BIT(PORTD_REG,au8_PIN);
						}
						else if(au8_VALUE==HIGH)
						{
							SET_BIT(PORTD_REG,au8_PIN);
						}
						else
						{
							//do noting
						}
						break;
			default:au8_errorstate = DIO_CHOISE_NOT_FOUND;//error
				break;
		}//switch
	return au8_errorstate;
}//function
uint8_t DIO_TogPinValue(uint8_t au8_PORT , uint8_t PIN)
{
	uint8_t au8_errorstate = DIO_SUCCESS ;
	switch(au8_PORT)
	{
		case PORTA: TOG_BIT(PORTA_REG,PIN);break;
		case PORTB: TOG_BIT(PORTB_REG,PIN);break;
		case PORTC: TOG_BIT(PORTC_REG,PIN);break;
		case PORTD: TOG_BIT(PORTD_REG,PIN);break;
		default:au8_errorstate = DIO_CHOISE_NOT_FOUND;//error
			break;
	}//switch
	return au8_errorstate;
}//function
uint8_t DIO_TogPinDirection(uint8_t au8_PORT , uint8_t PIN)
{
	uint8_t au8_errorstate = DIO_SUCCESS ;
	switch(au8_PORT)
	{
		case PORTA: TOG_BIT(DDRA_REG,PIN);break;
		case PORTB: TOG_BIT(DDRB_REG,PIN);break;
		case PORTC: TOG_BIT(DDRC_REG,PIN);break;
		case PORTD: TOG_BIT(DDRD_REG,PIN);break;
		default:au8_errorstate = DIO_CHOISE_NOT_FOUND;//error
			break;
	}//switch
	return au8_errorstate;
}//function
uint8_t DIO_Setau8_PORTDirection(uint8_t au8_PORT , uint8_t DIRECTION)
{
	uint8_t au8_errorstate = DIO_SUCCESS ;
	switch(au8_PORT)
	{
		case PORTA: DDRA_REG=DIRECTION;break;
		case PORTB: DDRB_REG=DIRECTION;break;
		case PORTC: DDRC_REG=DIRECTION;break;
		case PORTD: DDRD_REG=DIRECTION;break;
		default:au8_errorstate = DIO_CHOISE_NOT_FOUND;//error
			break;
	}//switch
	return au8_errorstate;
}//function
uint8_t DIO_Setau8_PORTValue(uint8_t au8_PORT , uint8_t VALUE)
{
	uint8_t au8_errorstate = DIO_SUCCESS ;
	switch(au8_PORT)
	{
		case PORTA: PORTA_REG=VALUE;break;
		case PORTB: PORTB_REG=VALUE;break;
		case PORTC: PORTC_REG=VALUE;break;
		case PORTD: PORTD_REG=VALUE;break;
		default:au8_errorstate = DIO_CHOISE_NOT_FOUND;//error
			break;
	}//switch
	return au8_errorstate;
}//function
uint8_t DIO_GetPinValue(uint8_t au8_PORT,uint8_t PIN)
{
	uint8_t PinValue;
	switch(au8_PORT)
	{
		case PORTA: PinValue = GET_BIT(PINA_REG,PIN); break;
		case PORTB: PinValue = GET_BIT(PINB_REG,PIN); break;
		case PORTC: PinValue = GET_BIT(PINC_REG,PIN); break;
		case PORTD: PinValue = GET_BIT(PIND_REG,PIN); break;
		default:PinValue=DIO_CHOISE_NOT_FOUND;//error
			break;
	}//switch
	return PinValue;
}//function
uint8_t DIO_Getau8_PORTValue(uint8_t au8_PORT)
{
	uint8_t PinValue;
	switch(au8_PORT)
	{
		case PORTA: PinValue =*((uint8_t*)0x39); break;
		case PORTB: PinValue =*((uint8_t *)0x36); break;
		case PORTC: PinValue =*((uint8_t*)0x33); break;
		case PORTD: PinValue =*((uint8_t*)0x30); break;
		default:PinValue=DIO_CHOISE_NOT_FOUND;//error
			break;
	}//switch
	return PinValue;
}

