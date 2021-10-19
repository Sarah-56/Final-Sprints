/*
 * motors.c
 *
 *  Created on: Sep 5, 2021
 *      Author: Bassant Yasser
 */


#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/Timer/Timer2/Timer2_Interface.h"
#include "motors.h"

typedef enum{
	low,
	high
}motor_state;

PIN_Config_t pd0 = {OUTPUT, 0, 0, D};
PIN_Config_t pd1 = {OUTPUT, 1, 0, D};
PIN_Config_t pd2 = {OUTPUT, 2, 0, D};
PIN_Config_t pd3 = {OUTPUT, 3, 0, D};

void motor_init()
{

	pin_init(&pd0);
	pin_init(&pd1);
	pin_init(&pd2);
	pin_init(&pd3);
	PIN_Config_t ph6 = {OUTPUT, 6, 0, H};
	pin_init(&ph6);
	TIMER2_voidInitializeTimer2();
}

void motor_start(uint8_t speed, Direction dir)
{
	set_mspeed(speed);
	set_direction(dir);
}

void set_mspeed(uint8_t duty_cycle)
{
	//TIMER2_voidFastPWM(duty_cycle, Channel_A2);
	//TIMER2_voidFastPWM(duty_cycle, Channel_B2);
}

void set_direction(uint8_t dir)
{
	switch(dir)
	{
	case Forward:
		pin_write(&pd0, 0);
		pin_write(&pd1, 1);
		pin_write(&pd2, 0);
		pin_write(&pd3, 1);
		break;
	case Backward:
		Write_Pin(D, 0, HIGH);
		Write_Pin(D, 1, low);
		Write_Pin(D, 2, HIGH);
		Write_Pin(D, 3, low);
		break;
	case Left:
		Write_Pin(D, 0, low);
		SET_BIT(BASE_D, 1);
		Write_Pin(D, 1, HIGH);
		Write_Pin(D, 2, HIGH);
		Write_Pin(D, 3, low);
		break;
	case Right:
		Write_Pin(D, 0, HIGH);
		Write_Pin(D, 1, low);
		Write_Pin(D, 2, low);
		Write_Pin(D, 3, HIGH);
		break;
	}
}

void motor_stop()
{
	Write_Pin(D, 0, low);
	Write_Pin(D, 1, low);
	Write_Pin(D, 2, low);
	Write_Pin(D, 3, low);
}
