/*
 * test_bluetooth.c
 *
 *  Created on: Oct 12, 2021
 *      Author: ah132
 */

#include "../../HAL/Bluetooth/bluetooth.h"
#include "../../HAL/LED/LED.h"
#include "app1.h"
#include "../../MCAL/UART/uart.h"

void Delay(unsigned long counter)
{
	unsigned long i = 0;

	for(i=0; i< counter; i++);
}

void Test_Bluetooth(void){
	HC05_init();
	//uart_start();
	LED_Init();
	unsigned char d = 'b';
	while(1){
		d= Bluetooth_Read();
		Delay(100);
		Bluetooth_Write(d);

		if(d == 'o'){
			LED_ON();
		}
		else{
			LED_OFF();
		}
	}


}
