/*
 * Timer_Interface.h
 *
 *  Created on: Oct 13, 2021
 *      Author: ah132
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_
#include "../../../Utils/std_types.h"
#include "Timer2_Config.h"
#include "Timer2_Private.h"






/*==================================================================================================================
 * timer2 Modules
 *==================================================================================================================*/


/*
 * Prototype   : void TIMER2_voidStartTimer(void);
 * Description : Start timer2 counter register
 * Arguments   : void
 * return      : void
 */
 void TIMER2_voidStartTimer(void);

/*
 * Prototype   : void TIMER2_voidStopTimer(void);
 * Description : Stop timer2 counter register
 * Arguments   : void
 * return      : void
 */
 void TIMER2_voidStopTimer(void);

/*
 * Prototype   : void TIMER2_voidInitializetimer2(void);
 * Description : Initialize timer2 with pre configured values in cofig file
 * Arguments   : void
 * return      : void
 */
 void TIMER2_voidInitializeTimer2(void);

/*==================================================================================================================
 * timer2 Normal Mode
 *==================================================================================================================*/
 #if TIMER2_MODE == TIMER2_NORMAL_MODE

	/*
	* Prototype   : void TIMER2_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);
	* Description : Calculate timer2 tick time for desire input time in ms
	* Arguments   : void
	* return      : void
	*/
	void TIMER2_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);


	/*
	* Prototype   : void TIMER2_voidSetDesiredTime_us(uint32_t Copy_Time_us);
	* Description : Calculate timer2 tick time for desire input time in us
	* Arguments   : void
	* return      : void
	*/
	void TIMER2_voidSetDesiredTime_us(uint32_t Copy_Time_us);


   /*====================================================================
	* timer2 Over flow Interrupt
	*====================================================================*/
   /*
	* Prototype   : void TIMER2_voidOverFlowCallBack(void(*Copy_Ptr)(void));
	* Description : Callback function for timer2 over flow Interrupt
	* Arguments   : pointer to function Copy_Ptr
	* return      : void
	*/
	void TIMER2_voidOverFlowCallBack(void(*Copy_Ptr)(void));



/*==================================================================================================================
 * timer2 CTC Mode
 *==================================================================================================================*/
 #elif TIMER2_MODE == TIMER2_CTC_MODE

   /*
	* Prototype   : void TIMER2_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);
	* Description : Calculate timer2 tick time for desire input time in ms
	* Arguments   : void
	* return      : void
	*/
	void TIMER2_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);

   /*
	* Prototype   : void TIMER2_voidSetDesiredTime_us(uint32_t Copy_Time_us);
	* Description : Calculate timer2 tick time for desire input time in us
	* Arguments   : void
	* return      : void
	*/
	void TIMER2_voidSetDesiredTime_us(uint32_t Copy_Time_us);

   /*
	* Prototype   : void TIMER2_voidCTCCallBackfunction(void(*Copy_Ptr)(void));
	* Description : Call back function
	* Arguments   : void
	* return      : Pointer to function Copy_Ptr
	*/
	void TIMER2_voidCTCCallBackfunction(void(*Copy_Ptr)(void));


/*==================================================================================================================
 * timer2 Fast PWM Mode
 *==================================================================================================================*/
 #elif (TIMER2_MODE == TIMER2_FAST_PWM_MODE)

   /*
	* Prototype   : void TIMER2_voidFastPWM(uint8_t Copy_uint8_tDutyCycle,uint8_t Copy_uint8_tPWMMode);
	* Description : output Fast PWM on OC0 pin with duty cycle of Copy_uint8_tDutyCycle
	* Arguments   : DutyCycle: determine PWM duty cycle from 0 to 100
	* return      : void
	*/
	 void TIMER2_voidFastPWM(uint8_t Copy_uint8_tDutyCycle);

 /*==================================================================================================================
 * timer2 Phase correct PWM Mode
 *==================================================================================================================*/
 #elif TIMER2_MODE == TIMER2_PHASE_CORCT_MODE

   /*
	* Prototype   : void TIMER2_voidPhaseCorrectPWM(uint8_t Copy_uint8_tDutyCycle);
	* Description : output phase correct PWM on OC0 pin with duty cycle of Copy_uint8_tDutyCycle
	* Arguments   : DutyCycle: determine PWM duty cycle from 0 to 100
	* return      : void
	*/
	void TIMER2_voidPhaseCorrectPWM(uint8_t Copy_uint8_tDutyCycle);

 #endif



#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
