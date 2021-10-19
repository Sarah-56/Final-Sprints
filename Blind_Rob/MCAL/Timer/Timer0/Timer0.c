/*
 * Timer.c
 *
 *  Created on: Oct 13, 2021
 *      Author: ah132
 */

#include "Timer0_Config.h"
#include "Timer0_Privae.h"


/*====================================================================
 * TIMER0 Interrupt ISRs
 *====================================================================*/
#if TIMER0_MODE == TIMER0_CTC_MODE
void __vector_21 (void) __attribute__ ((signal,used)); 	/* Timer/Counter0 Compare Match A */
void __vector_22 (void) __attribute__ ((signal,used));	/* Timer/Counter0 Compare Match B */
#elif TIMER0_MODE == TIMER0_NORMAL_MODE
void __vector_23 (void) __attribute__ ((signal,used));	/* Timer/Counter0 Overflow */
#endif
/*====================================================================
 * Call back pointers
 *====================================================================*/
#if TIMER0_MODE == TIMER0_NORMAL_MODE
static void (*TIMER0_OverFlowCallBackPointer)(void);
#elif TIMER0_MODE == TIMER0_CTC_MODE
static void (*TIMER0_CTCA_CallBackPointer)(void);
static void (*TIMER0_CTCB_CallBackPointer)(void);
#endif
/*====================================================================
 * Global Variables
 *====================================================================*/
#if TIMER0_MODE == TIMER0_NORMAL_MODE
static volatile uint32_t TIMER0_uint32_tOverFlowNo   = 0;
static uint8_t           TIMER0_uint8_tTCNT2Preload  = 0;
#endif
//static volatile uint32_t TIMER0_uint32_tCTCMatchNo   = 0;
static uint8_t           TIMER0_uint8_tTCCR0A_Value    = 0;
static uint8_t           TIMER0_uint8_tTCCR0B_Value    = 0;
static uint16_t          TIMER0_u16Prescaler    	   = 1;


/*==================================================================================================================
 * TIMER0 Modules
 *==================================================================================================================*/

/**************************************************************************************
 * Prototype   : void TIMER0_voidStartTimer(void);
 * Description : Start TIMER0 counter register
 * Arguments   : void
 * return      : void
 **************************************************************************************/
 void TIMER0_voidStartTimer(void)
 {
	 /*Start TCNT2 Reg counting by loading it's value*/
	 TCCR0A = TIMER0_uint8_tTCCR0A_Value;
	 TCCR0B = TIMER0_uint8_tTCCR0B_Value;

 }

/**************************************************************************************
 * Prototype   : void TIMER0_voidStopTimer(void);
 * Description : Stop TIMER0 counter register
 * Arguments   : void
 * return      : void
 **************************************************************************************/
 void TIMER0_voidStopTimer(void)
 {

	 /*Stop TCNT0 Reg counting by loading zeros in CS00,CS01,CS02*/
 	 TCCR0B = TIMER0_uint8_tTCCR0B_Value & TIMER0_STOP_MASK;


 }


