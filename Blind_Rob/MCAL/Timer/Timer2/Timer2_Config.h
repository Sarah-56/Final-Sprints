/*
 * timer2.h
 *
 *  Created on: Oct 13, 2021
 *      Author: ah132
 */

#ifndef MCAL_TIMER_TIMER2_CONFIG_H_
#define MCAL_TIMER_TIMER2_CONFIG_H_

typedef enum{
	Channel_A2, Channel_B2
}Channal_t;

/*
 * Notes :
 * ======================================
 * - F_CPU and prescaler will determine PWM Frequency configure them accordingly
 *
 * - you can configure Timer2 in Normal mode and CTC mode in 2 ways:
 *   using Timer2_voidSetDesiredTime_ms() function or by configuring F_CPU and prescaler to set desired time
 *
 * - in CTC mode using Timer2_voidSetDesiredTime_ms() is limited by OCR Max value 256
 *   and Maximun generated time is Tick time * 256 if inputed a larger number fn will not work properly
 *
 * - Timer2_voidSetDesiredTime_us() acurecy decreas below 200 us
 */

#ifndef F_CPU
/*MCU Clock frequency*/
#define F_CPU           8000000UL
#endif
/*
 * Choose prescaler from
 *  - No_Prescaller
 *  - Prescaller_8
 *  - Prescaller_64
 *  - Prescaller_256 -
 *  - Prescaller_1024
 *  - Prescaller_FalExtClk
 *  - Prescaller_RaisExtClk
 *  These two options are used with counter option
 * 	- Prescaller_FalExtClk
 * 	- Prescaller_RaisExtClk
 */
#define TIMER2_PRESCALER       Prescaller_1024

/*
 * Choose Mode :
 *  - TIMER2_NORMAL_MODE
 *  - TIMER2_CTC_MODE
 *  - TIMER2_FAST_PWM_MODE
 *  - TIMER2_PHASE_CORCT_MODE
 */
#define TIMER2_MODE            TIMER2_FAST_PWM_MODE

/*
 * Timers interrupt initial status :
 *  - TIMER2_INT_ENABLED
 *  - TIMER2_INT_DISABLED
 */
#define TIMER2_INTERRUPT_STATUS   TIMER2_INT_DISABLED


#define Timer2_ChannalA		CHANNAL_A_EN
#define Timer2_ChannalB		CHANNAL_B_EN
/*
 * Choose Timer2 OC2 Mode :
 * + with PWM modes:
 *   -  Timer2_DISCONNECT_OC2
 *   -  Timer2_PWM_NONINVERTED_OC2
 *   -  Timer2_PWM_INVERTED_OC2
 * + with non PWM Modes:
 *   -  TIMRE2_DISCONNECT_OC2
 *   -  TIMER2_TOGGLE_OC2
 *   -  TIMER2_CLEAR_OC2
 *   -  TIMER2_SET_OC2
 */
//#define Timer2_OC2_MODE   Timer2_PWM_NONINVERTED_OC2
#define Timer2_OC2A_MODE   TIMER2_PWM_NONINVERTED_OC2
#define Timer2_OC2B_MODE   TIMER2_PWM_NONINVERTED_OC2


/*OCR2A Initial Value*/
#define TIMER2_OCR2A_VALUE  155

/*OCR2B Initial Value*/
#define TIMER2_OCR2B_VALUE  0

#endif /* MCAL_TIMER_TIMER2_CONFIG_H_ */
