/*
 * Timer.c
 *
 *  Created on: Oct 13, 2021
 *      Author: ah132
 */

#include "Timer2_Config.h"
#include "Timer2_Private.h"





/*====================================================================
 * Timer2 Interrupt ISRs
 *====================================================================*/
#if TIMER2_MODE == TIMER2_CTC_MODE
void __vector_13 (void) __attribute__ ((signal,used)); 	/* Timer/Counter2 Compare Match A */
void __vector_14 (void) __attribute__ ((signal,used));	/* Timer/Counter2 Compare Match B */
#elif TIMER2_MODE == TIMER2_NORMAL_MODE
void __vector_15 (void) __attribute__ ((signal,used));	/* Timer/Counter2 Overflow */
#endif
/*====================================================================
 * Call back pointers
 *====================================================================*/
#if TIMER2_MODE == TIMER2_NORMAL_MODE
static void (*TIMER2_OverFlowCallBackPointer)(void);
#elif TIMER2_MODE == TIMER2_CTC_MODE
static void (*TIMER2_CTCA_CallBackPointer)(void);
static void (*TIMER2_CTCB_CallBackPointer)(void);
#endif
/*====================================================================
 * Global Variables
 *====================================================================*/
#if TIMER2_MODE == TIMER2_NORMAL_MODE
static volatile uint32_t TIMER2_uint32_tOverFlowNo   = 0;
static uint8_t           TIMER2_uint8_tTCNT2Preload  = 0;
#endif
//static volatile uint32_t TIMER2_uint32_tCTCMatchNo   = 0;
static uint8_t           TIMER2_uint8_tTCCR2A_Value    = 0;
static uint8_t           TIMER2_uint8_tTCCR2B_Value    = 0;
static uint16_t          TIMER2_u16Prescaler    	   = 1;


/*==================================================================================================================
 * Timer2 Modules
 *==================================================================================================================*/

/**************************************************************************************
 * Prototype   : void TIMER2_voidStartTimer(void);
 * Description : Start Timer2 counter register
 * Arguments   : void
 * return      : void
 **************************************************************************************/
 void TIMER2_voidStartTimer(void)
 {
	 /*Start TCNT2 Reg counting by loading it's value*/
	 TCCR2A = TIMER2_uint8_tTCCR2A_Value;
	 TCCR2B = TIMER2_uint8_tTCCR2B_Value;

 }

/**************************************************************************************
 * Prototype   : void TIMER2_voidStopTimer(void);
 * Description : Stop Timer2 counter register
 * Arguments   : void
 * return      : void
 **************************************************************************************/
 void TIMER2_voidStopTimer(void)
 {

	 /*Stop TCNT2 Reg counting by loading zeros in CS20,CS21,CS22*/
 	 TCCR2B = TIMER2_uint8_tTCCR2B_Value & TIMER2_STOP_MASK;


 }


