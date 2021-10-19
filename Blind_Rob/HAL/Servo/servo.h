/*
 * servo.h
 *
 *  Created on: Oct 13, 2021
 *      Author: Lenovo
 */

#ifndef SERVO_SERVO_H_
#define SERVO_SERVO_H_



#include "../../Utils/std_types.h"
#include "../../Utils/common_macros.h"

typedef enum{
	S1, S2
}servo_num;

void Servo_Init();
void Increase_angle(servo_num ser_num);
void Decrease_angle(servo_num ser_num);

#endif /* SERVO_SERVO_H_ */
