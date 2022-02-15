#ifndef TIMERS_H_
#define TIMERS_H_

#include "../../LIB/BIT_math.h"
#include "../../LIB/ATMEGA32_registers.h"

/****************************************************************************/
/*                                                                          */
/*                        TIMER0 Control Register Bits                      */
/*                                                                          */
/****************************************************************************/

#define CS00  (0)
#define CS01  (1)
#define CS02  (2)
#define WGM01 (3)
#define COM00 (4)
#define COM01 (5)
#define WGM00 (6)
#define FOC0  (7)

/****************************************************************************/
/*                                                                          */
/*                        TIMER2 Control Register Bits                      */
/*                                                                          */
/****************************************************************************/

#define CS20  (0)
#define CS21  (1)
#define CS22  (2)
#define WGM21 (3)
#define COM20 (4)
#define COM21 (5)
#define WGM20 (6)
#define FOC2  (7)
 
 /****************************************************************************/
 /*                                                                          */
 /*                        TIMER2 Asynchronous Register Bits                 */
 /*                                                                          */
 /****************************************************************************/
 
 #define TCR2UB (0)
 #define OCR2UB (1)
 #define TCN2UB (2)
 #define AS2    (3)
 
/****************************************************************************/
/*                                                                          */
/*                   Timers Interrupt Flag Register Bits                    */
/*                                                                          */
/****************************************************************************/

#define TOV0  (0)
#define OCF0  (1)
#define TOV1  (2)
#define OCF1B (3)
#define OCF1A (4)
#define ICF1  (5)
#define TOV2  (6)
#define OCF2  (7)

/****************************************************************************/
/*                                                                          */
/*                   Timers Interrupt Masking Register Bits                 */
/*                                                                          */
/****************************************************************************/

#define TOIE0  (0)
#define OCIE0  (1)
#define TOIE1  (2)
#define OCIE1B (3)
#define OCIE1A (4)
#define TICIE1 (5)
#define TOIE2  (6)
#define OCIE2  (7)

/****************************************************************************/
/*                                                                          */
/*                            Functions Prototypes                          */
/*                                                                          */
/****************************************************************************/

void OVI0_init     (void);
void OCI0_init     (void);
void OVI2_init     (void);
void OCI2_init     (void);
void TIMER0_start  (uint16_t u16_prescale);
void TIMER0_stop   (void);
void TIMER2_start  (uint16_t u16_prescale);
void TIMER2_stop   (void);
void TIMER0_msdelay(uint16_t mseconds);


#endif
