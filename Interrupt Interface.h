#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#include "STD_TYPES"

#define EXTI_INT0        0
#define EXTI_INT1        1

#define LOW_LEVEL        0
#define ANY_CHANGE       1
#define FALLING_EDGE     2
#define RISING_EDGE      3

#define ISC00            0
#define ISC01            1
#define ISC10            2
#define ISC11            3

#define INT0             0
#define INT1             1

void EXTI_Init(u8 Copy_u8INT, u8 Copy_u8Sense);
void EXTI_Enable(u8 Copy_u8INT);
void EXTI_Disable(u8 Copy_u8INT);
void EXTI_SetCallBack(u8 Copy_u8INT, void (*ptr)(void));

#endif
