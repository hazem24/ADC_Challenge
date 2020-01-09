/*
 * Timer_Config.c
 *
 * Created: 06-Dec-19 3:56:40 PM
 *  Author: LENOVO
 */ 

#include "Timer_Config.h"

volatile uint8_t* control_register[NUMBER_OF_CHANNELS] = {
    &TCCR0,
    &TCCR1B,
    &TCCR2,
};

/* until now i handle 8-bit timer only. */
volatile uint8_t* timer_values_registers[NUMBER_OF_CHANNELS] = 
{
    &TCNT0,
    &TCNT1L,
    &TCNT2
};
/**
 * @brief array contains all type of sources of clock.
 * this array fill at calling INIT function.
 */
volatile uint8_t prescalers[NUMBER_OF_CLOCK_SOURCES] = {0};