/**********************************************************************************
 * Prototype   : void TIMER0_voidInitializeTIMER0(void);
 * Description : Initialize TIMER0 with pre configured values in cofig file
 * Arguments   : void
 * return      : void
 ***********************************************************************************/
 void TIMER0_voidInitializeTIMER0(void)
 {
	 TCNT0=0;

	/*TCCR2B Prescaler value is stored temporarily in TIMER0_uint8_tTCCR0B_Value variable*/
	/*Initialize TCCR2B_ value*/
	/*Reset first 3 BITS*/
	TIMER0_uint8_tTCCR0B_Value &= TIMER0_TCCR0B_MASK;


	/*Mask Prescaler value*/
	TIMER0_uint8_tTCCR0B_Value |= TIMER0_PRESCALER;


	/*====================================================================
	 * calculate Prescaler value that will be used later in equations
	 *====================================================================*/
	TIMER0_u16Prescaler = 1;
	#if (TIMER0_PRESCALER==No_Prescaller)
		/* set prescaler vale with a value higher than prescaler value
		 * because in calculation when dividing value will be zero (no flaut point calculation)*/
		TIMER0_u16Prescaler = F_CPU/1000000;

	#elif (TIMER0_PRESCALER==Prescaller_8)

		TIMER0_u16Prescaler = 8;

	#elif (TIMER0_PRESCALER>Prescaller_8 && TIMER0_PRESCALER<=Prescaller_1024)

		/*caclulate prescaler = 2^(2*Prescaller)*/
		for (uint8_t i=0;i<(TIMER0_PRESCALER*2);i++)
		{
			TIMER0_u16Prescaler *= 2;
		}
#elif (TIMER0_PRESCALER == Prescaller_FalExtClk)



	#else

		#error "Wrong Prescaller"

	#endif
	/*====================================================================
	 * Choose TIMER0 Mode
	 *====================================================================*/
	#if (TIMER0_MODE==TIMER0_NORMAL_MODE)

		//Choose normal mode
		CLEAR_BIT(TIMER0_uint8_tTCCR0B_Value,TIMER0_WGM22);
		CLEAR_BIT(TIMER0_uint8_tTCCR0A_Value,TIMER0_WGM21);
		CLEAR_BIT(TIMER0_uint8_tTCCR0A_Value,TIMER0_WGM20);

		#if (TIMER0_INTERRUPT_STATUS == TIMER0_INT_ENABLED)
		//enable Global interrupt
		sei();
		//enable TIMER0 Overflow interrupt
		SET_BIT(TIMSK2,TIMER0_TOIE2);
		#endif


	#elif (TIMER0_MODE == TIMER0_CTC_MODE)

		/*Choose CTC mode*/
		CLEAR_BIT(TIMER0_uint8_tTCCR0A_Value,TIMER0_WGM00);
		SET_BIT(TIMER0_uint8_tTCCR0A_Value,TIMER0_WGM01);
		CLEAR_BIT(TIMER0_uint8_tTCCR0B_Value,TIMER0_WGM02);


		SET_BIT(TIMER0_uint8_tTCCR0B_Value,6);
		SET_BIT(TIMER0_uint8_tTCCR0B_Value,7);

#if TIMER0_ChannalA
		/*Set OC0A initial value*/
		OCR0A = TIMER0_OCR0A_VALUE;
		DDRB_OCA0 |= (1<<7);

#endif
#if TIMER0_ChannalB
		/*Set OC0B initial value*/
		OCR0B = TIMER0_OCR0B_VALUE;
		DDRG_OCB0 |= (1<<5);
#endif


		#if (TIMER0_INTERRUPT_STATUS == TIMER0_INT_ENABLED)
		//enable Global interrupt
		sei();
#if TIMER0_ChannalA
		//enable TIMER0 CTC interrupt
		SET_BIT(TIMSK2,TIMER0_OCIE2A);
#endif
#if TIMER0_ChannalB
		//enable TIMER0 CTC interrupt
		SET_BIT(TIMSK2,TIMER0_OCIE2B);
#endif
		#endif


	#elif (TIMER0_MODE==TIMER0_PHASE_CORCT_MODE)

		/*Choose Phase correct mode*/
		SET_BIT(TIMER0_uint8_tTCCR0A_Value,TIMER0_WGM20);
		CLEAR_BIT(TIMER0_uint8_tTCCR0A_Value,TIMER0_WGM21);
		CLEAR_BIT(TIMER0_uint8_tTCCR0B_Value,TIMER0_WGM22);

	#elif (TIMER0_MODE==TIMER0_FAST_PWM_MODE)

		/*Choose Fast PWM mode*/
		SET_BIT(TIMER0_uint8_tTCCR0A_Value,TIMER0_WGM00);
		SET_BIT(TIMER0_uint8_tTCCR0A_Value,TIMER0_WGM01);
		SET_BIT(TIMER0_uint8_tTCCR0B_Value,TIMER0_WGM02);
		//SET_BIT(DDRB_OCA0,7);
		OCR0A = TIMER0_OCR0A_VALUE;
#if TIMER0_ChannalB
		SET_BIT(DDRG_OCB0,5);
#endif


	#else
		#error "Wrong Tomer0 Mode"
	#endif


	/*Choose OC0A, OC0B Pin Mode*/
	/*mask COM.A0,COM0A1,COM0B0,COM0B1 bits with zeros*/
	TIMER0_uint8_tTCCR0A_Value &= TIMER0_COM_MASK;
	/*Put mode in COM2A0,COM2A1 bits*/
	TIMER0_uint8_tTCCR0A_Value |= (TIMER0_OC0A_MODE<<6) ;
	/*Put mode in COM2B0,COM2B1 bits*/
	TIMER0_uint8_tTCCR0A_Value |= (TIMER0_OC0B_MODE<<4) ;



 }/*TIMER0_voidInitializeTIMER0*/

#if TIMER0_MODE == TIMER0_NORMAL_MODE

/*==================================================================================================================
 * TIMER0 Normal Mode
 *==================================================================================================================*/

/**************************************************************************************
 * Prototype   : void TIMER0_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);
 * Description : Calculate TIMER0 tick time for desire input time in ms
 * Arguments   : void
 * return      : void
 **************************************************************************************/
