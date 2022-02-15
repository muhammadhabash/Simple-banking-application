#include "SPI_interface.h"
#include "../DIO/DIO_interface.h"
#include "../TIMERS/TIMERS.h"


void SPI_init(void){
	
	#if SPI_MODE == MASTER_MODE
	DIO_SetPinDirection(PORTB,SCK,OUTPUT);
	DIO_SetPinDirection(PORTB,MOSI,OUTPUT);
	DIO_SetPinDirection(PORTB,SS,OUTPUT);
	DIO_SetPinValue(PORTB,SS,HIGH);
	SPC_R |= (1 << SPE) | (1 << MSTR);
	
	#if SCK_FREQ_PRESCALE == PRESCALER_2
	SPC_R |= (1 << SPI2X);
	#elif SCK_FREQ_PRESCALE == PRESCALER_4
	SPC_R &= ~(1 << SPR0) & ~(1 << SPR1) & ~(1 << SPI2X);
	#elif SCK_FREQ_PRESCALE == PRESCALER_8
	SPC_R |= (1 << SPR0) | (1 << SPI2X);
	#elif SCK_FREQ_PRESCALE == PRESCALER_16
	SPC_R |= (1 << SPR0);
	#elif SCK_FREQ_PRESCALE == PRESCALER_32
	SPC_R |= (1 << SPR1) | (1 << SPI2X);
	#elif SCK_FREQ_PRESCALE == PRESCALER_64
	SPC_R |= (1 << SPR1);
	#elif SCK_FREQ_PRESCALE == PRESCALER_128
	SPC_R |= (1 << SPR1) | (1 << SPR0);
	#else
	#error "Invalid Clock Frequency Setting"
	#endif
	
	#if CLOCK_POLARITY == HIGH_WHEN_IDLE
	SPC_R |= (1 << CPOL);
	#elif CLOCK_POLARITY == LOW_WHEN_IDLE
	SPC_R &= ~(1 << CPOL);
	#else
	#error "Invalid Clock Polarity Setting"
	#endif
	
	#if DATA_SAMPLING == LEADING_EDGE
	SPC_R &= ~(1 << CPHA);
	#elif DATA_SAMPLING == TRAILING_EDGE
	SPC_R |= (1 << CPHA);
	#else
	#error "Invalid Data Sampling Setting"
	#endif
	
	#elif SPI_MODE == SLAVE_MODE
	DIO_SetPinDirection(PORTB,MISO,OUTPUT);
	SPC_R |= (1 << SPE);
	#else
	#error "Invalid Mode Setting"
	#endif
	
	#if SPI_INTERRUPT == ENABLE
	SPC_R    |= (1 << SPIE);
	STATUS_R |= (1 << GLOBAL_INTERRUPT);
	#elif SPI_INTERRUPT == DISABLE
	SPC_R    &=	~(1 << SPIE);
	STATUS_R &= ~(1 << GLOBAL_INTERRUPT);
	#else
	#error "Invalid Interrupt Setting"
	#endif
	
	#if DATA_ORDER == MSB_FIRST
	SPC_R &= ~(1 << DORD);
	#elif DATA_ORDER == LSB_FIRST
	SPC_R |= (1 << DORD);
	#else
	#error "Invalid Data Order Setting"
	#endif
}

uint8_t SPI_tranceiver(uint8_t u8_data){
	
	DIO_SetPinValue(PORTB,SS,LOW);
	SPD_R = u8_data;
	while(!(SPS_R & (1 << SPIF)));
	DIO_SetPinValue(PORTB,SS,HIGH);
	return SPD_R;
}

void SPI_masterTransmitString(uint8_t* u8_buffer){
	
	uint8_t u8_buffIndex = 0;
	
	do{
		SPI_tranceiver(u8_buffer[u8_buffIndex]);
		u8_buffIndex++;
	}while(u8_buffer[u8_buffIndex - 1] != '\0');
}

/*
uint8_t SPI_slaveReceiveByte(void)
{
	uint8_t u8_dummy;
	uint8_t u8_dataReceived;
	u8_dataReceived = SPI_tranceiver(u8_dummy);
	return u8_dataReceived;
}*/