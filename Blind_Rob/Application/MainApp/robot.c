/*
 * robot.c
 *
 *  Created on: Oct 16, 2021
 *      Author: Lenovo
 */

#include "robot.h"

uint8_t system_state = '1';


void MainApp(){
	HC05_init();
	motor_init();
	Servo_Init();

	uint8_t key ;
	while(1){

		switch(system_state){
		case '0': //auto
			//enable interrupt
			//standby();
			break;
		case '1': // manual
			 key = Bluetooth_Read();
			 Bluetooth_Write(key);
			switch(key){
			case '0':
				motor_start(50, Forward);
				break;
			case '1':
				motor_start(50, Right);
				break;
			case '2':
				motor_start(50, Left);

				break;
			case '3':
				motor_stop();
				break;

			case '4'://switch to auto state
				//call fn to enable uart interrupt "will be done ISA :("
				system_state = 0;
				sei();
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
