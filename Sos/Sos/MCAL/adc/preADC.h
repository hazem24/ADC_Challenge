/*
 * preADC.h
 *
 * Created: 08-Jan-20 1:17:27 PM
 *  Author: LENOVO
 */ 


#ifndef PREADC_H_
#define PREADC_H_
/*- INCLUDES -----------------------------------------------*/
#include "../../micro_registers.h"
/*- CONSTANTS ----------------------------------------------*/
#define ADC_INTERNAL_VOLTAGE   (uint8_t) 3       
#define ADC_EXTERNAL_VOLTAGE   (uint8_t) 1


#define ADC_DATA_REGISTER               ADC 
#define ADC_SELECTION_REGISTER          ADMUX
#define ADC_STATUS_REGISTER             ADCSRA

#define ADC_START_CONVERSION_BIT        ADSC
#define ADC_INTERRUPT_FLAG              ADIF
#define ADC_INTERRUPT_EN                ADIE
#define ADC_ENABLE_BIT                  ADEN
/* Channels Single ended. */
#define ADC0                        0U
#define ADC1                        1U
#define ADC2                        2U
#define ADC3                        3U
#define ADC4                        4U
#define ADC5                        5U
#define ADC6                        6U
#define ADC7                        7U


/* Prescaler. */
#define ADC_CLK_2                         1U
#define ADC_CLK_4                         2U
#define ADC_CLK_8                         3U
#define ADC_CLK_16                        4U
#define ADC_CLK_32                        5U
#define ADC_CLK_64                        6U
#define ADC_CLK_128                       7U

/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif /* PREADC_H_ */