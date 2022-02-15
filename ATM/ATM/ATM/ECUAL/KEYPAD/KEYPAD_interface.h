#ifndef __KEYPAD__INTERFACE__
#define __KEYPAD__INTERFACE__

#define u8_KEYPAD_NOT_PRESSED 	20

void Keyad_VoidINit(void);
uint8_t KeyPad_U8Data (void);
uint32_t Key_U8Delay(uint8_t au8_delayper_milli);

#endif
