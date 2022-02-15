#ifndef ATM_INTERFACE_H_
#define ATM_INTERFACE_H_

#include "../LIB/STD_types.h"
#define u8_MAX_PIN_INDEX_ARR			 3
#define ATM_TRUE                         1
#define ATM_FALSE                        0
#define u8_CARD_PRESSED					'#'
#define ASTERISK				   		 0x2A
#define u8_EQUAL_STR					 0
#define ADMIN_PASS                       "1234"
#define u8_PAN_BYTE_NUM				  	 0
#define u8_BALANCE_BYTE_NUM              20
#define u8_MAX_TRIALS                    3
#define u8_MAX_BALANCE					 (uint8_t*)"500000"
#define u8_MAX_BALANCE_MAX_SIZE          7
#define u8_MAX_BALANCE_MIN_SIZE          7
#define u8_MAX_BALANCE_PAGE_NUM			 510
#define u8_MAX_BALANCE_BYTE_NUM			 25
#define u8_RECORDS_PAGE_NUM			 	 510
#define u8_RECORDS_FIRST_BYTE_NUM		 35
#define u8_RECORDS_SECOND_BYTE_NUM        36      
#define u8_PAN_MAX_SIZE		     (17)
#define u8_PAN_MIN_SIZE          (9)
#define u8_PIN_SIZE						 5
#define u8_OPTION_SIZE                   3
#define u8_BALANCE_MAX_SIZE              9
#define u8_BALANCE_MIN_SIZE              2
#define u8_ADMIN_PASS_SIZE               5
#define u8_INTIAL_VAL					 0
#define u8_OUTSIDE_ATM					 20
#define u8_INSIDE_ATM					 21
#define u8_END_OF_TRANSACTION			 22
#define u8_REQ_PAN						 50
#define u8_PAN_VALID			     	 51
#define u8_PAN_INVALID			       	 52
#define u8_REQ_PIN				 	 	 53
#define u8_PIN_VALID			  	     54
#define u8_PIN_INVALID                  (55)
#define u8_SENT_DONE			        (56)
#define u8_REQ_RECEIVED			        (57)
#define u8_USER_ENTERED_AMOUNT_NUMBERS	 6
#define	u8_USER_WANTED_AMOUNT_ARR_SIZE	 7
#define u8_MAX_TIMES_WRONG_AMOUNT		 3
#define u8_BALANCE_NOT_VALID			 0
#define u8_BALANCE_VALID			 	 1

#define u8_EMPTY                         0
#define NEW_REC                          0x31
#define SET_MAX_BAL                      0x32
#define EXIT                             0x33
#define u8_MAX_ENTERED_PIN_TIMES 		 3
#define u8_MAX_TEMP						 35
#define ADMIN_MODE_STR                   (uint8_t*)"\r1- For programming mode type ADMIN\r"
#define USER_MODE_STR                    (uint8_t*)"\r2- For user mode type USER \r"
#define PROG_FIRST_STATE_STR             (uint8_t*)"Server is Empty. You are now in admin mode\r"
#define REQUIRE_PASS_STR                 (uint8_t*)"Enter Password: "
#define WRONG_PASS_STR                   (uint8_t*)"WRONG PASSWORD\r"
#define NEW_REC_STR                      (uint8_t*)"\r1 - Enter new record\r"
#define MAX_BAL_STR                      (uint8_t*)"2 - Enter max balance\r"
#define EXIT_STR                         (uint8_t*)"3 - Exit\r"
#define CHOICE_STR                       (uint8_t*)"Choice: "
#define NO_REC_TO_EXIT_STR               (uint8_t*)"\rPlease enter at least one record to exit"
#define WRONG_CHOICE_STR       		     (uint8_t*)"WRONG CHOICE!!!\r"
#define WRONG_PAN_STR					 (uint8_t*)"WRONG PAN!!!\r"
#define REQUIRE_PAN_STR					 (uint8_t*)"\rEnter PAN: "
#define ENTER_BAL_STR				     (uint8_t*)"\rEnter balance: "
#define REQUIRE_MAX_BAL_STR				 (uint8_t*)"\rEnter Max Balance: "
#define WRONG_MAX_BAL_STR				 (uint8_t*)"WRONG BALANCE!!!\r"
#define LCD_INSERT_CARD_STR				 (uint8_t*)"1-Insert Card"
#define LCD_SHOW_TEMP_OPTION_STR		 (uint8_t*)"2-Temp"
#define LCD_EXIT_OPTION_STR              (uint8_t*)"3-Exit"
#define ADMIN_STR						 (uint8_t*)"ADMIN"
#define USER_STR						 (uint8_t*)"USER"
#define LCD_ENTER_CARD_STR				 (uint8_t*)"Enter Card"
#define PROCESS_WAIT_STR				 (uint8_t*)"Processing.."
#define LCD_REQUIRE_PIN_STR 			 (uint8_t*)"Enter pin"
#define LCD_WRONG_PIN_STR				 (uint8_t*)"Wrong pin "
#define LCD_REQUIRE_USER_BAL_STR		 (uint8_t*)"wanted Balance:"
#define LCD_REQUIRED_SAMPLE_BAL_STR		 (uint8_t*)"XXXX.XX"
#define LCD_EXIT_TO_MAIN_STR			 (uint8_t*)"1-EXIT"
#define LCD_SHOW_TEMP_STR				 (uint8_t*)"Temp now: "
#define LCD_WAIT_CASH_STR				 (uint8_t*)"Please wait cash"

typedef enum{
	USER ,
	ADMIN
}ATM_modes;

void ATM_Init(void) ;
void TERMINAL_init(void);
void TERMINAL_display(uint8_t* u8_stream);
void TERMINAL_command(uint8_t* u8_buffer, uint8_t u8_arrSize);
uint8_t TERMINAL_u8getInput(uint8_t* pu8_inputBuff, uint8_t u8_maxBuffSize, uint8_t u8_minBuffSize);
uint8_t ACCESS_grant(void);
uint8_t ATM_u8getArrCount(uint8_t* pu8_inputBuff) ;
uint8_t ATM_panValidity(uint8_t* pu8_panWantedBuffer,uint16_t* pu16_wantedPanRecordnum) ;
void ATM_voidstoreBalance(uint8_t* pu8_newRecBal,uint8_t* pu8_tempRecBal,uint8_t u8_digitsCount) ;
void ATM_voidlcdUserInterface(void) ;
uint8_t ATM_u8PinAccessGrant(uint8_t* pu8_cardPin) ;
uint8_t ATM_u8checkBalanceValidity(uint8_t* pu8_userInputBal) ;
void ATM_voidShowTemp(void) ;
void ATM_voidGetCash(void) ;
uint8_t ATM_u8checkAccounBal(uint8_t* pu8_balanceWanted,uint8_t* pu8_returnUserBal,uint16_t u16_RecNum) ;
void ATM_voidStoreRecNum(uint16_t u16_recNum);
uint16_t ATM_u16GetRecNum(void);


#endif
