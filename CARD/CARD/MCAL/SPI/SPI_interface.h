#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "SPI_private.h"

#define SPI_INTERRUPT     (DISABLE)

#define DATA_ORDER        (MSB_FIRST)

#define SPI_MODE          (MASTER_MODE)

#define CLOCK_POLARITY    (LOW_WHEN_IDLE)

#define DATA_SAMPLING     (LEADING_EDGE)

#define SCK_FREQ_PRESCALE (PRESCALER_128)

void SPI_init(void);
void SPI_masterTransmitString(uint8_t* u8_buffer);
//uint8_t SPI_slaveReceiveByte(void);



#endif