/**
 * @file Timer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-11-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include "../../common/compiler.h"
#include "../../common/macros.h"
#include "Timer_Config.h"



#define TIMER_MODE_COUNTER 0
#define TIMER_MODE_TIMER   1
 

#define TIMER_MODE_INTERRUPT 0
#define TIMER_MODE_POLLING   1


#define TIMER_255  256
#define TIMER_1024 65535

#define TIMER_NO_PRESCALER        1
#define TIMER_PRESCALER_8         8
#define TIMER_PRESCALER_64        64
#define TIMER_PRESCALER_256       256
#define TIMER_PRESCALER_1024      1024

#define CLEAR_CLOCK_BITS 0xF8
/**
 * @brief This struct contains all configuration needed for timer.
 */
typedef struct 
{
    uint8_t channel;
    uint16_t prescaler;
    uint8_t timer_mode;/* counter or timer. */
    uint8_t mode; /* polling or interrupt. */
    uint16_t resolution;/* 256, 65535 */
}TimerConfiguration;



/**
 * @brief Timer_Init initilize new timer instant.
 * @param <TimerConfiguration*> Pointer to Timer configuration struct.
 * @return void.
 */
void Timer_Init(TimerConfiguration* timer_cfg);


/**
 * @brief this function used to start timer.
 * @param <u8> channel, <u16> delay -> time to delay to milli-second.
 * @return void.
 */
void Timer_Start(uint8_t channel, uint16_t delay);

 /** 
 * @brief this method used to stop timer.
 * @return void.
 */
void Timer_Stop(uint8_t channel);

/**
 * @brief this function used to get timer value.
 * @param <u8> channel.
 * @return u16. 
 */
void Timer_getValue(uint8_t channel, uint16_t* value);

/**
 * @brief set flag to be incremented in timer0 ISR. 
 * @param flag 
 * @return void
 */
void Timer_setFlag(const volatile uint8_t* flag);


void Timer_reset(uint8_t channel);
#endif