void TIMER0_voidSetDesiredTime_ms(uint32_t Copy_Time_ms)
{
	/*TIMER0 calculations*/

	uint32_t Local_uint32_tTickTime               = (TIMER0_u16Prescaler*1000000)/F_CPU ;  /*Time in micro second*/
	uint32_t Local_uint32_tOverFlowTime           = Local_uint32_tTickTime * TIMER0_REG_CAPACITY ;
	uint32_t Local_uint32_tDesiredTime            = Copy_Time_ms*1000;                              /*Time in micro second*/

	if (TIMER0_PRESCALER == No_Prescaller)
	{
		/*Multiply bu the same value multiplied by prescaler*/
		Local_uint32_tDesiredTime = Local_uint32_tDesiredTime * (F_CPU/1000000);
	}
	/*Number of over flow required*/
	TIMER0_uint32_tOverFlowNo               = Local_uint32_tDesiredTime/Local_uint32_tOverFlowTime;
	/*Number of over flaws remainder*/
	uint32_t TIMER0_uint32_tOverFlowRemainder    = Local_uint32_tDesiredTime%Local_uint32_tOverFlowTime;

	/*clear TCNT2 Register*/
	TCNT2=0;

	/*if there is initial value*/
	if (TIMER0_uint32_tOverFlowRemainder>0)
	{
		/*initialize TCNT2 value with pre load value */
		TIMER0_uint8_tTCNT2Preload = TIMER0_REG_CAPACITY - TIMER0_uint32_tOverFlowRemainder ;
		TCNT2 = TIMER0_uint8_tTCNT2Preload;
		/*increment no of overflows by one*/
		TIMER0_uint32_tOverFlowNo++;
	}

	/*Start counter by setting TCCR0 value*/
	TIMER0_voidStartTimer();

#if !TIMER0_INTERRUPT_STATUS
	uint32_t Local_uint32_tCounter = 0;
	while(Local_uint32_tCounter != TIMER0_uint32_tOverFlowNo){
		while(BIT_IS_CLEAR(TIFR2, TOV2));	// wait till compare flag goes up
		SET_BIT(TIFR2, TOV2);
		Local_uint32_tCounter++;
	}
	TCNT2 =   TIMER0_uint8_tTCNT2Preload;
	TIMER0_voidStopTimer();						// stop timer to save energy
#endif

}/*end of TIMER0_voidSetDesiredTime_ms()*/

/**************************************************************************************
 * Prototype   : void TIMER0_voidSetDesiredTime_us(uint32_t Copy_Time_us);
 * Description : Calculate TIMER0 tick time for desire input time in us
 * Arguments   : void
 * return      : void
 **************************************************************************************/
void TIMER0_voidSetDesiredTime_us(uint32_t Copy_Time_us)
{

	/*TIMER0 calculations*/

	uint32_t Local_uint32_tTickTime               = (TIMER0_u16Prescaler*1000000)/F_CPU ;  /*Time in micro second*/
	uint32_t Local_uint32_tOverFlowTime           = Local_uint32_tTickTime * TIMER0_REG_CAPACITY ;
	uint32_t Local_uint32_tDesiredTime            = Copy_Time_us;									  /*Time in micro second*/

	if (TIMER0_PRESCALER == No_Prescaller)
	{
		/*Multiply bu the same value multiplied by prescaler*/
		Local_uint32_tDesiredTime = Local_uint32_tDesiredTime * (F_CPU/1000000);
	}

	TIMER0_uint32_tOverFlowNo               = Local_uint32_tDesiredTime/Local_uint32_tOverFlowTime;
	uint32_t TIMER0_uint32_tOverFlowRemainder    = Local_uint32_tDesiredTime%Local_uint32_tOverFlowTime;

	/*clear TCNT2 Register*/
	TCNT2=0;

	/*if there is initial value*/
	if (TIMER0_uint32_tOverFlowRemainder>0)
	{
		/*initialize TCNT2 value with pre load value */
		TIMER0_uint8_tTCNT2Preload = TIMER0_REG_CAPACITY - TIMER0_uint32_tOverFlowRemainder ;
		TCNT2 = TIMER0_uint8_tTCNT2Preload;
		/*increment no of overflows by one*/
		TIMER0_uint32_tOverFlowNo++;
	}

	/*Start counter by setting TCCR0 value*/
	TIMER0_voidStartTimer();
#if !TIMER0_INTERRUPT_STATUS
	uint32_t Local_uint32_tCounter = 0;
	while(Local_uint32_tCounter != TIMER0_uint32_tOverFlowNo){
		while(BIT_IS_CLEAR(TIFR2, TOV2));	// wait till compare flag goes up
		SET_BIT(TIFR2, TOV2);
		Local_uint32_tCounter++;
	}
	TCNT2 =   TIMER0_uint8_tTCNT2Preload;
	TIMER0_voidStopTimer();						// stop timer to save energy
#endif

}/*end of TIMER0_voidSetDesiredTime_us()*/


