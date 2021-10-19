/*
 * LED.c
 *
 *  Created on: Oct 12, 2021
 *      Author: ah132
 */

#include "../../HAL/LED/LED.h"
typedef unsigned char         uint8_t;

#include "avr/io.h"

void LED_Init(){
	DDRA = 0xff;
	PORTA = 0;
}

void LED_ON(){
	PORTA|= 1;

}
void LED_OFF(){
	PORTA &= ~1;

}
void LED2_ON(){
	PORTA |= 2;

}
void LED2_OFF(){
	PORTA &= ~(1<<2);

}