/**********************************************************************************
 * Prototype   : void TIMER2_voidInitializeTimer2(void);
 * Description : Initialize Timer2 with pre configured values in cofig file
 * Arguments   : void
 * return      : void
 ***********************************************************************************/
 void TIMER2_voidInitializeTimer2(void)
 {
	 TCNT2=0;

	/*TCCR2B Prescaler value is stored temporarily in TIMER2_uint8_tTCCR2B_Value variable*/
	/*Initialize TCCR2B_ value*/
	/*Reset first 3 BITS*/
	TIMER2_uint8_tTCCR2B_Value &= TIMER2_TCCR2B_MASK;


	/*Mask Prescaler value*/
	TIMER2_uint8_tTCCR2B_Value |= TIMER2_PRESCALER;


	/*====================================================================
	 * calculate Prescaler value that will be used later in equations
	 *====================================================================*/
	TIMER2_u16Prescaler = 1;
	#if (TIMER2_PRESCALER==No_Prescaller)
		/* set prescaler vale with a value higher than prescaler value
		 * because in calculation when dividing value will be zero (no flaut point calculation)*/
		TIMER2_u16Prescaler = F_CPU/1000000;

	#elif (TIMER2_PRESCALER==Prescaller_8)

		TIMER2_u16Prescaler = 8;

	#elif (TIMER2_PRESCALER>Prescaller_8 && TIMER2_PRESCALER<=Prescaller_1024)

		/*caclulate prescaler = 2^(2*Prescaller)*/
		for (uint8_t i=0;i<(TIMER2_PRESCALER*2);i++)
		{
			TIMER2_u16Prescaler *= 2;
		}

	#else

		#error "Wrong Prescaller"

	#endif
	/*====================================================================
	 * Choose Timer2 Mode
	 *====================================================================*/
	#if (TIMER2_MODE==TIMER2_NORMAL_MODE)

		//Choose normal mode
		CLEAR_BIT(TIMER2_uint8_tTCCR2B_Value,TIMER2_WGM22);
		CLEAR_BIT(TIMER2_uint8_tTCCR2A_Value,TIMER2_WGM21);
		CLEAR_BIT(TIMER2_uint8_tTCCR2A_Value,TIMER2_WGM20);

		#if (TIMER2_INTERRUPT_STATUS == TIMER2_INT_ENABLED)
		//enable Global interrupt
		sei();
		//enable Timer2 Overflow interrupt
		SET_BIT(TIMSK2,TIMER2_TOIE2);
		#endif


	#elif (TIMER2_MODE == TIMER2_CTC_MODE)

		/*Choose CTC mode*/
		CLEAR_BIT(TIMER2_uint8_tTCCR2A_Value,TIMER2_WGM20);
		CLEAR_BIT(TIMER2_uint8_tTCCR2B_Value,TIMER2_WGM22);
		SET_BIT(TIMER2_uint8_tTCCR2B_Value,TIMER2_FOC2A);
		SET_BIT(TIMER2_uint8_tTCCR2A_Value,TIMER2_WGM21);

#if Timer2_ChannalA
		/*Set OC2A initial value*/
		OCR2A = TIMER2_OCR2A_VALUE;
		DDRB_OC2A |= 1<<4;
#endif
#if Timer2_ChannalB
		/*Set OC2B initial value*/
		OCR2B = TIMER2_OCR2B_VALUE;
		DDRH_OC2B |= 1<<6;
#endif


		#if (TIMER2_INTERRUPT_STATUS == TIMER2_INT_ENABLED)
		//enable Global interrupt
		sei();
#if Timer2_ChannalA
		//enable Timer2 CTC interrupt
		SET_BIT(TIMSK2,TIMER2_OCIE2A);
#endif
#if Timer2_ChannalB
		//enable Timer2 CTC interrupt
		SET_BIT(TIMSK2,TIMER2_OCIE2B);
#endif
		#endif


	#elif (TIMER2_MODE==TIMER2_PHASE_CORCT_MODE)

		/*Choose Phase correct mode*/
		SET_BIT(TIMER2_uint8_tTCCR2A_Value,TIMER2_WGM20);
		CLEAR_BIT(TIMER2_uint8_tTCCR2A_Value,TIMER2_WGM21);
		CLEAR_BIT(TIMER2_uint8_tTCCR2B_Value,TIMER2_WGM22);

	#elif (TIMER2_MODE==TIMER2_FAST_PWM_MODE)



		/*Choose Fast PWM mode*/
		SET_BIT(TIMER2_uint8_tTCCR2A_Value,TIMER2_WGM20);
		SET_BIT(TIMER2_uint8_tTCCR2A_Value,TIMER2_WGM21);
		SET_BIT(TIMER2_uint8_tTCCR2B_Value,TIMER2_WGM22);
		//SET_BIT(DDRB_OC2A,4);
		OCR2A = TIMER2_OCR2A_VALUE;
#if Timer2_ChannalB
		SET_BIT(DDRH_OC2B,6);
#endif


	#else
		#error "Wrong Tomer0 Mode"
	#endif


	/*Choose OC2A, OC2B Pin Mode*/
	/*mask COM2A0,COM2A1,COM2B0,COM2B1 bits with zeros*/
	TIMER2_uint8_tTCCR2A_Value &= TIMER2_COM_MASK;
	/*Put mode in COM2A0,COM2A1 bits*/
	TIMER2_uint8_tTCCR2A_Value |= (Timer2_OC2A_MODE<<6) ;
	/*Put mode in COM2B0,COM2B1 bits*/
	TIMER2_uint8_tTCCR2A_Value |= (Timer2_OC2B_MODE<<4) ;



 }/*TIMER2_voidInitializeTimer2*/

