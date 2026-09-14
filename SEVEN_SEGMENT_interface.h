#ifndef SEVEN_SEGMENT_INTERFACE_H
#define SEVEN_SEGMENT_INTERFACE_H

#include "STD_TYPES_C.h"
#include "GPIO_INTERFACE.h"

/* Select Display Type: 1 for Common Cathode, 0 for Common Anode */
#define SEG_COMMON_CATHODE    1

/* Configuration */
#define SEG_DATA_PORT         GPIO_PORTB

/* Function Prototypes */
void SSD_VidInit(u8 copy_u8Port);
void SSD_VidDisplayNumber(u8 copy_u8Port, u8 copy_u8Number);
void SSD_VidTurnOff(u8 copy_u8Port);

#endif /* SEVEN_SEGMENT_INTERFACE_H */
