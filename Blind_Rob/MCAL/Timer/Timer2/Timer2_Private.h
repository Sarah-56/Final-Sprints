/*
 * Timer_Privae.h
 *
 *  Created on: Oct 13, 2021
 *      Author: ah132
 */

#ifndef MCAL_TIMER_TIMER_PRIVAE_H_
#define MCAL_TIMER_TIMER_PRIVAE_H_
#include "../../../Utils/std_types.h"
#include "../../../Utils/common_macros.h"

/* For Global Interrupt */
#ifndef INTERRUPT
#define INTERRUPT
# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)
#endif


#define DDRB_OC2A	(*(volatile uint8_t *)(0x24))
#define DDRH_OC2B	(*(volatile uint8_t *)(0x101))

/*===============================================================================
 * Timer2 Private Macros
 *===============================================================================
 * Timer2 Initial state
 *======================================================*/
 #define TIMER2_TIMER_START           1
 #define TIMER2_TIMER_STOP            0
 /*======================================================
 *  Timer2 Enable Interrupt
 *======================================================*/
  #define TIMER2_INT_ENABLED      1
  #define TIMER2_INT_DISABLED     0
/*======================================================
 *  Timer2 Register Resolution
 *======================================================*/
 #define TIMER2_REG_CAPACITY      256
/*======================================================
 *Prescaler Macros
 *======================================================*/
 #define No_Prescaller             1
 #define Prescaller_8              2
 #define Prescaller_64             3
 #define Prescaller_256            4
 #define Prescaller_1024           5
 #define Prescaller_FalExtClk      6
 #define Prescaller_RaisExtClk     7
/*======================================================
 * Timer2 Modes
 *======================================================*/
 #define TIMER2_NORMAL_MODE       0
 #define TIMER2_CTC_MODE          1
 #define TIMER2_FAST_PWM_MODE     2
 #define TIMER2_PHASE_CORCT_MODE  3
 #define Prescaller_RaisExtClk     7
/*======================================================
 * Timer2 Channels
 *======================================================*/
#define CHANNAL_A_EN	1
#define CHANNAL_B_EN	1
#define CHANNAL_A_DIS	0
#define CHANNAL_B_DIS	0

/*===============================================================================*/
/* Time2 Registers Pins*/
/*===============================================================================
 * TCCR2 Register pins
 *======================================================*/

#define TIMER2_WGM20			 0
#define TIMER2_WGM21             1
#define TIMER2_WGM22			 3
#define TIMER2_FOC2A			 7
/*======================================================
 * TIMSK2
 *======================================================*/
#define TIMER2_TOIE2              0
#define TIMER2_OCIE2A             1
#define TIMER2_OCIE2B             2
/*======================================================
 * TIFR2
 *======================================================*/
#define OCF2B					  2
#define OCF2A					  1
#define TOV2					  0


/*value to be masked with TCNT0 to stop register counting
 *===============================================================================*/
#define TIMER2_STOP_MASK          0xf8
/*value to be masked with COM Bits
 *===============================================================================*/
#define TIMER2_COM_MASK           0b00001111
/*value to be masked with TCCR0 Reg to clear first 3 bits
 *===============================================================================*/
#define TIMER2_TCCR2A_MASK         0xf8
#define TIMER2_TCCR2B_MASK         0xf8



/*===============================================================*/
/*OC0 Non PWM Modes*/
/*===============================================================*/

#define TIMER2_DISCONNECT_OC2      0
#define TIMER2_TOGGLE_OC2          1
#define TIMER2_CLEAR_OC2           2
#define TIMER2_SET_OC2             3

/*===============================================================*/
/*OC0 PWM Modes*/
/*===============================================================*/

#define TIMER2_PWM_NONINVERTED_OC2 2
#define TIMER2_PWM_INVERTED_OC2    3








/*===============================================================================
* Timer2 Registers Addresses
*===============================================================================*/
#define TIMSK2 	(*(volatile uint8_t *)(0x70)) /*Timer interrupt control Reg*/
#define TCCR2A 	(*(volatile uint8_t *)(0xB0))
#define TCCR2B 	(*(volatile uint8_t *)(0xB1))
#define TCNT2 	(*(volatile uint8_t *)(0xB2))
#define OCR2A  	(*(volatile uint8_t *)(0xB3)) /*Register OCR0  (Output compare 0 Reg)*/
#define OCR2B  	(*(volatile uint8_t *)(0xB4)) /*Register OCR0  (Output compare 0 Reg)*/
#define TIFR2  	(*(volatile uint8_t *)(0x37)) /*Register TIFR  (Flag Reg)*/

#endif /* MCAL_TIMER_TIMER_PRIVAE_H_ */
