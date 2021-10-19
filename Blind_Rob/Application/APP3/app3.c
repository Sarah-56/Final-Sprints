/*
 * app3.c
 *
 *  Created on: Oct 14, 2021
 *      Author: ah132
 */


#include "test_adc.h"
#include "../../MCAL/ADC/adc.h"
#include "../../HAL/LED/LED.h"
#include "../../HAL/Bluetooth/bluetooth.h"
#include <stdlib.h>

void testadc(){
	int sen1=0;
	int sen2=0, sen3=0;
	ADC_init();
	LED_Init();
	HC05_init();
	char String[5];
	while(1){
		ADC_readChannel(0);
		sen1 = ((uint32_t)g_adcResult*150*5)/(1023*1.5);
		itoa(sen1,String,10);	/* Integer to string conversion */
		Bluetooth_Write_String(String);
		Bluetooth_Write('-');
		ADC_readChannel(1);
		sen2= ((uint32_t)g_adcResult*150*5)/(1023*1.5);
		itoa(sen2,String,10);	/* Integer to string conversion */
		Bluetooth_Write_String(String);
		Bluetooth_Write('-');
		ADC_readChannel(2);
		sen3= ((uint32_t)g_adcResult*150*5)/(1023*1.5);
		itoa(sen3,String,10);	/* Integer to string conversion */
		Bluetooth_Write_String(String);
		Bluetooth_Write('\r');
		if(sen1){
			LED_ON();
		}else{
			LED_OFF();
		}
		if(sen2){
			LED2_ON();

		}else{
			LED2_OFF();
		}

	}

}
