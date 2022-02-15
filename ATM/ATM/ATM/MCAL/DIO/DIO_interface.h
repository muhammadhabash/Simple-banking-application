#ifndef _DIO_INTERFACE_H_
#define _DIO_INTERFACE_H_

#include "../../LIB/STD_types.h"
#include "../../LIB/ATMEGA32_registers.h"
#include "DIO_private.h"
                    /* DIO APIs deales with pins */
         uint8_t DIO_SetPinDirection(uint8_t PORT , uint8_t PIN , uint8_t DIRECTION);
         uint8_t DIO_SetPinValue(uint8_t PORT , uint8_t PIN , uint8_t VALUE);
         uint8_t DIO_TogPinValue(uint8_t PORT , uint8_t PIN);
         uint8_t DIO_TogPinDirection(uint8_t PORT , uint8_t PIN);
         uint8_t DIO_GetPinValue(uint8_t PORT,uint8_t PIN);

                     /* DIO APIs deales with ports */
        uint8_t DIO_SetPortDirection(uint8_t PORT , uint8_t DIRECTION);
        uint8_t DIO_SetPortValue(uint8_t PORT , uint8_t VALUE);
        uint8_t DIO_PULLUP(uint8_t PORT,uint8_t PIN);
        uint8_t DIO_GetPortValue(uint8_t PORT);




// DIO macros
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

/* pin direction*/
#define OUTPUT 1
#define INPUT  0

/* pin values*/
#define LOW  0
#define HIGH 1

/* Pin numbers*/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7


#endif /* DIO_INTERFACE_H_ */
