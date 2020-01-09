/**
 * @file Timer_Config.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-11-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

#include "../../common/compiler.h"
#include "../../micro_registers.h"
#include "../../micro_config.h"

#define MICRO_FREQ F_CPU
 
/* define BITS. */
#define TIMER_BIT0 0
#define TIMER_BIT1 1
#define TIMER_BIT2 2
#define TIMER_BIT3 3
#define TIMER_BIT4 4
#define TIMER_BIT5 5
#define TIMER_BIT6 6
#define TIMER_BIT7 7

/* Number of timers channels in the target. */
#define NUMBER_OF_CHANNELS      3


#define TIMER0    (0)
#define TIMER1    (1)
#define TIMER2    (2)  


#define CHECKER_FLAG   TOV0
#define FLAGS_REGISTER TIFR


#define NUMBER_OF_CLOCK_SOURCES 8

#define BITS_PER_REGISTER       8

extern volatile uint8_t* control_register[NUMBER_OF_CHANNELS];

/* until now i handle 8-bit timer only. */
extern volatile uint8_t* timer_values_registers[NUMBER_OF_CHANNELS];
/**
 * @brief array contains all type of sources of clock.
 * this array fill at calling INIT function.
 */
extern volatile uint8_t prescalers[NUMBER_OF_CLOCK_SOURCES];

#endif