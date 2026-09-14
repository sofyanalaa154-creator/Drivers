#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include "STD_TYPES"
#include "BIT_MATH"

#define DDRB_REG     *((volatile u8*)0x24)
#define PORTB_REG    *((volatile u8*)0x25)
#define PINB_REG     *((volatile u8*)0x23)
#define DDRC_REG     *((volatile u8*)0x27)
#define PORTC_REG    *((volatile u8*)0x28)
#define PINC_REG     *((volatile u8*)0x26)
#define DDRD_REG     *((volatile u8*)0x2A)
#define PORTD_REG    *((volatile u8*)0x2B)
#define PIND_REG     *((volatile u8*)0x29)

#define GPIO_HIGH 1
#define GPIO_LOW 0

#define GPIO_OUTPUT 1
#define GPIO_INPUT 0

#define GPIO_PIN0 0
#define GPIO_PIN1 1
#define GPIO_PIN2 2
#define GPIO_PIN3 3
#define GPIO_PIN4 4
#define GPIO_PIN5 5
#define GPIO_PIN6 6
#define GPIO_PIN7 7

#define GPIO_PORTB          1
#define GPIO_PORTC          2
#define GPIO_PORTD          3



void GPIO_VidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
void GPIO_VidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);
void GPIO_VidSetPortDirection(u8 Copy_u8Port,u8 Copy_u8Direction);
void GPIO_VidSetPortValue(u8 Copy_u8Port,u8 Copy_u8Value);
u8 U8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin);
u8 U8GetPortValue(u8 Copy_u8Port);
void GPIO_VidTogglePinValue(u8 Copy_u8Port,u8 Copy_u8Pin);


#endif /* GPIO_INTERFACE_H */
