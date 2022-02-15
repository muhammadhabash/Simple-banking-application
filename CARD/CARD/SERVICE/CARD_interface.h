#ifndef CARD_INTERFACE_H_
#define CARD_INTERFACE_H_

#define TRUE                     (1)
#define FALSE                    (0)
#define PROGRAMMING_MODE         (1)
#define USER_MODE                (2)
#define ASTERISK		         (0x2A)
#define u8_EQUAL_STR	         (0)
#define u8_PAN_PAGE_NUM	         (0)
#define u8_PAN_BYTE_NUM	         (0)
#define u8_PIN_PAGE_NUM	         (0)
#define u8_PIN_BYTE_NUM	         (20)
#define u8_PAN_MAX_SIZE		     (17)
#define u8_PAN_MIN_SIZE          (9)
#define u8_PIN_SIZE		         (5)
#define u8_NEEDED_DATA_SIZE	     (15)
#define u8_CARD				     ('A')
#define u8_CARD_INTIAL_VAL	     (5)
#define u8_INTIAL_VAL		     (0)
#define u8_OUTSIDE_ATM		     (20)
#define u8_INSIDE_ATM		     (21)
#define u8_END_OF_TRANSACTION    (22)
#define u8_REQ_PAN			     (50)
#define u8_PAN_VALID			 (51)
#define u8_PAN_INVALID			 (52)
#define u8_REQ_PIN				 (53)
#define u8_PIN_VALID			 (54)
#define u8_PIN_INVALID           (55)
#define u8_SENT_DONE			 (56)
#define u8_REQ_RECEIVED			 (57)
#define u8_PAN_VALID_RECEIVED	 (58)
#define u8_PAN_INVALID_RECEIVED	 (59)
#define PROG_MODE_STR            (uint8_t*)"Programming mode accessed\r"
#define PAN_REQ_STR              (uint8_t*)"Enter PAN: "
#define WRONG_PAN_STR            (uint8_t*)"Wrong PAN!!!\r"
#define PIN_REQ_STR              (uint8_t*)"Enter PIN: "
#define WRONG_PIN_STR            (uint8_t*)"Wrong PIN!!!\r"
#define USER_MODE_STR            (uint8_t*)"User mode accessed\r"

typedef enum
{
	ADMIN,
	USER
}cardMode_t;

void CARD_init(void);
void TERMINAL_init(void);
void TERMINAL_display(uint8_t* pu8_stream);
void TERMINAL_command(uint8_t* pu8_buffer, uint8_t u8_arrSize);
void CARD_voidCheckPanValidity(uint8_t* pu8_cardPAN, uint8_t* u8_panSize);
void CARD_voidCheckPinValidity(uint8_t* pu8_cardPIN);
uint8_t CARD_u8ModeSelection(void);

void CARD_sendBufferState(uint8_t pu8_bufferSent);
void CARD_sendInfoString(uint8_t* pu8_bufferSent );
uint8_t CARD_geTCardState(void);

#endif