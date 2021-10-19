#include "Application/App1/app1.h"
#include "Application/App2/test_dio.h"
#include "Application/APP3/test_adc.h"
#include "Application/MainApp/robot.h"
#include <util/delay.h>
#include "HAL/Servo/servo.h"
#include "HAL/Motor/motors.h"

//#include "MCAL/UART/uart.h"
//#include "ECUAL/LED/LED.h"

int main(){
	MainApp();
	return  0;
}
