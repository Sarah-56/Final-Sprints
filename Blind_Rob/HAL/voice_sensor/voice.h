/*
 * voice.h
 *
 *  Created on: Oct 14, 2021
 *      Author: Lenovo
 */

#ifndef VOICE_ORDER_VOICE_H_
#define VOICE_ORDER_VOICE_H_

#include "../../MCAL/ADC/adc.h"
#include "../../Utils/std_types.h"
#include "../../Utils/common_macros.h"
#include "../Bluetooth/bluetooth.h"

//extern volatile uint16_t g_adcResult;

typedef enum{
	SEN1, SEN2
}sensor_num;

void Compare_Action();
void Voice_Sensor_Init();
uint32_t sensorRead(uint8_t v_sensor);


#endif /* VOICE_ORDER_VOICE_H_ */
