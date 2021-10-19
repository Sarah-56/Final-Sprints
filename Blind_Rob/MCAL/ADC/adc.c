 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#include "adc.h"
#include "avr/io.h"
#include "../../HAL/LED/LED.h"
/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

volatile uint16_t g_adcResult = 0;
static volatile void (*ADC_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/
void __vector_29 (void) __attribute__ ((signal,used));//Declaration
void __vector_29(void)/*ADC ISR*/ //Definition
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
	if(ADC_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*ADC_callBackPtr)();
	}



}/*end of __vector_29()*/


/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
void ADC_INT_EN(){
	ADCSRA |= (1<<ADIE);
}
void ADC_INT_DIS(){
	ADCSRA &= ~(1<<ADIE);
}
void ADC_init(void)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = 0;
	CLEAR_BIT(ADCSRB, MUX5);
	DDRF =0;

	//ADCSRB &=~(1<<MUX5);


	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 1 Enable ADC Interrupt ----  | (1<<ADIE)
	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN)  | (1<<ADPS1) | (1<<ADPS0);
	DIDR0 = 1<<ADC0D | 1<<ADC1D | 1<<ADC2D;
}

uint32_t ADC_readChannel(uint8_t channel_num)
{
	channel_num &= 0x07; 			/* channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; 					/* clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; 	/* choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); 			/* start conversion write '1' to ADSC */
	while((ADCSRA&(1<<ADIF))==0);	/* Monitor end of conversion interrupt */
	g_adcResult = ADC;
	return ((uint32_t)g_adcResult*150*5)/(1023*1.5);
}

void ADC_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	ADC_callBackPtr = a_ptr;
}

