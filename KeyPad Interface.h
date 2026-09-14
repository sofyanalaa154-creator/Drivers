#ifndef KEYPAD_INTERFACE_H
#define KEYPAD_INTERFACE_H

#include "STD_TYPES"
#include "GPIO_INTERFACE.h"

#define GPIO_LOW_NOT_ALL    0xF0  /* Columns (4..7) Output, Rows (0..3) Input */
#define GPIO_HIGH_ALL       0xFF  /* Pull-ups ON for Rows, Columns set HIGH */

#define Keypad_Arr { {'7','8','9','/'}, \
                     {'4','5','6','B'}, \
                     {'1','2','3','-'}, \
                     {'C','0','=','+'} }

#define KPD_Row1    GPIO_PIN0
#define KPD_Row2    GPIO_PIN1
#define KPD_Row3    GPIO_PIN2
#define KPD_Row4    GPIO_PIN3

#define KPD_col1    GPIO_PIN4
#define KPD_col2    GPIO_PIN5
#define KPD_col3    GPIO_PIN6
#define KPD_col4    GPIO_PIN7

#define KPD_ROWNUM  4
#define KPD_ColNUM  4

void KPD_Init(u8 copy_port);
u8 KPD_GetKey(u8 copy_u8port);

#endif /* KEYPAD_INTERFACE_H */
