/*
 * preKeypad.h
 *
 * Created: 04-Jan-20 11:57:06 AM
 *  Author: LENOVO
 */ 


#ifndef PREKEYPAD_H_
#define PREKEYPAD_H_

/*- INCLUDES -----------------------------------------------*/
#include "../../micro_registers.h"
/*- CONSTANTS ----------------------------------------------*/
#define KEYPAD_ROWS  3
#define KEYPAD_COLS  3

/* DDR. */
#define KEYPAD_ROWS_DDR   DDRC
#define KEYPAD_COLS_DDR   DDRC

/* PORT. */
#define KEYPAD_ROWS_PORT  PORTC
#define KEYPAD_COLS_PORT  PORTC
/* PIN. */
#define KEYPAD_ROWS_PIN   PINC
#define KEYPAD_COLS_PIN   PINC

/* PINS OF ROWS. */
#define KEYPAD_PINS_ROWS ((uint8_t)0x1C) /* 0b00011100 */

/* PINS OF COLS. */
#define KEYPAD_PINS_COLS ((uint8_t)0xE0)/* 0b11100000 */

/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/




#endif /* PREKEYPAD_H_ */