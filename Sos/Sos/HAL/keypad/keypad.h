/*
 * keypad.h
 *
 * Created: 04-Jan-20 11:56:47 AM
 *  Author: LENOVO
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

/*- INCLUDES -----------------------------------------------*/
#include "preKeypad.h"
#include "../../micro_registers.h"
#include "../../common/compiler.h"
#include "linkKeypad.h"

typedef uint8_t KEYPAD_STATUS_t;
/*- CONSTANTS ----------------------------------------------*/
#define KEYPAD_BASE_STATUS_CODE     (KEYPAD_STATUS_t)10
#define KEYPAD_SUCESS               (KEYPAD_BASE_STATUS_CODE)
#define KEYPAD_REINIT_NOT_ALLOWED   (KEYPAD_BASE_STATUS_CODE + 1U)
#define KEYPAD_NOT_INIT             (KEYPAD_BASE_STATUS_CODE + 2U)
/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/

/**
 * @brief Keypad init.
 * 
 * @return KEYPAD_STATUS_t 
 */
KEYPAD_STATUS_t KEYPAD_init(void);
 
/**
 * @brief ReadInput
 * 
 * @param au8_ptr_data 
 * @return KEYPAD_STATUS_t 
 */
KEYPAD_STATUS_t KEYPAD_ReadInput(uint8_t* au8_ptr_data);




#endif /* KEYPAD_H_ */