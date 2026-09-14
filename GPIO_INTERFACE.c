#include "GPIO_INTERFACE_C.h"



void GPIO_VidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
    switch(Copy_u8Port)
    {
        case GPIO_PORTB:
            if(Copy_u8Direction == GPIO_OUTPUT)
            {
                SET_BIT(DDRB_REG,Copy_u8Pin);
            }
            else if(Copy_u8Direction == GPIO_INPUT)
            {
                CLR_BIT(DDRB_REG,Copy_u8Pin);
            }
            else
            {
            }
            break;
            
        case GPIO_PORTC:
            if(Copy_u8Direction == GPIO_OUTPUT)
            {
                SET_BIT(DDRC_REG,Copy_u8Pin);
            }
            else if(Copy_u8Direction == GPIO_INPUT)
            {
                CLR_BIT(DDRC_REG,Copy_u8Pin);
            }
            break;
            
        case GPIO_PORTD:
            if(Copy_u8Direction == GPIO_OUTPUT)
            {
                SET_BIT(DDRD_REG,Copy_u8Pin);
            }
            else if(Copy_u8Direction == GPIO_INPUT)
            {
                CLR_BIT(DDRD_REG,Copy_u8Pin);
            }
            break;
    }
}

void GPIO_VidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
    switch (Copy_u8Port)
    {
      case GPIO_PORTB:
         if(Copy_u8Value==GPIO_HIGH)
          {
            SET_BIT(PORTB_REG,Copy_u8Pin); 
          }
          else if(Copy_u8Value==GPIO_LOW)
          {
            CLR_BIT(PORTB_REG,Copy_u8Pin); 
          }  
         break;
        case GPIO_PORTC:
         if(Copy_u8Value==GPIO_HIGH)
          {
            SET_BIT(PORTC_REG,Copy_u8Pin); 
          }
          else if(Copy_u8Value==GPIO_LOW)
          {
            CLR_BIT(PORTC_REG,Copy_u8Pin); 
          }  
         break;
        case GPIO_PORTD:
         if(Copy_u8Value==GPIO_HIGH)
         {
            SET_BIT(PORTD_REG,Copy_u8Pin);
         }
         else
         {
            CLR_BIT(PORTD_REG,Copy_u8Pin);
         }
         break;
    
    default:
        break;
    }
}

void GPIO_VidSetPortDirection(u8 Copy_u8Port,u8 Copy_u8Direction)
{
    switch (Copy_u8Port)
    {
        case GPIO_PORTB:
         DDRB_REG = Copy_u8Direction;
          break;
        case GPIO_PORTC:
         DDRC_REG = Copy_u8Direction;
          break;
        case GPIO_PORTD:
         DDRD_REG = Copy_u8Direction;
          break;
    }
}

void GPIO_VidSetPortValue(u8 Copy_u8Port,u8 Copy_u8Value)
{
    switch (Copy_u8Port)
    {
        case GPIO_PORTB:
         PORTB_REG = Copy_u8Value;
          break;
        case GPIO_PORTC:
         PORTC_REG = Copy_u8Value;
          break;
        case GPIO_PORTD:
         PORTD_REG = Copy_u8Value;
          break;
    }
}

u8 U8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    u8 Local_U8Result = 0;
    if (Copy_u8Pin <= 7) {
        switch (Copy_u8Port) {
            case GPIO_PORTB:
             Local_U8Result = GET_BIT(PINB_REG, Copy_u8Pin);
              break;
            case GPIO_PORTC:
             Local_U8Result = GET_BIT(PINC_REG, Copy_u8Pin);
              break;
            case GPIO_PORTD:
             Local_U8Result = GET_BIT(PIND_REG, Copy_u8Pin);
              break;
        }
    }
    return Local_U8Result;
}

u8 U8GetPortValue(u8 Copy_u8Port)
{
    u8 Local_U8Result = 0;
    switch (Copy_u8Port) {
        case GPIO_PORTB:
         Local_U8Result = PINB_REG;
          break;
        case GPIO_PORTC:
         Local_U8Result = PINC_REG;
          break;
        case GPIO_PORTD:
         Local_U8Result = PIND_REG;
          break;
    }
    return Local_U8Result;
}

void GPIO_VidTogglePinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
    switch (Copy_u8Port)
    {
        case GPIO_PORTB:
            TOGGLE_BIT(PORTB_REG, Copy_u8Pin);
            break;
        case GPIO_PORTC:
            TOGGLE_BIT(PORTC_REG, Copy_u8Pin);
            break;
        case GPIO_PORTD:
            TOGGLE_BIT(PORTD_REG, Copy_u8Pin);
            break;
        default:
            break;
    }
}
