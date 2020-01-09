/*
 * pre_os.h
 *
 * Created: 03-Jan-20 2:39:59 PM
 *  Author: LENOVO
 */ 


#ifndef PRE_OS_H_
#define PRE_OS_H_

/*- INCLUDES -----------------------------------------------*/
#include "../../common/compiler.h"
#include "../../MCAL/timer/Timer.h"
/*- CONSTANTS ----------------------------------------------*/
#define SOS_MAX_TASKS     (uint8_t)5
#define SOS_SYSTEM_TICKS  (uint8_t)131 /* NUMBER of system ticks which will convert into time => 131 == 1 ms in 256 timer and prescaler 64, MC Freq 8MHZ */
#define SOS_TIMER         TIMER0 
/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/




#endif /* PRE_OS_H_ */