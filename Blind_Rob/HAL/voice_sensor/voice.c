/*
 * voice.c
 *
 *  Created on: Oct 14, 2021
 *      Author: Lenovo
 */

#include "voice.h"


uint32_t sensorRead(uint8_t v_sensor){
	ADC_readChannel(v_sensor);
	//_delay_ms(30);
	return g_adcResult;
}

uint8_t compare(){

}