#if TIMER2_MODE == TIMER2_NORMAL_MODE

/*==================================================================================================================
 * Timer2 Normal Mode
 *==================================================================================================================*/

/**************************************************************************************
 * Prototype   : void TIMER2_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);
 * Description : Calculate Timer2 tick time for desire input time in ms
 * Arguments   : void
 * return      : void
 **************************************************************************************/
void TIMER2_voidSetDesiredTime_ms(uint32_t Copy_Time_ms)
{
	/*Timer2 calculations*/

	uint32_t Local_uint32_tTickTime               = (TIMER2_u16Prescaler*1000000)/F_CPU ;  /*Time in micro second*/
	uint32_t Local_uint32_tOverFlowTime           = Local_uint32_tTickTime * TIMER2_REG_CAPACITY ;
	uint32_t Local_uint32_tDesiredTime            = Copy_Time_ms*1000;                              /*Time in micro second*/

	if (TIMER2_PRESCALER == No_Prescaller)
	{
		/*Multiply bu the same value multiplied by prescaler*/
		Local_uint32_tDesiredTime = Local_uint32_tDesiredTime * (F_CPU/1000000);
	}
	/*Number of over flow required*/
	TIMER2_uint32_tOverFlowNo               = Local_uint32_tDesiredTime/Local_uint32_tOverFlowTime;
	/*Number of over flaws remainder*/
	uint32_t TIMER2_uint32_tOverFlowRemainder    = Local_uint32_tDesiredTime%Local_uint32_tOverFlowTime;

	/*clear TCNT2 Register*/
	TCNT2=0;

	/*if there is initial value*/
	if (TIMER2_uint32_tOverFlowRemainder>0)
	{
		/*initialize TCNT2 value with pre load value */
		TIMER2_uint8_tTCNT2Preload = TIMER2_REG_CAPACITY - TIMER2_uint32_tOverFlowRemainder ;
		TCNT2 = TIMER2_uint8_tTCNT2Preload;
		/*increment no of overflows by one*/
		TIMER2_uint32_tOverFlowNo++;
	}

	/*Start counter by setting TCCR0 value*/
	TIMER2_voidStartTimer();

#if !TIMER2_INTERRUPT_STATUS
	uint32_t Local_uint32_tCounter = 0;
	while(Local_uint32_tCounter != TIMER2_uint32_tOverFlowNo){
		while(BIT_IS_CLEAR(TIFR2, TOV2));	// wait till compare flag goes up
		SET_BIT(TIFR2, TOV2);
		Local_uint32_tCounter++;
	}
	TCNT2 =   TIMER2_uint8_tTCNT2Preload;
	TIMER2_voidStopTimer();						// stop timer to save energy
#endif

}/*end of TIMER2_voidSetDesiredTime_ms()*/

/**************************************************************************************
 * Prototype   : void TIMER2_voidSetDesiredTime_us(uint32_t Copy_Time_us);
 * Description : Calculate Timer2 tick time for desire input time in us
 * Arguments   : void
 * return      : void
 **************************************************************************************/
