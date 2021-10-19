/*
 * bluetooth.c
 *
 *  Created on: Oct 12, 2021
 *      Author: ah132
 */

#include "../../MCAL/UART/uart.h"
#include "bluetooth.h"

extern uint8_t system_state;

void Bluetooth_ISR(){
	uint8_t data = USART_Receive();
	//20 is a magic number
	if(data == 20){
		//switch system state & disable interrupt
		system_state ^= 1;
		cli();

	}
}
void HC05_init(void)
{
	//USART_Init();
	uart_start();
	int_setCallBack(Bluetooth_ISR);

}
char Bluetooth_Read(void)
{
	return USART_Receive();
}


void Bluetooth_Write(unsigned char data)
{
	//USART_Transmit(data);
	uart_sendint(data);
}

void Bluetooth_Write_String(char *str)
{
  while(*str)
	{
		Bluetooth_Write(*(str++));
	}
}


