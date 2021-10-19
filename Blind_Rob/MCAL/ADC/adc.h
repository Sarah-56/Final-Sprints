 /******************************************************************************
 *
 * adc.h
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

//#include "../../micro_config.h"
#include "../../Utils/std_types.h"
#include "../../Utils/common_macros.h"
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern Public global variables to be used by other modules */
extern volatile uint16_t g_adcResult;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(void);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
void ADC_readChannel(uint8_t channel_num);

#endif /* ADC_H_ */
