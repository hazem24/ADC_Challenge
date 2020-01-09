/*
 * app.h
 *
 * Created: 09-Jan-20 9:26:32 AM
 *  Author: LENOVO
 */ 


#ifndef APP_H_
#define APP_H_

/*- INCLUDES -----------------------------------------------*/
#include "../MCAL/adc/adc.h"
/*- CONSTANTS ----------------------------------------------*/
#define SENSOR_CHANNEL_NUMBER    ADC0
/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/

void APP_init(Str_AdcConfig*);


void APP_measureTemp();


void APP_displayTemp(uint16_t);

#endif /* APP_H_ */