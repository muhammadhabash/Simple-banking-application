#ifndef LCD_H_
#define LCD_H_
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMERS/TIMERS.h"
#include "../../LIB/ATMEGA32_registers.h"
#include <math.h>

#define RS (PIN1)
#define RW (PIN2)
#define EN (PIN3)
#define D4 (PIN4)
#define D5 (PIN5)
#define D6 (PIN6)
#define D7 (PIN7)

#define FOUR_BITS_MODE        (0x20)
#define DISPLAY_CLEAR         (0x01)
#define DISPLAY_CURSOR_ON     (0x0E)
#define ENTRY_MODE            (0x06)
#define DISPLAY_ON_CURSOR_OFF (0x0C)
#define LEFT                  (0x10)
#define RIGHT                 (0x14)
#define DATA_REGISTER         (Ru8_PORTA)
#define u8_LCD_INTIAL_VAL	  (0)

void LCD_init();
void LCD_command(uint8_t u8_command);
void LCD_data(uint8_t u8_data);
void LCD_printString(uint8_t* stream);
void LCD_printDigits(uint32_t u32_number);
void LCD_cursorMove(uint8_t u8_direction, uint8_t u8_numOfMoves);
void LCD_newLine(void);


#endif
