#include "../../LIB/STD_types.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "KEYPAD_private.h"


uint32_t Key_U8Delay(uint8_t au8_delayper_milli)
{

	uint32_t au32_delay_micro =(uint32_t) au8_delayper_milli *(uint32_t)1000;

	uint32_t au32_counter=0;
	 au32_counter = au32_delay_micro *8;
	 for(uint32_t au64_Local_counter =0 ;au64_Local_counter<(au32_counter/8) ;au64_Local_counter++)
	 {

	 }
	 return au32_counter ;
}

void Keyad_VoidINit(void){

		// DIO_SetPortDirection(PORTD ,0b00001111);
	      /*all rows inputs */
	DIO_SetPinDirection(PORTC ,PIN2 ,INPUT);
	DIO_SetPinDirection(PORTC ,PIN3 ,INPUT);
	DIO_SetPinDirection(PORTC ,PIN4 ,INPUT);
	DIO_SetPinDirection(PORTB ,PIN2 ,INPUT);

	        /*all columns are outputs*/
	DIO_SetPinDirection(PORTC ,PIN5 ,OUTPUT);
	DIO_SetPinDirection(PORTC ,PIN6 ,OUTPUT);
	DIO_SetPinDirection(PORTC ,PIN7 ,OUTPUT);
	DIO_SetPinDirection(PORTB ,PIN3 ,OUTPUT);
	          /*all output high*/
	 DIO_SetPinValue(PORTC , PIN5 , HIGH);
	 DIO_SetPinValue(PORTC , PIN6 , HIGH);
	 DIO_SetPinValue(PORTC , PIN7 , HIGH);
	 DIO_SetPinValue(PORTB , PIN3 , HIGH);
             /*pull up for inputs*/
	 DIO_SetPinValue(PORTC , PIN2 , HIGH);
	 DIO_SetPinValue(PORTC , PIN3 , HIGH);
	 DIO_SetPinValue(PORTC , PIN4 , HIGH);
	 DIO_SetPinValue(PORTB , PIN2 , HIGH);
}


uint8_t KeyPad_U8Data(void)
{
	uint8_t au8_Copy_Pressed_key=20;
	uint8_t au8_Copy_Colum;
	uint8_t au8_Copy_Row;
	for(au8_Copy_Colum=START_CO;au8_Copy_Colum<=MAX_CO;au8_Copy_Colum++)
	{
		   if(au8_Copy_Colum == 8 )
		   {
			   DIO_SetPinValue(PORTB , PIN3 , LOW);
		   }
		   else
		   {
		   DIO_SetPinValue(PORTC ,(au8_Copy_Colum), LOW);
		   }

		  for(au8_Copy_Row=START_ROW;au8_Copy_Row<=MAX_ROW; au8_Copy_Row++)
		  {

                   if(au8_Copy_Row <5)
                   {
			                if ((LOW == DIO_GetPinValue(PORTC,(au8_Copy_Row))) )
            				{
			                	Key_U8Delay(40);

			                	while((LOW == DIO_GetPinValue(PORTC,au8_Copy_Row )));

            	           	    return g_keymap[au8_Copy_Row-2][au8_Copy_Colum-5];

            				}
			                else
			                {/*for MEZRARULE */};
                   }
                   else
                   {
  			             if ( ( LOW== DIO_GetPinValue(PORTB,PIN2) ) )
  			             {
  			            	 Key_U8Delay(20);
              	             while((LOW == DIO_GetPinValue(PORTB,PIN2 ) ))
              	           	   // DIO_SetPinValue(PORTB , PIN3 , HIGH);
              		    	 return g_keymap[au8_Copy_Row-2][au8_Copy_Colum-5];
  			             }
  			             else
  			             {/*for MEZRARULE */};
                   }

		  }
		  if(au8_Copy_Colum == 8 )
		  {
			  DIO_SetPinValue(PORTB , PIN3 , HIGH);
		  }
		  else
		  {
			  DIO_SetPinValue(PORTC ,(au8_Copy_Colum), HIGH);
		  }
	   }

	return au8_Copy_Pressed_key;
}