/*====================================================================
 * TIMER0 Over flow Interrupt
 *====================================================================*/
/***************************************************************
 * Prototype   : void TIMER0_voidOverFlowCallBack(void(*Copy_Ptr)(void));
 * Description : Callback function for TIMER0 over flow Interrupt
 * Arguments   : pointer to function Copy_Ptr
 * return      : void
 ***************************************************************/
 void TIMER0_voidOverFlowCallBack(void(*Copy_Ptr)(void))
 {
	 TIMER0_OverFlowCallBackPointer = Copy_Ptr;
 }

/**************************************************************
 * Prototype   : void __vector_11(void);
 * Description : TIMER0 over flow ISR
 * Arguments   : void
 * return      : void
 ***************************************************************/
void __vector_15(void) /*TIMER0 over flow ISR*/
{
	static uint32_t Local_uint32_tCounter = 0;
	Local_uint32_tCounter++;
	if(Local_uint32_tCounter == TIMER0_uint32_tOverFlowNo)
	{
		/*Run call back function for TIMER0 over flow interrupt*/
		TIMER0_OverFlowCallBackPointer();

		Local_uint32_tCounter = 0;
		TCNT2 =   TIMER0_uint8_tTCNT2Preload;
	}


}/*end of __vector_15()*/



#elif TIMER0_MODE == TIMER0_CTC_MODE
/*==================================================================================================================
 * TIMER0 CTC Mode
 *==================================================================================================================*/
/*
 * Prototype   : void TIMER0_voidSetDesiredTime_ms(uint32_t Copy_Time_ms);
 * Description : Calculate TIMER0 tick time for desire input time in ms
 * Arguments   : void
 * return      : void
 */
 void TIMER0_voidSetDesiredTime_ms(uint32_t Copy_Time_ms)
 {
 	 /*TIMER0 calculations*/
	 uint32_t Local_uint32_tTickTime   = (TIMER0_u16Prescaler * 1000000) / F_CPU ;  /*Time in micro second*/
	 uint32_t Local_uint32_tDesiredTime = Copy_Time_ms * 1000;                                /*Time in micro second*/
//	 uint32_t Local_uint32_tDesiredTicks=0;
//	 uint32_t Local_uint32_tOCR=0;
	 if (TIMER0_PRESCALER == No_Prescaller)
	 {
		 /*Multiply bu the same value multiplied by prescaler*/
		 Local_uint32_tDesiredTime = Local_uint32_tDesiredTime * (F_CPU/1000000);
	 }

	 /*set OCR2A value*/
	 OCR0A = Local_uint32_tDesiredTime / Local_uint32_tTickTime;
//	 Local_uint32_tDesiredTicks    = Local_uint32_tDesiredTime / Local_uint32_tTickTime;
//	 if(Local_uint32_tDesiredTicks > TIMER0_REG_CAPACITY){
//		 OCR2A = 0xFF;
//		 TIMER0_uint32_tCTCMatchNo = Local_uint32_tDesiredTicks /TIMER0_REG_CAPACITY;
//		 Local_uint32_tOCR =  Local_uint32_tDesiredTicks %TIMER0_REG_CAPACITY;
//		 TIMER0_uint32_tCTCMatchNo++;
//
//	 }else{
//		 /*set OCR2A value*/
//		 OCR2A = Local_uint32_tDesiredTicks;
//	 }

	 /*Start counter by setting TCCR0 value*/
	 TIMER0_voidStartTimer();

#if !TIMER0_INTERRUPT_STATUS
	 while(BIT_IS_CLEAR(TIFR0, OCF0A));	// wait till compare flag goes up
	 SET_BIT(TIFR0, OCF0A);

//	uint32_t Local_uint32_tCounter = 0;
//	while(Local_uint32_tCounter != TIMER0_uint32_tCTCMatchNo){
//		while(BIT_IS_CLEAR(TIFR2, OCF2A));	// wait till compare flag goes up
//		Local_uint32_tCounter++;
//		if(Local_uint32_tCounter+1 == TIMER0_uint32_tCTCMatchNo) OCR2A = Local_uint32_tOCR;
//		SET_BIT(TIFR2, OCF2A);
//	}
//	TIMER0_voidStopTimer();						// stop timer to save energy
#endif

 }/*end of TIMER0_voidSetDesiredTime_ms()*/

