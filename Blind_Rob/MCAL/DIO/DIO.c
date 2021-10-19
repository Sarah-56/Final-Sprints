/*
 * DIO.c
 */

#include "DIO.h"


void pin_init(PIN_Config_t * Pin) {

	switch(Pin -> port){
	case A:
		if(Pin->direction){
			SET_BIT(DIR_A, Pin->pin_num);
		}else{
			CLEAR_BIT(DIR_A, Pin->pin_num);
		}
		break;
	case B:
		if(Pin->direction){
			SET_BIT(DIR_B, Pin->pin_num);
		}else{
			CLEAR_BIT(DIR_B, Pin->pin_num);
		}
		break;
		break;
	case C:
		if(Pin->direction){
			SET_BIT(DIR_C, Pin->pin_num);
		}else{
			CLEAR_BIT(DIR_C, Pin->pin_num);
		}
		break;
	case D:
		if(Pin->direction){
			SET_BIT(DIR_D, Pin->pin_num);
		}else{
			CLEAR_BIT(DIR_D, Pin->pin_num);
		}
		break;
	case E:
		if(Pin->direction){
			SET_BIT(DIR_E, Pin->pin_num);
		}else{
			CLEAR_BIT(DIR_E, Pin->pin_num);
		}
		break;
	case F:
		if(Pin->direction){
			SET_BIT(DIR_F, Pin->pin_num);
		}else{
			CLEAR_BIT(DIR_F, Pin->pin_num);
		}
		break;
	case G:
		if(Pin->direction){
			SET_BIT(DIR_G, Pin->pin_num);
		}else{
			CLEAR_BIT(DIR_G, Pin->pin_num);
		}
		break;
	case H:
		if(Pin->direction){
			SET_BIT(DIR_H, Pin->pin_num);
		}else{
			CLEAR_BIT(DIR_H, Pin->pin_num);
		}
		break;
	case J:
		if(Pin->direction){
			SET_BIT(DIR_J, Pin->pin_num);
		}else{
			CLEAR_BIT(DIR_J, Pin->pin_num);
		}
		break;
	case K:
		if(Pin->direction){
			SET_BIT(DIR_K, Pin->pin_num);
		}else{
			CLEAR_BIT(DIR_K, Pin->pin_num);
		}
		break;
	case L:
		if(Pin->direction){
			SET_BIT(DIR_L, Pin->pin_num);
		}else{
			CLEAR_BIT(DIR_L, Pin->pin_num);
		}
		break;
	}
}

void port_init(PORT_Config_t * Port) {
	switch(Port -> port){
		case A:
			DIR_A = Port->direction;
			break;
		case B:
			DIR_B = Port->direction;
			break;
		case C:
			DIR_C = Port->direction;
			break;
		case D:
			DIR_D = Port->direction;
			break;
		case E:
			DIR_E = Port->direction;
			break;
		case F:
			DIR_F = Port->direction;
			break;
		case G:
			DIR_G = Port->direction;
			break;
		case H:
			DIR_H = Port->direction;
			break;
		case J:
			DIR_J = Port->direction;
			break;
		case K:
			DIR_K = Port->direction;
			break;
		case L:
			DIR_L = Port->direction;
			break;
		}
}

uint8_t pin_read(PIN_Config_t * Pin) {
	switch(Pin -> port){
	case A:
		return BIT_IS_SET(BASE_A, Pin -> pin_num);
	case B:
		return BIT_IS_SET(BASE_B, Pin -> pin_num);
	case C:
		return BIT_IS_SET(BASE_C, Pin -> pin_num);
	case D:
		return BIT_IS_SET(BASE_D, Pin -> pin_num);
	case E:
		return BIT_IS_SET(BASE_E, Pin -> pin_num);
	case F:
		return BIT_IS_SET(BASE_F, Pin -> pin_num);
	case G:
		return BIT_IS_SET(BASE_G, Pin -> pin_num);
	case H:
		return BIT_IS_SET(BASE_H, Pin -> pin_num);
	case J:
		return BIT_IS_SET(BASE_J, Pin -> pin_num);
	case K:
		return BIT_IS_SET(BASE_K, Pin -> pin_num);
	case L:
		return BIT_IS_SET(BASE_L, Pin -> pin_num);
	}
	return 1;

}
void Write_Pin(PORT_t port, uint8_t pin, uint8_t Data){
	switch(port){
	case A:
		BASE_A = (BASE_A & (~(1<<pin))) | ((Data & 0x01) <<pin);
		break;
	case B:
		BASE_B = (BASE_B & (~(1<<pin))) | ((Data & 0x01) <<pin);
		break;
	case C:
		BASE_C = (BASE_C & (~(1<<pin))) | ((Data & 0x01) <<pin);
		break;
	case D:
		BASE_D = (BASE_D & (~(1<<pin))) | ((Data & 0x01) <<pin);
		break;
	case E:
		BASE_E = (BASE_E & (~(1<<pin))) | ((Data & 0x01) <<pin);
		break;
	case F:
		BASE_F = (BASE_F & (~(1<<pin))) | ((Data & 0x01) <<pin);
		break;
	case G:
		BASE_G = (BASE_G & (~(1<<pin))) | ((Data & 0x01) <<pin);
		break;
	case H:
		BASE_H = (BASE_H & (~(1<<pin))) | ((Data & 0x01) <<pin);
		break;
	case J:
		BASE_J = (BASE_J & (~(1<<pin))) | ((Data & 0x01) <<pin);
		break;
	case K:
		BASE_K = (BASE_K & (~(1<<pin))) | ((Data & 0x01) <<pin);
		break;
	case L:
		BASE_L = (BASE_L & (~(1<<pin))) | ((Data & 0x01) <<pin);
		break;
	}
}

