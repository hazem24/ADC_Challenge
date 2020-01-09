/*
 * osPost.c
 *
 * Created: 04-Jan-20 10:26:46 AM
 *  Author: LENOVO
 */ 
#include "../../MCAL/timer/Timer.h"
/* Config Timer. */
TimerConfiguration timer_cfg = { TIMER0, TIMER_PRESCALER_64, TIMER_MODE_TIMER, TIMER_MODE_INTERRUPT, TIMER_255 };
