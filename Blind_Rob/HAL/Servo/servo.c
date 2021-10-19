/*
 * servo.c
 *
 *  Created on: Oct 13, 2021
 *      Author: Lenovo
 */

#include "servo.h"

#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/Timer/Timer0/Timer0_Interface.h"
#include "../../MCAL/Timer/Timer2/Timer2_Interface.h"



uint8_t duty_cycle_S1 = 6;
uint8_t duty_cycle_S2 = 6;

void Servo_Init(){
	//three pins initialization
	PIN_Config_t pc7 = {OUTPUT, 7, 0, C};
	PIN_Config_t pg5 = {OUTPUT, 5, 0, G};
	PIN_Config_t pb4 = {OUTPUT, 4, 0, B};
	pin_init(&pc7);
	pin_init(&pg5);
	pin_init(&pb4);

	TIMER0_voidInitializeTIMER0();
	TIMER2_voidInitializeTimer2();
	TIMER0_voidFastPWM(duty_cycle_S1);
	TIMER2_voidFastPWM(duty_cycle_S2);

}

void Increase_angle(servo_num ser_num)
{
	switch(ser_num){
	case 0:
		duty_cycle_S1 = duty_cycle_S1 < 15? duty_cycle_S1 +1 : duty_cycle_S1;
		TIMER0_voidFastPWM(duty_cycle_S1);
		break;
	case 1:
		duty_cycle_S2 = duty_cycle_S2 < 15? duty_cycle_S2 +1 : duty_cycle_S2;
		TIMER2_voidFastPWM(duty_cycle_S2);
		break;
//	case 2:
//		TIMER2_voidFastPWM(duty_cycle, Channel_A2);
//		break;
	}
}


void Decrease_angle(servo_num ser_num)
{
	switch(ser_num){
	case 0:
		duty_cycle_S1 = duty_cycle_S1 > 6? duty_cycle_S1 -1 : duty_cycle_S1;
		TIMER0_voidFastPWM(duty_cycle_S1);
		break;
	case 1:
		duty_cycle_S2 = duty_cycle_S2 > 6? duty_cycle_S2 -1 : duty_cycle_S2;
		TIMER2_voidFastPWM(duty_cycle_S2);
		break;
//	case 2:
//		TIMER2_voidFastPWM(duty_cycle, Channel_A2);
//		break;
	}
}
