#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include "STD_TYPES"
#include "GPIO_INTERFACE.h"

/* Config */
#define LCD_DATA_PORT   GPIO_PORTB
#define LCD_CTRL_PORT   GPIO_PORTB

/* Control Pins */
#define LCD_RS_PIN      GPIO_PIN0
#define LCD_RW_PIN      GPIO_PIN1
#define LCD_EN_PIN      GPIO_PIN2

/* Data Pins (4-bit mode) */
#define LCD_D4          GPIO_PIN3
#define LCD_D5          GPIO_PIN4
#define LCD_D6          GPIO_PIN5
#define LCD_D7          GPIO_PIN6

/* Commands */
#define LCD_CLEAR       0x01
#define LCD_RETURN_HOME 0x02
#define LCD_ENTRY_MODE  0x06
#define LCD_ON          0x0C
#define LCD_4BIT_MODE   0x28 

/* Function Prototypes */
void LCD_Init(void);
void LCD_SendCommand(u8 cmd);
void LCD_SendChar(u8 data);
void LCD_SendString(const char* str);
void LCD_SetCursor(u8 row, u8 col);
void LCD_Clear(void);
void LCD_SendNumber(s32 Number);

#endif /* LCD_INTERFACE_H */