void pin_write(PIN_Config_t* Pin, uint8_t val) {
	switch(Pin -> port){
	case A:
		if(val){
			SET_BIT(BASE_A, Pin -> pin_num);
		}else{
			CLEAR_BIT(BASE_A, Pin -> pin_num);
		}
		break;
	case B:
		if(val){
			SET_BIT(BASE_B, Pin -> pin_num);
		}else{
			CLEAR_BIT(BASE_B, Pin -> pin_num);
		}
		break;
	case C:
		if(val){
			SET_BIT(BASE_C, Pin -> pin_num);
		}else{
			CLEAR_BIT(BASE_C, Pin -> pin_num);
		}
		break;
	case D:
		if(val){
			SET_BIT(BASE_D, Pin -> pin_num);
		}else{
			CLEAR_BIT(BASE_D, Pin -> pin_num);
		}
		break;
	case E:
		if(val){
			SET_BIT(BASE_E, Pin -> pin_num);
		}else{
			CLEAR_BIT(BASE_E, Pin -> pin_num);
		}
		break;
	case F:
		if(val){
			SET_BIT(BASE_F, Pin -> pin_num);
		}else{
			CLEAR_BIT(BASE_F, Pin -> pin_num);
		}
		break;
	case G:
		if(val){
			SET_BIT(BASE_G, Pin -> pin_num);
		}else{
			CLEAR_BIT(BASE_G, Pin -> pin_num);
		}
		break;
	case H:
		if(val){
			SET_BIT(BASE_H, Pin -> pin_num);
		}else{
			CLEAR_BIT(BASE_H, Pin -> pin_num);
		}
		break;
	case J:
		if(val){
			SET_BIT(BASE_J, Pin -> pin_num);
		}else{
			CLEAR_BIT(BASE_J, Pin -> pin_num);
		}
		break;
	case K:
		if(val){
			SET_BIT(BASE_K, Pin -> pin_num);
		}else{
			CLEAR_BIT(BASE_K, Pin -> pin_num);
		}
		break;
	case L:
		if(val){
			SET_BIT(BASE_L, Pin -> pin_num);
		}else{
			CLEAR_BIT(BASE_L, Pin -> pin_num);
		}
		break;
	}

}
uint8_t port_read(PORT_Config_t * Port) {
	switch(Port -> port){
	case A:
		return BASE_A;
	case B:
		return BASE_B;
	case C:
		return BASE_C;
	case D:
		return BASE_D;
	case E:
		return BASE_E;
	case F:
		return BASE_F;
	case G:
		return BASE_G;
	case H:
		return BASE_H;
	case J:
		return BASE_J;
	case K:
		return BASE_K;
	case L:
		return BASE_L;
	}
	return 1;
}

void port_write(PORT_Config_t * Port, uint8_t val) {
	switch(Port -> port){
		case A:
			BASE_A = val;
			break;
		case B:
			BASE_B = val;
			break;
		case C:
			BASE_C = val;
			break;
		case D:
			BASE_D = val;
			break;
		case E:
			BASE_E = val;
			break;
		case F:
			BASE_F = val;
			break;
		case G:
			BASE_G = val;
			break;
		case H:
			BASE_H = val;
			break;
		case J:
			BASE_J = val;
			break;
		case K:
			BASE_K = val;
			break;
		case L:
			BASE_L = val;
			break;
		}
}

