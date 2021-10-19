/*
 * Timer0_face.h
 *
 *  Created on: Oct 14, 2021
 *      Author: ah132
 */

#ifndef MCAL_TIMER_TIMER0_TIMER0_INTERFACE_H_
#define MCAL_TIMER_TIMER0_TIMER0_INTERFACE_H_

#include "../../../Utils/std_types.h"
#include "TIMER0_Config.h"
#include "TIMER0_Privae.h"






/*==================================================================================================================
 * TIMER0 Modules
 *==================================================================================================================*/


/*
 * Prototype   : void TIMER0_voidStartTimer(void);
 * Description : Start TIMER0 counter register
 * Arguments   : void
 * return      : void
 */
 void TIMER0_voidStartTimer(void);

/*
 * Prototype   : void TIMER0_voidStopTimer(void);
 * Description : Stop TIMER0 counter register
 * Arguments   : void
 * return      : void
 */
 void TIMER0_voidStopTimer(void);

/*
 * Prototype   : void TIMER0_voidInitializeTIMER0(void);
 * Description : Initialize TIMER0 with pre configured values in cofig file
 * Arguments   : void
 * return      : void
 */
 void TIMER0_voidInitializeTIMER0(void);

/*==================================================================================================================
 * TIMER0 Normal Mode
 *==================================================================================================================*/
 #if TIMER0_MODE == TIMER0_NORMAL_MODE

	/*
	* Prototype   : void TIMER0_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);
	* Description : Calculate TIMER0 tick time for desire input time in ms
	* Arguments   : void
	* return      : void
	*/
	void TIMER0_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);


	/*
	* Prototype   : void TIMER0_voidSetDesiredTime_us(uint32_t Copy_Time_us);
	* Description : Calculate TIMER0 tick time for desire input time in us
	* Arguments   : void
	* return      : void
	*/
	void TIMER0_voidSetDesiredTime_us(uint32_t Copy_Time_us);


   /*====================================================================
	* TIMER0 Over flow Interrupt
	*====================================================================*/
   /*
	* Prototype   : void TIMER0_voidOverFlowCallBack(void(*Copy_Ptr)(void));
	* Description : Callback function for TIMER0 over flow Interrupt
	* Arguments   : pointer to function Copy_Ptr
	* return      : void
	*/
	void TIMER0_voidOverFlowCallBack(void(*Copy_Ptr)(void));



/*==================================================================================================================
 * TIMER0 CTC Mode
 *==================================================================================================================*/
 #elif TIMER0_MODE == TIMER0_CTC_MODE

   /*
	* Prototype   : void TIMER0_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);
	* Description : Calculate TIMER0 tick time for desire input time in ms
	* Arguments   : void
	* return      : void
	*/
	void TIMER0_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);

   /*
	* Prototype   : void TIMER0_voidSetDesiredTime_us(uint32_t Copy_Time_us);
	* Description : Calculate TIMER0 tick time for desire input time in us
	* Arguments   : void
	* return      : void
	*/
	void TIMER0_voidSetDesiredTime_us(uint32_t Copy_Time_us);

   /*
	* Prototype   : void TIMER0_voidCTCCallBackfunction(void(*Copy_Ptr)(void));
	* Description : Call back function
	* Arguments   : void
	* return      : Pointer to function Copy_Ptr
	*/
	void TIMER0_voidCTCCallBackfunction(void(*Copy_Ptr)(void));


/*==================================================================================================================
 * TIMER0 Fast PWM Mode
 *==================================================================================================================*/
 #elif (TIMER0_MODE == TIMER0_FAST_PWM_MODE)

   /*
	* Prototype   : void TIMER0_voidFastPWM(uint8_t Copy_uint8_tDutyCycle,uint8_t Copy_uint8_tPWMMode);
	* Description : output Fast PWM on OC0 pin with duty cycle of Copy_uint8_tDutyCycle
	* Arguments   : DutyCycle: determine PWM duty cycle from 0 to 100
	* return      : void
	*/
	 void TIMER0_voidFastPWM(uint8_t Copy_uint8_tDutyCycle);

 /*==================================================================================================================
 * TIMER0 Phase correct PWM Mode
 *==================================================================================================================*/
 #elif TIMER0_MODE == TIMER0_PHASE_CORCT_MODE

   /*
	* Prototype   : void TIMER0_voidPhaseCorrectPWM(uint8_t Copy_uint8_tDutyCycle);
	* Description : output phase correct PWM on OC0 pin with duty cycle of Copy_uint8_tDutyCycle
	* Arguments   : DutyCycle: determine PWM duty cycle from 0 to 100
	* return      : void
	*/
	void TIMER0_voidPhaseCorrectPWM(uint8_t Copy_uint8_tDutyCycle);

 #endif



#endif /* MCAL_TIMER_TIMER0_TIMER0_INTERFACE_H_ */