void TIMER2_voidSetDesiredTime_us(uint32_t Copy_Time_us)
{

	/*Timer2 calculations*/

	uint32_t Local_uint32_tTickTime               = (TIMER2_u16Prescaler*1000000)/F_CPU ;  /*Time in micro second*/
	uint32_t Local_uint32_tOverFlowTime           = Local_uint32_tTickTime * TIMER2_REG_CAPACITY ;
	uint32_t Local_uint32_tDesiredTime            = Copy_Time_us;									  /*Time in micro second*/

	if (TIMER2_PRESCALER == No_Prescaller)
	{
		/*Multiply bu the same value multiplied by prescaler*/
		Local_uint32_tDesiredTime = Local_uint32_tDesiredTime * (F_CPU/1000000);
	}

	TIMER2_uint32_tOverFlowNo               = Local_uint32_tDesiredTime/Local_uint32_tOverFlowTime;
	uint32_t TIMER2_uint32_tOverFlowRemainder    = Local_uint32_tDesiredTime%Local_uint32_tOverFlowTime;

	/*clear TCNT2 Register*/
	TCNT2=0;

	/*if there is initial value*/
	if (TIMER2_uint32_tOverFlowRemainder>0)
	{
		/*initialize TCNT2 value with pre load value */
		TIMER2_uint8_tTCNT2Preload = TIMER2_REG_CAPACITY - TIMER2_uint32_tOverFlowRemainder ;
		TCNT2 = TIMER2_uint8_tTCNT2Preload;
		/*increment no of overflows by one*/
		TIMER2_uint32_tOverFlowNo++;
	}

	/*Start counter by setting TCCR0 value*/
	TIMER2_voidStartTimer();
#if !TIMER2_INTERRUPT_STATUS
	uint32_t Local_uint32_tCounter = 0;
	while(Local_uint32_tCounter != TIMER2_uint32_tOverFlowNo){
		while(BIT_IS_CLEAR(TIFR2, TOV2));	// wait till compare flag goes up
		SET_BIT(TIFR2, TOV2);
		Local_uint32_tCounter++;
	}
	TCNT2 =   TIMER2_uint8_tTCNT2Preload;
	TIMER2_voidStopTimer();						// stop timer to save energy
#endif

}/*end of TIMER2_voidSetDesiredTime_us()*/


/*====================================================================
 * Timer2 Over flow Interrupt
 *====================================================================*/
/***************************************************************
 * Prototype   : void TIMER2_voidOverFlowCallBack(void(*Copy_Ptr)(void));
 * Description : Callback function for Timer2 over flow Interrupt
 * Arguments   : pointer to function Copy_Ptr
 * return      : void
 ***************************************************************/
 void TIMER2_voidOverFlowCallBack(void(*Copy_Ptr)(void))
 {
	 TIMER2_OverFlowCallBackPointer = Copy_Ptr;
 }

/**************************************************************
 * Prototype   : void __vector_11(void);
 * Description : Timer2 over flow ISR
 * Arguments   : void
 * return      : void
 ***************************************************************/
void __vector_15(void) /*Timer2 over flow ISR*/
{
	static uint32_t Local_uint32_tCounter = 0;
	Local_uint32_tCounter++;
	if(Local_uint32_tCounter == TIMER2_uint32_tOverFlowNo)
	{
		/*Run call back function for Timer2 over flow interrupt*/
		TIMER2_OverFlowCallBackPointer();

		Local_uint32_tCounter = 0;
		TCNT2 =   TIMER2_uint8_tTCNT2Preload;
	}


}/*end of __vector_15()*/



#elif TIMER2_MODE == TIMER2_CTC_MODE
/*==================================================================================================================
 * Timer2 CTC Mode
 *==================================================================================================================*/
