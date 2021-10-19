/*
 * DIO.h
 */

#ifndef DIO_H_
#define DIO_H_
/************************************************************************
  	  	  	  	  	  	  	  Includes
 ***********************************************************************/
#include "HW_DIO.h"
#include "../../Utils/std_types.h"
#include "../../Utils/common_macros.h"

/************************************************************************
  	  	  	  	  	  	  	  ENUMS
 ***********************************************************************/
typedef enum gpio_error {
	STATE_SUCCESS,
	STATE_ERROR,
	STATE_INVALID_ADDR,
	STATE_INVAILD_PIN,
	STATE_INVALID_DIR,
	STATE_PULLUP_OFF
} Error_t;

typedef enum{
	INPUT,
	OUTPUT
}Direction_t;

typedef enum{
	A, B, C, D, E, F, G, H, J, K, L
}PORT_t;

/************************************************************************
  	  	  	  	  	  	  	  STRUCTS & UNIONS
 ***********************************************************************/
typedef struct{
	uint8_t direction;
	uint8_t Data;
	PORT_t port;
}PORT_Config_t;

typedef struct{
	uint8_t direction;
	uint8_t pin_num;
	uint8_t Data;
	PORT_t port;
}PIN_Config_t;

/************************************************************************
  	  	  	  	  	  	  	  Function Decelerations
 ***********************************************************************/
void pin_init(PIN_Config_t* Pin);

void port_init(PORT_Config_t * Port);

uint8_t pin_read(PIN_Config_t * Pin);

void Write_Pin(PORT_t port, uint8_t pin, uint8_t Data);

void pin_write(PIN_Config_t* Pin, uint8_t val);

uint8_t port_read(PORT_Config_t * Port);

void port_write(PORT_Config_t * Port, uint8_t val);



#endif /* DIO_H_ */
