/*
 * voice.c
 *
 *  Created on: Oct 14, 2021
 *      Author: Lenovo
 */

#include "voice.h"
//#include "../Motor/motors.h"
#include "stdlib.h"

extern uint8_t auto_state;

void Compare_Action(){
	ADC_INT_DIS();

	uint32_t SR1 = ADC_readChannel(SEN1);

	uint32_t SR2 = ADC_readChannel(SEN2);

	if(SR1 > SR2){
		auto_state = 'R';
	}
	else if(SR1 == SR2){
		auto_state = 'F';
	}
	else{
		auto_state = 'L';
	}
	Bluetooth_Write(auto_state);
}

void Voice_Sensor_Init(){
	ADC_init();
	ADC_setCallBack(Compare_Action);
}
uint32_t sensorRead(uint8_t v_sensor){
	ADC_readChannel(v_sensor);
	//_delay_ms(30);
	return g_adcResult;
}


