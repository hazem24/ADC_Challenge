/*
 * app.c
 *
 * Created: 09-Jan-20 9:25:36 AM
 *  Author: LENOVO
 */ 


/*- INCLUDES ----------------------------------------------*/
#include "app.h"
#include "../MCAL/adc/adc.h"
#include "../HAL/lcd/lcd.h"
/*- LOCAL MACROS ------------------------------------------*/

/* Coordination of measured temp in LCD. */
#define TEMP_X  1U
#define TEMP_Y  8U
/*- LOCAL Dataypes ----------------------------------------*/
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
static Str_AdcConfig* gStr_adc_config;
/*- GLOBAL STATIC VARIABLES -------------------------------*/
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*- APIs IMPLEMENTATION -----------------------------------*/

void APP_init(Str_AdcConfig* Str_channel_confg)
{
    LCD_init();
    ADC_init(ADC_CLK_64);
    ADC_SetCallBack(APP_displayTemp);/* Print temp in ISR of ADC. */
    LCD_displayString("Temp = ");
    gStr_adc_config = Str_channel_confg;
}
/**
 * @brief this function used ADC to measure temp via temp sensor.
 * 
 */
void APP_measureTemp()
{
    if (NULL != gStr_adc_config)
    {
        ADC_Start(gStr_adc_config);
    }
    else
    {
        /* Do Noting. */
    }
    
}

/**
 * @brief 
 * 
 */
void APP_displayTemp(uint16_t au16_temp)
{
    LCD_goToRowColumn(TEMP_X, TEMP_Y);
    LCD_integerToString((au16_temp/4));
    LCD_displayString(" C");
}

