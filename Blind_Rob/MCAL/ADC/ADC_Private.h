/*
 * ADC_Private.h
 *
 *  Created on: Oct 14, 2021
 *      Author: ah132
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define ADMUX	(*(volatile uint8_t *)(0x7C))
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define MUX4    4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0

#define ADCSRB	(*(volatile uint8_t *)(0x7B))
#define ACME    6
#define MUX5    3
#define ADTS2   2
#define ADTS1   1
#define ADTS0   0

#define ADCSRA	(*(volatile uint8_t *)(0x7A))
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0

#define DIDR0	(*(volatile uint8_t *)(0x7E))
#define ADC7D   7
#define ADC6D   6
#define ADC5D   5
#define ADC4D   4
#define ADC3D   3
#define ADC2D   2
#define ADC1D   1
#define ADC0D   0


#define ADC 	(*(volatile uint16_t *)(0x78))

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
