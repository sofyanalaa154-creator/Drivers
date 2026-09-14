#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "SEVEN_SEGMENT_interface.h"

/* Standard 7-Segment Digit Map (Pins 0..6 connected to segments A..G) */
static const u8 SSD_Digits[10] = {
    0b00111111, /* 0 */
    0b00000110, /* 1 */
    0b01011011, /* 2 */
    0b01001111, /* 3 */
    0b01100110, /* 4 */
    0b01101101, /* 5 */
    0b01111101, /* 6 */
    0b00000111, /* 7 */
    0b01111111, /* 8 */
    0b01101111  /* 9 */
};

void SSD_VidInit(u8 copy_u8Port) {
    /* Set all 8 pins of the port as OUTPUT */
    GPIO_VidSetPortDirection(copy_u8Port, 0xFF);
    SSD_VidTurnOff(copy_u8Port);
}

void SSD_VidDisplayNumber(u8 copy_u8Port, u8 copy_u8Number) {
    if (copy_u8Number > 9) return;

    u8 pattern = SSD_Digits[copy_u8Number];

#if SEG_COMMON_CATHODE == 0
    /* Invert pattern for Common Anode */
    pattern = ~pattern;
#endif

    GPIO_VidSetPortValue(copy_u8Port, pattern);
}

void SSD_VidTurnOff(u8 copy_u8Port) {
#if SEG_COMMON_CATHODE == 1
    GPIO_VidSetPortValue(copy_u8Port, 0x00);
#else
    GPIO_VidSetPortValue(copy_u8Port, 0xFF);
#endif
}
