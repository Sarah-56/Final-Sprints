///*
// * App2.c
// *
// *  Created on: Oct 12, 2021
// *      Author: ah132
// */
//
//#include "../../HAL/LED/LED.h"
//#include "../../MCAL/Timer/Timer2/Timer2_Interface.h"
//#include "test_dio.h"
//
//
//void op(){
//	LED_ON();
//}
//
//void test_dio(){
//
//
//	while(1){
//
//
//	}
//}
//
//

#include "../../HAL/LED/LED.h"
#include "../../MCAL/Timer/Timer0/Timer0_Interface.h"
#include "../../MCAL/Timer/Timer2/Timer2_Interface.h"

#include "test_dio.h"


void op(){
	LED_ON();
}

void test_dio(){
	TIMER0_voidInitializeTIMER0();
	TIMER2_voidInitializeTimer2();
	//timer2_d(12);
	TIMER0_voidFastPWM(10);
	TIMER2_voidFastPWM(89);
	while(1){


	}
}
