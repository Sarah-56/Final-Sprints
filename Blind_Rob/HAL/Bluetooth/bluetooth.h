/*
 * bluetooth.h
 *
 *  Created on: Oct 12, 2021
 *      Author: ah132
 */

#ifndef HAL_BLUETOOTH_BLUETOOTH_H_
#define HAL_BLUETOOTH_BLUETOOTH_H_



void Bluetooth_ISR();

void HC05_init(void);

char Bluetooth_Read(void);

void Bluetooth_Write(unsigned char data);

void Bluetooth_Write_String(char *str);


#endif /* HAL_BLUETOOTH_BLUETOOTH_H_ */
