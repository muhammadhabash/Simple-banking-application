#include "../../LIB/BIT_math.h"
#include "../../LIB/ATMEGA32_registers.h"
#include "TIMERS.h"

volatile uint32_t counts = 0;

void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	counts++;
}

void OVI0_init(void)
{
	SET_BIT(Ru8_TIMSK,0);
	SET_BIT(Ru8_SREG,7); 
}

void OCI0_init(void)
{
	SET_BIT(Ru8_TIMSK,1);
	SET_BIT(Ru8_SREG,7);
}

void OVI2_init(void)
{
	SET_BIT(Ru8_TIMSK,6);
	SET_BIT(Ru8_SREG,7);
}

void OCI2_init(void)
{
	SET_BIT(Ru8_TIMSK,7);
	SET_BIT(Ru8_SREG,7);
}

void TIMER0_msdelay(uint16_t mseconds)
{	
	volatile uint32_t ticks;
	volatile uint16_t remainder;
	ticks     = ( ( mseconds / 0.001 ) / 255 );
	remainder = ((mseconds / 0.001) - ( ticks * 255 ));  //Calculating the remaining fraction of clock cycles
	OVI0_init();                                         //Enabling system interrupt and flag for overflow int timer 0
	TIMER0_start(8);                                     //Prescaler of one that yields 8MHz frequency
	while (counts < ticks)
	{
		//Stay here till reaching the overflow counts that corresponds to the required delay
	}
	Ru8_TCNT0 = (255-remainder);                      //Compensation of ticks remaining fraction to increase accuracy
	TIMER0_stop();
	counts = 0; 
}

void TIMER0_start(uint16_t u16_prescale)
{
	if (1 == u16_prescale)
	{
		Ru8_TCCR0 |= (1<<CS00);
	}
	else if (8 == u16_prescale)
	{
		Ru8_TCCR0 |= (1<<CS01);	
	}
	else if (32 == u16_prescale)
	{
		Ru8_TCCR0 |= (1<<CS01) | (1<<CS00);
	}
	else if (64 == u16_prescale)
	{
		Ru8_TCCR0 |= (1<<CS02);
	}
	else if (128 == u16_prescale)
	{
		Ru8_TCCR0 |= (1<<CS02) | (1<<CS00);
	}
	else if (256 == u16_prescale)
	{
		Ru8_TCCR0 |= (1<<CS02) | (1<<CS01);
	}
	else if (1024 == u16_prescale)
	{
		Ru8_TCCR0 |= (1<<CS02) | (1<<CS01) | (1<<CS00);
	}
}

void TIMER0_stop(void)
{
	Ru8_TCCR0 = 0;
}

void TIMER2_start(uint16_t u16_prescale)
{
	if (1 == u16_prescale)
	{
		Ru8_TCCR2 |= (1<<CS00);
	}
	else if (8 == u16_prescale)
	{
		Ru8_TCCR2 |= (1<<CS01);
	}
	else if (32 == u16_prescale)
	{
		Ru8_TCCR2 |= (1<<CS01) | (1<<CS00);
	}
	else if (64 == u16_prescale)
	{
		Ru8_TCCR2 |= (1<<CS02);
	}
	else if (128 == u16_prescale)
	{
		Ru8_TCCR2 |= (1<<CS02) | (1<<CS00);
	}
	else if (256 == u16_prescale)
	{
		Ru8_TCCR2 |= (1<<CS02) | (1<<CS01);
	}
	else if (1024 == u16_prescale)
	{
		Ru8_TCCR2 |= (1<<CS02) | (1<<CS01) | (1<<CS00);
	}
}

void TIMER2_stop(void)
{
	Ru8_TCCR2 = 0;
}
