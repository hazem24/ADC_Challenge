/*
 * os.h
 *
 * Created: 03-Jan-20 1:42:43 PM
 *  Author: LENOVO
 */ 


#ifndef OS_H_
#define OS_H_

/*- INCLUDES -----------------------------------------------*/
#include "../../common/compiler.h"

typedef uint8_t SOS_STATUS_t;
typedef void (*SOS_Task_Cbk_t) (void);
/*- CONSTANTS ----------------------------------------------*/
#define SOS_BASE_STATUS_CODE            (SOS_STATUS_t)1
#define SOS_INIT_SUCCESS                SOS_BASE_STATUS_CODE
#define SOS_REINIT_NOT_ALLOWED          (SOS_STATUS_t) (SOS_BASE_STATUS_CODE + 1)
#define SOS_NO_HARDWARE_AVAILABLE       (SOS_STATUS_t) (SOS_BASE_STATUS_CODE + 2) 
#define SOS_MAX_TASKS_ALLOWED           (SOS_STATUS_t) (SOS_BASE_STATUS_CODE + 3)  
#define SOS_TASK_CREATED                (SOS_STATUS_t) (SOS_BASE_STATUS_CODE + 4)
#define SOS_TASK_CREATED_FAILED         (SOS_STATUS_t) (SOS_BASE_STATUS_CODE + 5)
#define SOS_NOT_INIT                    (SOS_STATUS_t) (SOS_BASE_STATUS_CODE + 6)
#define SOS_TASK_DELETED                (SOS_STATUS_t) (SOS_BASE_STATUS_CODE + 7)
#define SOS_NO_TASK_WITH_THIS_PRIORITY  (SOS_STATUS_t) (SOS_BASE_STATUS_CODE + 8)
/* Tasks Nature. */
#define ONE_TIME_TASK  0U
#define PRIODIC_TASK   1U  
/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct 
{
    uint8_t priority;
    uint8_t nature;/* One Time oR Periodic. */
    uint32_t period;
    SOS_Task_Cbk_t task_func;/* Task Func. */
}Str_SosTask_t;

/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/

/**
 * @brief Init OS system.
 * @return SOS_STATUS 
 */
SOS_STATUS_t SOS_init(void);


/**
 * @brief run SOS.
 * 
 */
void SOS_Run(void);

/**
 * @brief SOS create task.
 * 
 * @param aPtr_Str_task 
 * @return SOS_STATUS_t 
 */
SOS_STATUS_t SOS_CreateTask(const Str_SosTask_t* aPtr_Str_task);

/**
 * @brief SOS_DeleteTask
 * @param au8_priority 
 * @return SOS_STATUS_t 
 */
SOS_STATUS_t SOS_DeleteTask(const uint8_t au8_priority);
#endif /* OS_H_ */