/*
 * robot.c
 *
 *  Created on: Oct 16, 2021
 *      Author: Lenovo
 */

#include "robot.h"
#include "../../MCAL/UART/uart.h"
#include "../../MCAL/ADC/adc.h"

uint8_t system_state = '1';
uint8_t auto_state = 'F';


void MainApp(){
	sei();
	HC05_init();
	motor_init();
	Servo_Init();
	ADC_init();
	Voice_Sensor_Init();
	uint8_t key;

	while(1){

		switch(system_state){
		case '0': //auto
			ADC_INT_EN();
			//enable interrupt
			//standby();
			Compare_Action();

			while(auto_state == 'S');

			if(auto_state == 'R'){

				motor_start(100, Right);


			}else if(auto_state == 'L'){

				motor_start(100, Left);


			}else if(auto_state == 'F'){

				motor_start(100, Forward);

			}
//			switch(auto_state){
//
//			case 'F':
//				motor_start(100, Forward);
//				break;
//			case 'R':
//				motor_start(100, Right);
//				break;
//			case 'L':
//				motor_start(100, Left);
//				break;
//			default:
//				motor_stop();
//				break;
//			}
			Delay(500);
			motor_stop();
			auto_state = 'S';
			USART_INT_EN();
			ADC_INT_EN();
			break;
		case '1': // manual
			USART_INT_DIS();
			 key = Bluetooth_Read();
			 Bluetooth_Write(key);
			switch(key){
			case '0':
				motor_start(100, Forward);
				break;
			case '1':
				motor_start(100, Right);
				break;
			case '2':
				motor_start(100, Left);

				break;
			case '3':
				motor_stop();
				break;

			case '4'://switch to auto state
				//call fn to enable uart interrupt "will be done ISA :("
				system_state = '0';
				USART_INT_EN();
				ADC_INT_EN();
				break;
			//4 cases for servo
			case '5':
				Increase_angle(S1);
				break;
			case '6':
				Decrease_angle(S1);
				break;
			case '7':
				Increase_angle(S2);
				break;
			case '8':
				Decrease_angle(S2);
				break;
			}
			break;
		}



	}
}
