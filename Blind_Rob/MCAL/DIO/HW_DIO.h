/*
 * HW_DIO.h
 */

#ifndef HW_DIO_H_
#define HW_DIO_H_

/************************************************************************
  	  	  	  	  	  	  	  Includes
 ***********************************************************************/
#include "../../Utils/std_types.h"
#include "../../Utils/common_macros.h"

/************************************************************************
  	  	  	  	  	  	  	  Registers Definitions
 ***********************************************************************/
/************************************************************************
  	  	  	  	  	  	  	  PORTx
 ***********************************************************************/
#define BASE_A *((volatile uint8_t*)(0x22))
#define BASE_B *((volatile uint8_t*)(0x25))
#define BASE_C *((volatile uint8_t*)(0x28))
#define BASE_D *((volatile uint8_t*)(0x2B))
#define BASE_E *((volatile uint8_t*)(0x2E))
#define BASE_F *((volatile uint8_t*)(0x31))
#define BASE_G *((volatile uint8_t*)(0x34))
#define BASE_H *((volatile uint8_t*)(0x102))
#define BASE_J *((volatile uint8_t*)(0x105))
#define BASE_K *((volatile uint8_t*)(0x108))
#define BASE_L *((volatile uint8_t*)(0x10B))

/************************************************************************
  	  	  	  	  	  	  	  DDRx
 ***********************************************************************/
#define DIR_A *((volatile uint8_t*)(0x21))
#define DIR_B *((volatile uint8_t*)(0x24))
#define DIR_C *((volatile uint8_t*)(0x27))
#define DIR_D *((volatile uint8_t*)(0x2A))
#define DIR_E *((volatile uint8_t*)(0x2D))
#define DIR_F *((volatile uint8_t*)(0x30))
#define DIR_G *((volatile uint8_t*)(0x33))
#define DIR_H *((volatile uint8_t*)(0x101))
#define DIR_J *((volatile uint8_t*)(0x104))
#define DIR_K *((volatile uint8_t*)(0x107))
#define DIR_L *((volatile uint8_t*)(0x10A))

/************************************************************************
  	  	  	  	  	  	  	  PINx
 ***********************************************************************/
#define PIN_A *((volatile uint8_t*)(0x20))
#define PIN_B *((volatile uint8_t*)(0x23))
#define PIN_C *((volatile uint8_t*)(0x26))
#define PIN_D *((volatile uint8_t*)(0x29))
#define PIN_E *((volatile uint8_t*)(0x2C))
#define PIN_F *((volatile uint8_t*)(0x2F))
#define PIN_G *((volatile uint8_t*)(0x32))
#define PIN_H *((volatile uint8_t*)(0x100))
#define PIN_J *((volatile uint8_t*)(0x103))
#define PIN_K *((volatile uint8_t*)(0x106))
#define PIN_L *((volatile uint8_t*)(0x109))

#define MCUCR *((volatile uint8_t*)(0x55))
#define PUD 4

#endif /* HW_DIO_H_ */
