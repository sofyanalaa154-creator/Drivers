#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include "LCD_INTERFACE.h"

static void LCD_EnablePulse(void) {
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_HIGH);
    _delay_us(10); 
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_LOW);
    _delay_us(100);
}

static void LCD_send4bit(u8 value) {
    GPIO_VidSetPinValue(LCD_DATA_PORT, LCD_D4, (value >> 0) & 0x01);
    GPIO_VidSetPinValue(LCD_DATA_PORT, LCD_D5, (value >> 1) & 0x01);
    GPIO_VidSetPinValue(LCD_DATA_PORT, LCD_D6, (value >> 2) & 0x01);
    GPIO_VidSetPinValue(LCD_DATA_PORT, LCD_D7, (value >> 3) & 0x01);
    LCD_EnablePulse();
}

void LCD_Init(void) {
    GPIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_OUTPUT);
    GPIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_OUTPUT);
    GPIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_OUTPUT);
    GPIO_VidSetPinDirection(LCD_DATA_PORT, LCD_D4, GPIO_OUTPUT);
    GPIO_VidSetPinDirection(LCD_DATA_PORT, LCD_D5, GPIO_OUTPUT);
    GPIO_VidSetPinDirection(LCD_DATA_PORT, LCD_D6, GPIO_OUTPUT);
    GPIO_VidSetPinDirection(LCD_DATA_PORT, LCD_D7, GPIO_OUTPUT);

    _delay_ms(50);

    /* HD44780 initialization sequence for 4-bit mode */
    LCD_send4bit(0x03); 
    _delay_ms(5);
    LCD_send4bit(0x03);
    _delay_us(150);
    LCD_send4bit(0x03);
    LCD_send4bit(0x02); 

    LCD_SendCommand(LCD_4BIT_MODE);
    LCD_SendCommand(LCD_ON);
    LCD_Clear();
    LCD_SendCommand(LCD_ENTRY_MODE);
}

void LCD_SendCommand(u8 cmd) {
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_LOW);
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_LOW);
    
    LCD_send4bit(cmd >> 4);   /* High Nibble */
    LCD_send4bit(cmd & 0x0F); /* Low Nibble */
}

void LCD_SendChar(u8 data) {
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_HIGH);
    GPIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_LOW);

    LCD_send4bit(data >> 4);  /* High Nibble */
    LCD_send4bit(data & 0x0F); /* Low Nibble */
}

void LCD_SendString(const char* str) {
    while(*str) LCD_SendChar(*str++);
}

void LCD_SendNumber(s32 num) {
    char nArr[11];      
    u8 i = 0;
    s8 j;
    u32 u_num;

    if (num == 0) {
        LCD_SendChar('0');
        return;
    }

    if (num < 0) {
        LCD_SendChar('-');
        u_num = (u32)(-num);
    } else {
        u_num = (u32)num;
    }

    while (u_num > 0) {
        nArr[i++] = (u_num % 10) + '0';
        u_num /= 10;
    }

    for (j = i - 1; j >= 0; j--) {
        LCD_SendChar(nArr[j]);
    }
}

void LCD_Clear(void) {
    LCD_SendCommand(LCD_CLEAR);
    _delay_ms(2); 
}

void LCD_SetCursor(u8 row, u8 col) {
    u8 address = (row == 0) ? (0x80 + col) : (0xC0 + col);
    LCD_SendCommand(address);
}
