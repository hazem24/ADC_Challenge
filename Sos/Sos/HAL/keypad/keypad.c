/*
 * keypad.c
 *
 * Created: 04-Jan-20 11:56:32 AM
 *  Author: LENOVO
 */ 

/*- INCLUDES ----------------------------------------------*/
#include "keypad.h"
/*- LOCAL MACROS ------------------------------------------*/
/* EXP => Expression. */
#define KEYPAD_ROWS_INIT(REG, EXP) REG = (REG | EXP)/* Rows output. */
#define KEYPAD_COLS_INIT(REG, EXP) REG = (REG & (~EXP))/* Cols is input. */

#define KEYPAD_STAGE_SCANNING               (KEYPAD_STATUS_t)0U
#define KEYPAD_STAGE_DEBOUNCE               (KEYPAD_STATUS_t)2U
#define KEYPAD_STAGE_MULTI_SWITCH_PREVENT   (KEYPAD_STATUS_t)1U
#define KEYPAD_STAGE_IDENTIFY               (KEYPAD_STATUS_t)3U

#define RESET_PIN(REG, row) REG = REG & ~(1 << (row + 2));
/*- LOCAL Dataypes ----------------------------------------*/
/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/*- GLOBAL STATIC VARIABLES -------------------------------*/
static KEYPAD_STATUS_t gu8_keypad_is_init;
static uint8_t gu8_KEYPAD_Read_Switch_Stage;/* Read Switch stages. */
/*- GLOBAL EXTERN VARIABLES -------------------------------*/
/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/
/*- APIs IMPLEMENTATION -----------------------------------*/


/**
 * @brief Keypad init.
 * 
 * @return KEYPAD_STATUS_t 
 */
KEYPAD_STATUS_t KEYPAD_init(void)
{
    KEYPAD_STATUS_t au8_response = KEYPAD_SUCESS;
    /* Check if keypad is init before. */
    if(TRUE == gu8_keypad_is_init)
    {
        au8_response = KEYPAD_REINIT_NOT_ALLOWED;
    }
    else
    {
        /* Init ports. */
        //KEYPAD_ROWS_INIT(KEYPAD_ROWS_DDR, KEYPAD_PINS_ROWS);
        DDRC   = 0b00011100;
        PORTC |=  0b11100000;
        //KEYPAD_COLS_INIT(KEYPAD_COLS_DDR, KEYPAD_PINS_COLS);
        gu8_KEYPAD_Read_Switch_Stage = KEYPAD_STAGE_SCANNING;
        gu8_keypad_is_init = TRUE;
    }
    return au8_response;
}


/**
 * @brief ReadInput
 * 
 * @param au8_ptr_data 
 * @return KEYPAD_STATUS_t 
 */
KEYPAD_STATUS_t KEYPAD_ReadInput(uint8_t* au8_ptr_data)
{
    KEYPAD_STATUS_t au8_response = KEYPAD_SUCESS;
    static sint8_t su8_col_selected = -1;
    static sint8_t su8_row_selected = -1;
    if(FALSE == gu8_keypad_is_init)
    {
        au8_response = KEYPAD_NOT_INIT;
    }
    else
    {
        switch (gu8_KEYPAD_Read_Switch_Stage)
        {
        case KEYPAD_STAGE_SCANNING:
            /* scan keypad. */
            /* Ground all rows. KEYPAD_PINS_ROWS & ~(KEYPAD_PINS_ROWS)*/
            KEYPAD_ROWS_PORT =  ~(1 << 2) & ~(1 << 3) & ~(1 << 4);
            /* Check value of columns if(all one's => same stage). */
            if((KEYPAD_COLS_PIN >> 5) != 0b111)
            {
                /* Key is pressed. */
                /* increment stages. */
                KEYPAD_ROWS_PORT =  (1 << 2) | (1 << 3) | (1 << 4);
                su8_col_selected =  (KEYPAD_COLS_PIN >> 5);
                gu8_KEYPAD_Read_Switch_Stage++;
            }
            else
            {
                /* NOP. */
            }
            break;
        case KEYPAD_STAGE_MULTI_SWITCH_PREVENT:
            gu8_KEYPAD_Read_Switch_Stage++;
            break;
        case KEYPAD_STAGE_DEBOUNCE:
            gu8_KEYPAD_Read_Switch_Stage++;
            break;
        case KEYPAD_STAGE_IDENTIFY:
            /*Check if key is pressed. */
            if((KEYPAD_COLS_PIN >> 5)  == su8_col_selected)
            {
                /* ground one row at a time => key. */
                for (uint8_t row = 0; row < KEYPAD_ROWS; ++row)
                {
                    /* row => ground. */
                    PORTC = PORTC & ~(1 << (row + 2));
                    for(uint8_t col = 0; col < KEYPAD_COLS; ++col)
                    {
                        if((KEYPAD_COLS_PIN >> 5)  == su8_col_selected)
                        {
                            *au8_ptr_data  = gu8_keypad_keys[row][col];
                        }
                        else
                        {
                            /* NOP. */
                        }
                    }
                    /* Return it back. */
                    PORTC = (1 << 2) | (1 << 3) | (1 << 4);
                    /* check columns col 0 */
                }
                gu8_KEYPAD_Read_Switch_Stage = KEYPAD_STAGE_SCANNING;
            }
            else
            {
                gu8_KEYPAD_Read_Switch_Stage = KEYPAD_STAGE_SCANNING;
            }
            break;

        default:
            gu8_KEYPAD_Read_Switch_Stage = KEYPAD_STAGE_SCANNING;
            break;
        }
    }
    return au8_response;
}






/*static uint8_t scan_keypad()
{
}*/