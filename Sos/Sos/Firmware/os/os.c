/*
 * os.c
 *
 * Created: 03-Jan-20 1:42:22 PM
 *  Author: LENOVO
 */ 
/*- INCLUDES ----------------------------------------------*/
#include "os.h"
#include "pre_os.h"
#include "osPost.h"
#include <util/delay.h>
/*- LOCAL MACROS ------------------------------------------*/

#define TASK_READY         (SOS_STATUS_t)0U
#define TASK_RUNNING       (SOS_STATUS_t)1U
#define TASK_SUSPENDED     (SOS_STATUS_t)2U
#define TASK_STATE_DELETED (SOS_STATUS_t)3U
/*- LOCAL Dataypes ----------------------------------------*/
typedef struct 
{
    uint8_t priority;/*Not Used.gu8_SOS_New_System_Tick*/
    uint8_t state;/* Not Used. */
    uint32_t period_incrementer;/* if period_incrementer == period so task ready to run, incremented by system tick. */
}Str_SosTaskHandler_t;

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
static volatile uint8_t gu8_SOS_Is_Init;
static volatile uint8_t gu8_SOS_Prev_System_Tick;
static volatile uint8_t gu8_SOS_New_System_Tick;/* Reset every SuperLoop (LCM => Time). */
static volatile uint8_t gu8_SOS_Number_of_Created_Tasks;/* Number of tasks of created. */
static Str_SosTask_t gStr_SosTasks[SOS_MAX_TASKS];/* Array of tasks which created by user. */
static Str_SosTaskHandler_t gStr_TaskHandler[SOS_MAX_TASKS];/* Used by SOS To Handle Tasks. */
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*- APIs IMPLEMENTATION -----------------------------------*/

/**
 * @brief Init OS system.
 * @return SOS_STATUS_t 
 */
SOS_STATUS_t SOS_init(void)
{
    SOS_STATUS_t au8_response = SOS_INIT_SUCCESS;
    if(TRUE == gu8_SOS_Is_Init)
    {
        au8_response = SOS_REINIT_NOT_ALLOWED;
    }
    else
    {
        /* INIT Timing Source. */
	    Timer_Init(&timer_cfg);
	    Timer_Start(SOS_TIMER, SOS_SYSTEM_TICKS);
        Timer_setFlag(&gu8_SOS_New_System_Tick);/* Increment SOS time every System Tick. */
        gu8_SOS_Is_Init         = TRUE;
        /* Put prev_system_tick == new_system_tick just to force OS to enter Foor Loop for first time. */
        /* After first time the two variable will equal 1. */
        gu8_SOS_Prev_System_Tick = 0U;
        gu8_SOS_New_System_Tick  = 1U;
    }
    return au8_response;
}

/**
 * @brief run SOS.
 * 
 */
void SOS_Run(void)
{
    if( FALSE == gu8_SOS_Is_Init )
    {
        /* Do Noting. */
    }
    else
    {
        while ( TRUE )
        {
            /* New System Tick Coming. */
            if(gu8_SOS_Prev_System_Tick != gu8_SOS_New_System_Tick)
            {
                /* RUN OS. */
                for (uint8_t task = 0; task < SOS_MAX_TASKS; ++task)
                {
                    /* Priority == index (Task). */
                    /* Task With this priority is created. */
                    if(NULL != gStr_SosTasks[task].task_func)
                    {
                       
                        /* Priority == index (Task). */

                        /* TODO: Start at time. */
                        if(gStr_TaskHandler[task].period_incrementer >= gStr_SosTasks[task].period)
                        {
                            /* Run Task. */
                            gStr_SosTasks[task].task_func();
                            gStr_TaskHandler[task].period_incrementer = 0;
                            /* Handle Nature Logic Here. */
                            if( ONE_TIME_TASK == gStr_SosTasks[task].nature )
                            {
                                SOS_DeleteTask(task);
                            }
                            else
                            {
                                /* NOP. */
                            }
                        }
                        else
                        {
                            /* Increment period of task. */
                            gStr_TaskHandler[task].period_incrementer++;
                        }
                    }
                    else
                    {
                        /* No Tasks in Buffer. */
                    }
                }
                gu8_SOS_Prev_System_Tick = gu8_SOS_New_System_Tick;
            }
            else
            {
                /* code */
            }
        }
    }
}
/**
 * @brief SOS create task.
 * 
 * @param aPtr_Str_task 
 * @return SOS_STATUS_t 
 */
SOS_STATUS_t SOS_CreateTask(const Str_SosTask_t* aPtr_Str_task)
{
    SOS_STATUS_t au8_response = SOS_TASK_CREATED;
    /* Check if sos init. */
    if(TRUE != gu8_SOS_Is_Init)
    {
        au8_response = SOS_NOT_INIT;
    }
    else
    {
        /* Check if SOS_MAX_TASKS Can be handled by OS reached. */
        if(SOS_MAX_TASKS <= gu8_SOS_Number_of_Created_Tasks)
        {
            au8_response = SOS_MAX_TASKS_ALLOWED;
        }
        else
        {
            /* Check address of task if it's NULL. */
            if(NULL == aPtr_Str_task->task_func || NULL == aPtr_Str_task)
            {
                au8_response = SOS_TASK_CREATED_FAILED;
            }
            else
            {
                /* add new task. */
                gStr_SosTasks[aPtr_Str_task->priority].nature    = aPtr_Str_task->nature;
                gStr_SosTasks[aPtr_Str_task->priority].period    = aPtr_Str_task->period;
                gStr_SosTasks[aPtr_Str_task->priority].priority  = aPtr_Str_task->priority;
                gStr_SosTasks[aPtr_Str_task->priority].task_func = aPtr_Str_task->task_func; 

                /* add new task in OS Task Handler. */
                gStr_TaskHandler[aPtr_Str_task->priority].period_incrementer = 0U;
                gStr_TaskHandler[aPtr_Str_task->priority].state = TASK_READY;
                gStr_TaskHandler[aPtr_Str_task->priority].priority = aPtr_Str_task->priority;
                gu8_SOS_Number_of_Created_Tasks++;
            }
        }
        
    }
    return au8_response;
}

/**
 * @brief 
 * 
 * @param au8_priority 
 * @return SOS_STATUS_t 
 */
SOS_STATUS_t SOS_DeleteTask(const uint8_t au8_priority)
{
    SOS_STATUS_t au8_response = SOS_TASK_DELETED;
    if(FALSE == gu8_SOS_Is_Init)
    {
        au8_response = SOS_NOT_INIT;
    }
    else
    {
        /* I used priority as unique ID for each task. */
        if(au8_priority >= SOS_MAX_TASKS)
        {
            au8_response = SOS_NO_TASK_WITH_THIS_PRIORITY;
        }
        else
        {
            /* add new task. */
            gStr_SosTasks[au8_priority].nature = NULL;
            gStr_SosTasks[au8_priority].period = NULL;
            gStr_SosTasks[au8_priority].priority = NULL;
            gStr_SosTasks[au8_priority].task_func = NULL; 

            /* add new task in OS Task Handler. */
            gStr_TaskHandler[au8_priority].period_incrementer = NULL;
            gStr_TaskHandler[au8_priority].state = TASK_STATE_DELETED;
            gStr_TaskHandler[au8_priority].priority = NULL;
            gu8_SOS_Number_of_Created_Tasks--;
        }
        
    }
    return au8_response;
}
