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
#define DDRB_OCA0 (*(volatile uint8_t *)(0x24))
#define DDRG_OCB0 (*(volatile uint8_t *)(0x33))



/*===============================================================================
 * TIMER0 Private Macros
 *===============================================================================
 * TIMER0 Initial state
 *======================================================*/
 #define TIMER0_TIMER_START           1
 #define TIMER0_TIMER_STOP            0
 /*======================================================
 *  TIMER0 Enable Interrupt
 *======================================================*/
  #define TIMER0_INT_ENABLED      1
  #define TIMER0_INT_DISABLED     0
/*======================================================
 *  TIMER0 Register Resolution
 *======================================================*/
 #define TIMER0_REG_CAPACITY      256
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
 * TIMER0 Modes
 *======================================================*/
 #define TIMER0_NORMAL_MODE       0
 #define TIMER0_CTC_MODE          1
 #define TIMER0_FAST_PWM_MODE     2
 #define TIMER0_PHASE_CORCT_MODE  3

/*======================================================
 * TIMER0 Channels
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

#define TIMER0_WGM00			 0
#define TIMER0_WGM01             1
#define TIMER0_WGM02			 3
/*======================================================
 * TIMSK2
 *======================================================*/
#define TIMER0_TOIE0              0
#define TIMER0_OCIE0A             1
#define TIMER0_OCIE0B             2
/*======================================================
 * TIFR2
 *======================================================*/
#define OCF0B					  2
#define OCF0A					  1
#define TOV0					  0


/*value to be masked with TCNT0 to stop register counting
 *===============================================================================*/
#define TIMER0_STOP_MASK          0xf8
/*value to be masked with COM Bits
 *===============================================================================*/
#define TIMER0_COM_MASK           0b00001111
/*value to be masked with TCCR0 Reg to clear first 3 bits
 *===============================================================================*/
#define TIMER0_TCCR0A_MASK         0xf8
#define TIMER0_TCCR0B_MASK         0xf8



/*===============================================================*/
/*OC0 Non PWM Modes*/
/*===============================================================*/

#define TIMER0_DISCONNECT_OC0      0
#define TIMER0_TOGGLE_OC0          1
#define TIMER0_CLEAR_OC0           2
#define TIMER0_SET_OC0             3

/*===============================================================*/
/*OC0 PWM Modes*/
/*===============================================================*/

#define TIMER0_PWM_NONINVERTED_OC0 2
#define TIMER0_PWM_INVERTED_OC0    3




/*===============================================================================
* TIMER0 Registers Addresses
*===============================================================================*/
#define TIMSK0 (*(volatile uint8_t *)(0x6E)) /*Timer interrupt control Reg*/
#define TCCR0A (*(volatile uint8_t *)(0x44)) /*Register TCCR0 (TIMER0 Control Reg)*/
#define TCCR0B (*(volatile uint8_t *)(0x45)) /*Register TCCR0 (TIMER0 Control Reg)*/
#define TCNT0 (*(volatile uint8_t *)(0X46)) /*Register TCNT0 (Timer 2 Reg)*/
#define OCR0A  (*(volatile uint8_t *)(0X47)) /*Register OCR0  (Output compare 0 Reg)*/
#define OCR0B  (*(volatile uint8_t *)(0X48)) /*Register OCR0  (Output compare 0 Reg)*/
#define TIFR0  (*(volatile uint8_t *)(0x35)) /*Register TIFR  (Flag Reg)*/




#endif /* MCAL_TIMER_TIMER_PRIVAE_H_ */
