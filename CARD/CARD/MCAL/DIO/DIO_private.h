#ifndef _DIO_PRIVATE_H_
#define _DIO_PRIVATE_H_

#define DDRA_REG   *(( uint8_t*)0x3A)
#define PORTA_REG  *(( uint8_t*)0x3B)
#define PINA_REG   *((volatile uint8_t*)0x39)

#define DDRB_REG   *(( uint8_t*)0x37)
#define PORTB_REG  *(( uint8_t*)0x38)
#define PINB_REG   *((volatile uint8_t*)0x36)

#define DDRC_REG   *(( uint8_t*)0x34)
#define PORTC_REG  *(( uint8_t*)0x35)
#define PINC_REG   *((volatile uint8_t*)0x33)

#define DDRD_REG   *(( uint8_t*)0x31)
#define PORTD_REG  *(( uint8_t*)0x32)
#define PIND_REG   *((volatile uint8_t*)0x30)




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



#endif /* DIO_PRIVATE_H_ */
