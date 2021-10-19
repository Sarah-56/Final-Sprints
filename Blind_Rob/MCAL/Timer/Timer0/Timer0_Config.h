/*
 * Timer0_Config.h
 *
 *  Created on: Oct 13, 2021
 *      Author: ah132
 */

#ifndef MCAL_TIMER_TIMER0_CONFIG_H_
#define MCAL_TIMER_TIMER0_CONFIG_H_


typedef enum{
	Channel_A, Channel_B
}Channal;

/*
 * Notes :
 * ======================================
 * - F_CPU and prescaler will determine PWM Frequency configure them accordingly
 *
 * - you can configure TIMER0 in Normal mode and CTC mode in 2 ways:
 *   using TIMER0_voidSetDesiredTime_ms() function or by configuring F_CPU and prescaler to set desired time
 *
 * - in CTC mode using TIMER0_voidSetDesiredTime_ms() is limited by OCR Max value 256
 *   and Maximun generated time is Tick time * 256 if inputed a larger number fn will not work properly
 *
 * - TIMER0_voidSetDesiredTime_us() acurecy decreas below 200 us
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
#define TIMER0_PRESCALER       Prescaller_1024

/*
 * Choose Mode :
 *  - TIMER0_NORMAL_MODE
 *  - TIMER0_CTC_MODE
 *  - TIMER0_FAST_PWM_MODE
 *  - TIMER0_PHASE_CORCT_MODE
 */
#define TIMER0_MODE            TIMER0_FAST_PWM_MODE

/*
 * Timers interrupt initial status :
 *  - TIMER0_INT_ENABLED
 *  - TIMER0_INT_DISABLED
 */
#define TIMER0_INTERRUPT_STATUS   TIMER0_INT_DISABLED


#define TIMER0_ChannalA		CHANNAL_A_EN
#define TIMER0_ChannalB		CHANNAL_B_EN
/*
 * Choose TIMER0 OC0 Mode :
 * + with PWM modes:
 *   -  TIMER0_DISCONNECT_OC0
 *   -  TIMER0_PWM_NONINVERTED_OC0
 *   -  TIMER0_PWM_INVERTED_OC0
 * + with non PWM Modes:
 *   -  TIMRE2_DISCONNECT_OC0
 *   -  TIMER0_TOGGLE_OC0
 *   -  TIMER0_CLEAR_OC0
 *   -  TIMER0_SET_OC0
 */
//#define TIMER0_OC0_MODE   TIMER0_PWM_NONINVERTED_OC0
#define TIMER0_OC0A_MODE   TIMER0_PWM_NONINVERTED_OC0
#define TIMER0_OC0B_MODE   TIMER0_PWM_NONINVERTED_OC0



/*OCR2A Initial Value*/
#define TIMER0_OCR0A_VALUE  155

/*OCR2B Initial Value*/
#define TIMER0_OCR0B_VALUE  0

#endif /* MCAL_TIMER_TIMER0_CONFIG_H_ */
