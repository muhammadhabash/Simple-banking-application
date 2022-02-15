#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_
#include "../../LIB/STD_types.h"

#define  F_CPU 8000000UL



#define BUAD_RATE (9600) /*SET BUAD RATE*/




#define UART_COTR_STATUS_REGB                         Ru8_UCSRB
#define UART_BUAD_RATE_REG_HIGH_value                 Ru8_UBRRH_UCSRC
#define UART_BUAD_RATE_REG_LOW_value                  Ru8_UBRRL
#define UART_COTR_STATUS_REGC                         Ru8_UBRRH_UCSRC
#define UART_COTR_STATUS_REGA                         Ru8_UCSRA
#define UART_COTR_STATUS_REGB                         Ru8_UCSRB
#define UART_UART_BUFFER_REG						  Ru8_UDR


#define TXB8    0
#define RXB8    1
#define UCSZ2   2
#define TXEN    3
#define RXEN    4
#define UDRIE   5
#define TXCIE   6
#define RXCIE   7

#define MPCM    0
#define U2X     1
#define UPE     2
#define DOR     3
#define FE      4
#define UDRE    5
#define TXC     6
#define RXC     7

#define UCPOL   0
#define UCSZ0   1
#define UCSZ1   2
#define USBS    3
#define UPM0    4
#define UPM1    5
#define UMSEL   6
#define URSEL   7

extern uint16_t  MYUBRR;
 


enum USART_SYNCH_MODE_{
	USART_ASYNCH_MODE,
	USART_SYNCH_MODE =(1<<6)      /*Bit 6 – UMSEL: USART Mode Select*/
};

enum USART_SPEED_MODE{
	USART_NORMAL_SPEED,
	USART_DOUBLE_SPEED
};
enum USART_TX{
	USART_TX_DISABLE,
	USART_TX_ENABLE
};
enum USART_RX{
	USART_RX_DISABLE,
	USART_RX_ENABLE
};
enum USART_DATA_FORMAT{
	USART_DATA_FORMAT_5BIT_MODE =(0x0<<1),
	USART_DATA_FORMAT_6BIT_MODE =(0x1<<1),
	USART_DATA_FORMAT_7BIT_MODE =(0x2<<1),
	USART_DATA_FORMAT_8BIT_MODE =(0x3<<1)
};

enum USART_PARITY_MODE{
	USART_PARITY_DISABLE =(0x00<<4),
	USART_PARITY_MODE_EVEN   =(0x01<<4),
	USART_PARITY_MODE_ODD   =(0x11<<4)
	
};
enum USART_STOP_BITS_NUM{
	USART_1_STOP_BIT =(0x0<<3),
	USART_2_STOP_BITS =(0x1<<3)
};
enum USART_TX_INTERRUPT{
	USART_TX_INTERRUPT_DISABLE=(0<<6),
	USART_TX_INTERRUPT_ENABLE=(1<<6)
	
};
enum USART_RX_INTERRUPT{
	USART_RX_INTERRUPT_DISABLE= (0<<7),
	USART_RX_INTERRUPT_ENABLE= (1<<7)
};
/*Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable*/
enum USART_UDR_INTERRUPT{
	USART_UDR_INTERRUPT_DISABLE= (0<<5),
	USART_UDR_INTERRUPT_ENABLE= (1<<5)
	};

struct gstr_USART_Config_t{
	enum USART_SYNCH_MODE_          SYNCH_MODE;
	enum USART_SPEED_MODE           SPEED_MODE;
	enum USART_TX                   TX_;
	enum USART_RX                   RX_;
	enum USART_DATA_FORMAT          CHAR_SIZE;
	enum USART_PARITY_MODE          PARITY_MODE;
	enum USART_STOP_BITS_NUM        STOP_BITS_NUM;
	enum USART_TX_INTERRUPT         TX_INTERRUPT;
	enum USART_RX_INTERRUPT         RX_INTERRUPT;
	enum USART_UDR_INTERRUPT        UDR_INTERRUPT;
};


void (*ptr_To_TX_Int_fun)(void);
void (*ptr_To_RX_Int_fun)(void);


/***********************************************************************************************************
									funs prototypes															*
*************************************************************************************************************/
void USART_voidInit(struct gstr_USART_Config_t *USART_PRE_CONFIGRATION);
void USART_voidTransmit( uint8_t data );
uint8_t USART_u8Receive(void);
void USART_voidSendString (uint8_t *Packet_Send_Buffer );
void USART_voidRecieveString (uint8_t *Packet_Receive_Buffer );
void USART_voidRecievePacket (uint8_t *Packet_Receive_Buffer ,uint8_t u8_arrSize ,uint8_t Tail_Byte);
void USART_voidSendPacket(volatile uint8_t *str,uint8_t Stop_Byte);
void USART_voidReceiveByteIterrupt(volatile uint8_t *Byte_Address);
void USART_RX_Int_CallBack_fun(void (*ptr_To_Fun)(void));
void USART_TX_Int_CallBack_fun(void (*ptr_To_Fun)(void));






#endif /* UART_CONFIG_H_ */