/*
 * Prototype   : void TIMER2_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);
 * Description : Calculate Timer2 tick time for desire input time in ms
 * Arguments   : void
 * return      : void
 */
 void TIMER2_voidSetDesiredTime_ms(uint32_t Copy_Time_ms)
 {
 	 /*Timer2 calculations*/
	 uint32_t Local_uint32_tTickTime   = (TIMER2_u16Prescaler * 1000000) / F_CPU ;  /*Time in micro second*/
	 uint32_t Local_uint32_tDesiredTime = Copy_Time_ms * 1000;                                /*Time in micro second*/
//	 uint32_t Local_uint32_tDesiredTicks=0;
//	 uint32_t Local_uint32_tOCR=0;
	 if (TIMER2_PRESCALER == No_Prescaller)
	 {
		 /*Multiply bu the same value multiplied by prescaler*/
		 Local_uint32_tDesiredTime = Local_uint32_tDesiredTime * (F_CPU/1000000);
	 }

	 /*set OCR2A value*/
	 OCR2A = Local_uint32_tDesiredTime / Local_uint32_tTickTime;
//	 Local_uint32_tDesiredTicks    = Local_uint32_tDesiredTime / Local_uint32_tTickTime;
//	 if(Local_uint32_tDesiredTicks > TIMER2_REG_CAPACITY){
//		 OCR2A = 0xFF;
//		 TIMER2_uint32_tCTCMatchNo = Local_uint32_tDesiredTicks /TIMER2_REG_CAPACITY;
//		 Local_uint32_tOCR =  Local_uint32_tDesiredTicks %TIMER2_REG_CAPACITY;
//		 TIMER2_uint32_tCTCMatchNo++;
//
//	 }else{
//		 /*set OCR2A value*/
//		 OCR2A = Local_uint32_tDesiredTicks;
//	 }

	 /*Start counter by setting TCCR0 value*/
	 TIMER2_voidStartTimer();

#if !TIMER2_INTERRUPT_STATUS
	 while(BIT_IS_CLEAR(TIFR2, OCF2A));	// wait till compare flag goes up
	 SET_BIT(TIFR2, OCF2A);

//	uint32_t Local_uint32_tCounter = 0;
//	while(Local_uint32_tCounter != TIMER2_uint32_tCTCMatchNo){
//		while(BIT_IS_CLEAR(TIFR2, OCF2A));	// wait till compare flag goes up
//		Local_uint32_tCounter++;
//		if(Local_uint32_tCounter+1 == TIMER2_uint32_tCTCMatchNo) OCR2A = Local_uint32_tOCR;
//		SET_BIT(TIFR2, OCF2A);
//	}
//	TIMER2_voidStopTimer();						// stop timer to save energy
#endif

 }/*end of TIMER2_voidSetDesiredTime_ms()*/

/*
 * Prototype   : void TIMER2_voidSetDesiredTime_us(uint32_t Copy_Time_us);
 * Description : Calculate Timer2 tick time for desire input time in us
 * Arguments   : void
 * return      : void
 */
 void TIMER2_voidSetDesiredTime_us(uint32_t Copy_Time_us)
 {
  	 /*Timer2 calculations*/
	 uint32_t Local_uint32_tTickTime    = (TIMER2_u16Prescaler * 1000000) / F_CPU ;  /*Time in micro second*/
	 uint32_t Local_uint32_tDesiredTime = Copy_Time_us;                                       /*Time in micro second*/
	 if (TIMER2_PRESCALER == No_Prescaller)
	 {
		 /*Multiply bu the same value multiplied by prescaler*/
		 Local_uint32_tDesiredTime = Local_uint32_tDesiredTime * (F_CPU/1000000);
	 }

	 /*set OCR0 value*/
	 OCR2A    = Local_uint32_tDesiredTime / Local_uint32_tTickTime;
	 OCR2B    = Local_uint32_tDesiredTime / Local_uint32_tTickTime;

	 /*Start counter by setting TCCR0 value*/
	 TIMER2_voidStartTimer();

 }/*end of TIMER2_voidSetDesiredTime_us()*/

 /*====================================================================
  * Timer2 Compare mode Interrupt
  *====================================================================*/
 /*
 * Prototype   : void TIMER2_voidCTCA_CallBackfunction(void(*Copy_Ptr)(void));
 * Description : Call back function
 * Arguments   : void
 * return      : Pointer to function Copy_Ptr
 */
 void TIMER2_voidCTCA_CallBackfunction(void(*Copy_Ptr)(void))
 {
	 //save function address in global pointer to function
 	 TIMER2_CTCA_CallBackPointer = Copy_Ptr;

 }/*end of TIMER2_voidCTC_ACallBackfn()*/

 /*
  * Prototype   : void TIMER2_voidCTCB_CallBackfunction(void(*Copy_Ptr)(void));
  * Description : Call back function
  * Arguments   : void
  * return      : Pointer to function Copy_Ptr
  */
 void TIMER2_voidCTCB_CallBackfunction(void(*Copy_Ptr)(void))
 {
	 //save function address in global pointer to function
 	 TIMER2_CTCB_CallBackPointer = Copy_Ptr;

 }/*end of TIMER2_voidCTC_BCallBackfn()*/

 /*
 * Prototype   : void __vector_13(void);
 * Description : Timer2 output compare match channal A ISR
 * Arguments   : void
 * return      : void
 */
 void __vector_13(void)/*Timer2 CTC ISR*/
 {
 	 /*Run call back function*/
	 TIMER2_CTCA_CallBackPointer();

 }/*end of __vector_13()*/
 /*
 * Prototype   : void __vector_14(void);
 * Description : Timer2 output compare match channal B ISR
 * Arguments   : void
 * return      : void
 */
 void __vector_14(void)/*Timer2 CTC ISR*/
 {
 	 /*Run call back function*/
	 TIMER2_CTCB_CallBackPointer();

 }/*end of __vector_14()*/