/*
 * Prototype   : void TIMER0_voidSetDesiredTime_us(uint32_t Copy_Time_us);
 * Description : Calculate TIMER0 tick time for desire input time in us
 * Arguments   : void
 * return      : void
 */
 void TIMER0_voidSetDesiredTime_us(uint32_t Copy_Time_us)
 {
  	 /*TIMER0 calculations*/
	 uint32_t Local_uint32_tTickTime    = (TIMER0_u16Prescaler * 1000000) / F_CPU ;  /*Time in micro second*/
	 uint32_t Local_uint32_tDesiredTime = Copy_Time_us;                                       /*Time in micro second*/
	 if (TIMER0_PRESCALER == No_Prescaller)
	 {
		 /*Multiply bu the same value multiplied by prescaler*/
		 Local_uint32_tDesiredTime = Local_uint32_tDesiredTime * (F_CPU/1000000);
	 }

	 /*set OCR0 value*/
	 OCR0A    = Local_uint32_tDesiredTime / Local_uint32_tTickTime;

	 /*Start counter by setting TCCR0 value*/
	 TIMER0_voidStartTimer();

 }/*end of TIMER0_voidSetDesiredTime_us()*/

 /*====================================================================
  * TIMER0 Compare mode Interrupt
  *====================================================================*/
 /*
 * Prototype   : void TIMER0_voidCTCA_CallBackfunction(void(*Copy_Ptr)(void));
 * Description : Call back function
 * Arguments   : void
 * return      : Pointer to function Copy_Ptr
 */
 void TIMER0_voidCTCA_CallBackfunction(void(*Copy_Ptr)(void))
 {
	 //save function address in global pointer to function
 	 TIMER0_CTCA_CallBackPointer = Copy_Ptr;

 }/*end of TIMER0_voidCTC_ACallBackfn()*/

 /*
  * Prototype   : void TIMER0_voidCTCB_CallBackfunction(void(*Copy_Ptr)(void));
  * Description : Call back function
  * Arguments   : void
  * return      : Pointer to function Copy_Ptr
  */
 void TIMER0_voidCTCB_CallBackfunction(void(*Copy_Ptr)(void))
 {
	 //save function address in global pointer to function
 	 TIMER0_CTCB_CallBackPointer = Copy_Ptr;

 }/*end of TIMER0_voidCTC_BCallBackfn()*/

 /*
 * Prototype   : void __vector_13(void);
 * Description : TIMER0 output compare match channal A ISR
 * Arguments   : void
 * return      : void
 */
 void __vector_21(void)/*TIMER0 CTC ISR*/
 {
 	 /*Run call back function*/
	 TIMER0_CTCA_CallBackPointer();

 }/*end of __vector_13()*/
 /*
 * Prototype   : void __vector_14(void);
 * Description : TIMER0 output compare match channal B ISR
 * Arguments   : void
 * return      : void
 */
 void __vector_22(void)/*TIMER0 CTC ISR*/
 {
 	 /*Run call back function*/
	 TIMER0_CTCB_CallBackPointer();

 }/*end of __vector_14()*/

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
 void TIMER0_voidFastPWM(uint8_t Copy_uint8_tDutyCycle)
  {
// 	 if(channel ==Channel_A){
// 		 /*configure PWM Duty Cycle*/
// 		 //OCR0A = (Copy_uint8_tDutyCycle*TIMER0_REG_CAPACITY)/100;
// 	 }
 	 //else if(channel == Channel_B){
 		 /*configure PWM Duty Cycle*/
 		 //OCR0B = (Copy_uint8_tDutyCycle*TIMER0_OCR0A_VALUE)/100;
 		OCR0B = Copy_uint8_tDutyCycle;
 	 //}else return;
 	 /*Start PWM*/
 	 TIMER0_voidStartTimer();

  }/*end of TIMER0_voidFastPWM()*/

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
 void TIMER0_voidPhaseCorrectPWM(uint8_t Copy_uint8_tDutyCycle)
 {
	/*configure PWM Duty Cycle*/
 	OCR2A = (Copy_uint8_tDutyCycle*(TIMER0_REG_CAPACITY-1))/100;
 	OCR2B = (Copy_uint8_tDutyCycle*(TIMER0_REG_CAPACITY-1))/100;
 	/*Start PWM*/
	TIMER0_voidStartTimer();

 }/*end of TIMER0_voidPhaseCorrectPWM()*/

 /*==================================================================================================================
  * EOF
  *==================================================================================================================*/

 #endif
