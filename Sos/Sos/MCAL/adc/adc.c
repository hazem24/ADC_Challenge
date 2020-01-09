/*
 * adc.c
 *
 * Created: 08-Jan-20 8:25:56 AM
 *  Author: LENOVO
 */ 
/*- INCLUDES ----------------------------------------------*/
#include "adc.h"
#include "../../common/macros.h"
/*- LOCAL MACROS ------------------------------------------*/
/*- LOCAL Dataypes ----------------------------------------*/
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
static uint8_t gu8_adc_init;/* variable to indicate if adc is init or not. */
static volatile Adc_SampledData_Cbk gPtr_callBack;/* Adc call back function. */
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*- APIs IMPLEMENTATION -----------------------------------*/

/**
 * @brief 
 * 
 * @return ADC_STATUS_t 
 */
ADC_STATUS_t ADC_init(uint8_t au8_prescaler)
{
    ADC_STATUS_t au8_response  = ADC_SUCCESS;

    /* Check if module is init before. */
    if( TRUE == gu8_adc_init )
    {
        au8_response = ADC_ALREADY_INIT;
    }
    else
    {
        ADC_STATUS_REGISTER  |= (1 << ADC_ENABLE_BIT) | (1 << ADC_INTERRUPT_EN); 


        /* Setup prescaler. */
        ADC_STATUS_REGISTER |= au8_prescaler;

        sei();/* Enable global interrupt. */
        gu8_adc_init = TRUE;
    }
    return au8_response;
}

/**
 * @brief 
 * 
 * @param aPtr_adc_config 
 * @return ADC_STATUS_t 
 */
ADC_STATUS_t ADC_Start(Str_AdcConfig* aPtr_adc_config)
{
    ADC_STATUS_t au8_response  = ADC_SUCCESS;

    if( TRUE != gu8_adc_init )
    {
        au8_response = ADC_NOT_INIT;
    }
    else
    {
        /* Check if any conversion running now. */
        /* If there is adc channel used already and sampled data refused request. 
           but we can change it to accept this request in case 1 ADC clock passed, it saved in buffer.
        */
        if( TRUE == BIT_IS_CLEAR(ADC_STATUS_REGISTER, ADC_START_CONVERSION_BIT) )
        {
            /* ADC can accept conversion request. */
            //ADC_SELECTION_REGISTER = 0x00;/* clear selection register. */
            ADC_SELECTION_REGISTER = ADC_SELECTION_REGISTER | (aPtr_adc_config->channel);/* set it. */
            /* Reference voltage. */
            ADC_SELECTION_REGISTER = ADC_SELECTION_REGISTER | (aPtr_adc_config->refernce_voltage << 6);/* set it. */

            /* Start Conversion. */
            SET_BIT(ADC_STATUS_REGISTER, ADC_START_CONVERSION_BIT);
        }
        else
        {
            au8_response = ADC_BUSY;
        }
        
    }
    return au8_response;
}

/**
 * @brief Set way to put callback function for adc module. 
 * @param aPtr_Func 
 * @return ADC_STATUS_t 
 */
ADC_STATUS_t ADC_SetCallBack(Adc_SampledData_Cbk aPtr_Func)
{
    ADC_STATUS_t au8_response = ADC_SUCCESS;
    if(NULL == aPtr_Func)
    {
        au8_response = ADC_CALLBACK_ON_NULL;
    }
    else
    {
        gPtr_callBack = aPtr_Func;
    }
    return au8_response;
}

/* Interrupt handler of ADC.  */
ISR(ADC_vect)
{
    if( NULL != gPtr_callBack )
    {
        gPtr_callBack(ADC);
    }
}