/*==================================================================================================================
 * Timer2 Fast PWM Mode
 *==================================================================================================================*/

 #elif (TIMER2_MODE == TIMER2_FAST_PWM_MODE)

 /*
 * Prototype   : void TIMER2_voidFastPWM(uint8_t Copy_uint8_tDutyCycle,uint8_t Copy_uint8_tPWMMode);
 * Description : output Fast PWM on OC0 pin with duty cycle of Copy_uint8_tDutyCycle
 * Arguments   : DutyCycle: determine PWM duty cycle from 0 to 100
 * return      : void
 */
 void TIMER2_voidFastPWM(uint8_t Copy_uint8_tDutyCycle)
{
//	 if(channel == Channel_A2){
//		 /*configure PWM Duty Cycle*/
//		// OCR2A = (Copy_uint8_tDutyCycle*TIMER2_REG_CAPACITY)/100;
//	 }
	 //else if(channel == Channel_B2){
		 /*configure PWM Duty Cycle*/
		 //OCR2B = (Copy_uint8_tDutyCycle*TIMER2_REG_CAPACITY)/100;
		 OCR2B = Copy_uint8_tDutyCycle;
	 //}else return;
	 /*Start PWM*/
	 TIMER2_voidStartTimer();

}/*end of TIMER2_voidFastPWM()*/
 /*==================================================================================================================
 * Timer2 Phase correct PWM Mode
 *==================================================================================================================*/

 #elif TIMER2_MODE == TIMER2_PHASE_CORCT_MODE

 /*
 * Prototype   : void TIMER2_voidPhaseCorrectPWM(uint8_t Copy_uint8_tDutyCycle);
 * Description : output phase correct PWM on OC0 pin with duty cycle of Copy_uint8_tDutyCycle
 * Arguments   : DutyCycle: determine PWM duty cycle from 0 to 100
 * return      : void
 */
 void TIMER2_voidPhaseCorrectPWM(uint8_t Copy_uint8_tDutyCycle)
 {
	/*configure PWM Duty Cycle*/
 	OCR2A = (Copy_uint8_tDutyCycle*(TIMER2_REG_CAPACITY-1))/100;
 	OCR2B = (Copy_uint8_tDutyCycle*(TIMER2_REG_CAPACITY-1))/100;
 	/*Start PWM*/
	TIMER2_voidStartTimer();

 }/*end of TIMER2_voidPhaseCorrectPWM()*/

 /*==================================================================================================================
  * EOF
  *==================================================================================================================*/

 #endif
