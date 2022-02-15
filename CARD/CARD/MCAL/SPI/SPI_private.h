#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#include "../../LIB/ATMEGA32_registers.h"

/******************************************/
/*        SPI Control Register Bits       */
/******************************************/

#define SPR0 (0)
#define SPR1 (1)
#define CPHA (2)
#define CPOL (3)
#define MSTR (4)
#define DORD (5)
#define SPE  (6)
#define SPIE (7)

/*******************************************/
/*         SPI Status Register Bits        */
/*******************************************/

#define SPI2X (0)
#define WCOL  (6)
#define SPIF  (7)

/*******************************************/
/*                 SPI Pins                */
/*******************************************/

#define SCK   (7)
#define MISO  (6)
#define MOSI  (5)
#define SS    (4)

#define GLOBAL_INTERRUPT (7)
/*******************************************/
/*           SPI Configurations            */
/*******************************************/

#define MSB_FIRST      (10)
#define LSB_FIRST      (11)
#define MASTER_MODE    (12)
#define SLAVE_MODE     (13)
#define HIGH_WHEN_IDLE (14)
#define LOW_WHEN_IDLE  (15)
#define LEADING_EDGE   (16)
#define TRAILING_EDGE  (17)
#define PRESCALER_4    (18)
#define PRESCALER_16   (19)
#define PRESCALER_64   (20)
#define PRESCALER_128  (21)
#define PRESCALER_2    (22)
#define PRESCALER_8    (23)
#define PRESCALER_32   (24)
#define DISABLE        (25)
#define ENABLE         (26)


/********************************************/
/*                 SPI APIs                 */
/********************************************/


uint8_t SPI_tranceiver(uint8_t u8_data);



#endif