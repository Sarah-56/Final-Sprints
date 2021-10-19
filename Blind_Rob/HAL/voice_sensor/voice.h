/*
 * voice.h
 *
 *  Created on: Oct 14, 2021
 *      Author: Lenovo
 */

#ifndef VOICE_ORDER_VOICE_H_
#define VOICE_ORDER_VOICE_H_

#include "../../MCAL/ADC/ADC_Private.h"
#include "../../Utils/std_types.h"

extern volatile uint16_t g_adcResult;

typedef enum{
	SEN1, SEN2
}sensor_num;

uint32_t sensorRead(uint8_t v_sensor);
uint8_t compare();

#endif /* VOICE_ORDER_VOICE_H_ */
