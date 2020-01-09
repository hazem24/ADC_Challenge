/*
 * adc.h
 *
 * Created: 08-Jan-20 8:25:47 AM
 *  Author: LENOVO
 */ 


#ifndef ADC_H_
#define ADC_H_

/*- INCLUDES -----------------------------------------------*/
#include "../../common/compiler.h"
#include "preADC.h"

typedef uint8_t ADC_STATUS_t;
typedef void (*Adc_SampledData_Cbk) (uint16_t);
/*- CONSTANTS ----------------------------------------------*/
#define ADC_BASE_STATUS_CODE  ((ADC_STATUS_t) 1) 
#define ADC_SUCCESS           (ADC_BASE_STATUS_CODE)
#define ADC_ALREADY_INIT      (ADC_BASE_STATUS_CODE + 1)
#define ADC_CALLBACK_ON_NULL  (ADC_BASE_STATUS_CODE + 2)
#define ADC_NOT_INIT          (ADC_BASE_STATUS_CODE + 3)
#define ADC_BUSY              (ADC_BASE_STATUS_CODE + 3)
/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct 
{
    uint8_t refernce_voltage;
    uint8_t channel;
}Str_AdcConfig;

/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/


/**
 * @brief 
 * 
 * @return ADC_STATUS_t 
 */
ADC_STATUS_t ADC_init(uint8_t au8_prescaler);

/**
 * @brief 
 * 
 * @param aPtr_adc_config 
 * @return ADC_STATUS_t 
 */
ADC_STATUS_t ADC_Start(Str_AdcConfig* aPtr_adc_config);

/**
 * @brief Set way to put callback function for adc module. 
 * @param aPtr_Func 
 * @return ADC_STATUS_t 
 */
ADC_STATUS_t ADC_SetCallBack(Adc_SampledData_Cbk aPtr_Func);
#endif /* ADC_H_ */