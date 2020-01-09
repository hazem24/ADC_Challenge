/**
 * @file Timer.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-11-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "Timer.h"
#include "avr/interrupt.h"

static void fillPrescalersOptions();
static volatile uint8_t* ISR_flag = NULL;
/**
 * @brief this function used to calculate how many times, overflow should happen.
 * @param <uint32_t> ticks, <uint32_t> resoltuion. 
 * @return uint16_t 
 */
static void handleTimerStartingValue(uint8_t channel, uint32_t delay, uint16_t* number_of_overflow);


/**
 * @brief this function used to start delay.
 * @param <uint8_t> type of timer response, <uint8_t> delay_time.
 * @return void. 
 */
static void startDelay(uint8_t channel, uint16_t delay_counter);


static TimerConfiguration configuration[NUMBER_OF_CHANNELS];
/**
 * @brief Timer_Init initilize new timer instant.
 * @param <TimerConfiguration*> Pointer to Timer configuration struct.
 * @return void.
 */
void Timer_Init(TimerConfiguration* timer_cfg)
{
    /**
     * Fill all prescaler array.
     * set prescaler in timer control register.
     */
    fillPrescalersOptions();
    configuration[timer_cfg->channel].channel          = timer_cfg->channel;
    configuration[timer_cfg->channel].prescaler        = timer_cfg->prescaler;
    configuration[timer_cfg->channel].resolution       = timer_cfg->resolution;
    configuration[timer_cfg->channel].mode             = timer_cfg->mode;
    configuration[timer_cfg->channel].timer_mode       = timer_cfg->timer_mode;
	*(control_register[timer_cfg->channel]) = (*(control_register[timer_cfg->channel]) & CLEAR_CLOCK_BITS) | 3;
}

/**
 * @brief set flag to be incremented in timer0 ISR. 
 * @param flag 
 * @return void
 */
void Timer_setFlag(const volatile uint8_t* flag)
{
    ISR_flag = flag;
}

/**
 * @brief this function used to start timer.
 * @param <uint8_t> channel, <uint16_t> delay -> time to delay to milli-second.
 * @return void.
 */
void Timer_Start(uint8_t channel, uint16_t delay)
{
    /*
    * 1 - we have four inputs -> (F_CPU, prescaler, resolution).
    * So we need small calculation, for example -> 
    * 1 tick   -> F_CPU/prescaler
    * x ticks  -> delay (input).
        * if x in range of resolution -> timer should start from "resolution - x ticks."
        * else if out of range so we need to calculate overflow which should happen.
            * x ticks / resolution.   
    */
   uint16_t number_of_overflow;
   handleTimerStartingValue(channel, delay, &number_of_overflow);/* 247. */
   startDelay(channel, number_of_overflow);
}
 /** 
 * @brief this method used to stop timer.
 * @return void.
 */
void Timer_Stop(uint8_t channel)
{
    configuration[channel].prescaler        = 0;
    *(control_register[channel]) = (*(control_register[channel]) & CLEAR_CLOCK_BITS);
}

/**
 * @brief this function used to calculate how many times, overflow should happen.
 * @param <uint32_t> ticks, <uint32_t> resolution. 
 * @return uint16_t 
 */
static void handleTimerStartingValue(uint8_t channel, uint32_t delay, uint16_t* number_of_overflow)
{
    /*
    * 1 - we have four inputs -> (F_CPU, prescaler, resolution).
    * So we need small calculation, for example -> 
    * 1 tick   -> F_CPU/prescaler
    * x ticks  -> delay (input).
        * if x in range of resolution -> timer should start from "resolution - x ticks."
        * else if out of range so we need to calculate overflow which should happen.
            * x ticks / resolution.   
    */
   uint32_t ticks = (((uint64_t)MICRO_FREQ * delay)/(configuration[channel].prescaler * 1000));
   if(ticks > configuration[channel].resolution)
   {
       /* in this case we need to calculate how many times overflow or interrupt should happen. */
        *(timer_values_registers[channel]) = 0;/* starting of timer. */
        
        ticks = ((uint32_t)ticks/configuration[channel].resolution);/* in case of 2.3 should be handled. */
        *number_of_overflow = ticks;
   }else
   {
        *(timer_values_registers[channel]) = ticks;
        *number_of_overflow =  1;
   }
}
/**
 * @brief this function used to get timer value.
 * @param <uint8_t> channel.
 * @return uint16_t. 
 */
void Timer_getValue(uint8_t channel, uint16_t* value)
{
	*value = *(timer_values_registers[channel]);
}

void Timer_reset(uint8_t channel)
{
    *(timer_values_registers[channel]) = 0;
}
/**
 * @brief this function used to start delay.
 * @param <uint8_t> type of timer response, <uint8_t> delay_time.
 * @return void. 
 */
static void startDelay(uint8_t channel, uint16_t delay_counter)
{
	//delay_counter = 1;
    if(configuration[channel].mode == TIMER_MODE_POLLING)
    {
        /* POLLING LOGIC. */
        /* polling at TOV flag for delay_counter times. */
        uint16_t flag = 0;
        while(flag < delay_counter)/* read timer directly. */
        {
            while(BIT_IS_CLEAR(FLAGS_REGISTER, CHECKER_FLAG ));
            SET_BIT(FLAGS_REGISTER, CHECKER_FLAG);
            flag++;
        }

    }else
    {
        /* INTRRUPT LOGIC. */
        sei();
        TIMSK      = TIMSK | (1 << TOIE0);
    }
    
}

/**
 * @brief filling prescaler options.
 * @return void.
 */
static void fillPrescalersOptions()
{
    uint8_t i = 0;
    for(i = 0; i < NUMBER_OF_CLOCK_SOURCES;i++)
    {
        prescalers[i] = i;   
    }
}


ISR(TIMER0_OVF_vect)
{
    if(ISR_flag != NULL)
    {
        (*ISR_flag)++;
        *(timer_values_registers[TIMER0]) = 131;
    }
}