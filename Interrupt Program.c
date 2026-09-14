#include <avr/io.h>        
#include <avr/interrupt.h> 
#include "BIT_MATH.h"
#include "INTERRUPT_MAHH.h"


//  Callback pointers
static void (*EXTI0_CallBack)(void) = 0;
static void (*EXTI1_CallBack)(void) = 0;

// ================= INIT =================
void EXTI_Init(u8 Copy_u8INT, u8 Copy_u8Sense)
{
    switch(Copy_u8INT)
    {
        case EXTI_INT0:
        switch(Copy_u8Sense)
        {
            case LOW_LEVEL:
            CLR_BIT(EICRA, ISC00);
            CLR_BIT(EICRA, ISC01);
            break;

            case ANY_CHANGE:
            SET_BIT(EICRA, ISC00);
            CLR_BIT(EICRA, ISC01);
            break;

            case FALLING_EDGE:
            CLR_BIT(EICRA, ISC00);
            SET_BIT(EICRA, ISC01);
            break;

            case RISING_EDGE:
            SET_BIT(EICRA, ISC00);
            SET_BIT(EICRA, ISC01);
            break;
        }
        break;

        case EXTI_INT1:
        switch(Copy_u8Sense)
        {
            case LOW_LEVEL:
            CLR_BIT(EICRA, ISC10);
            CLR_BIT(EICRA, ISC11);
            break;

            case ANY_CHANGE:
            SET_BIT(EICRA, ISC10);
            CLR_BIT(EICRA, ISC11);
            break;

            case FALLING_EDGE:
            CLR_BIT(EICRA, ISC10);
            SET_BIT(EICRA, ISC11);
            break;

            case RISING_EDGE:
            SET_BIT(EICRA, ISC10);
            SET_BIT(EICRA, ISC11);
            break;
        }
        break;
    }

}

// ================= ENABLE =================
void EXTI_Enable(u8 Copy_u8INT)
{
    switch(Copy_u8INT)
    {
        case EXTI_INT0: SET_BIT(EIMSK, INT0); break;
        case EXTI_INT1: SET_BIT(EIMSK, INT1); break;
        default: break;
    }
}

// ================= DISABLE =================
void EXTI_Disable(u8 Copy_u8INT)
{
    switch(Copy_u8INT)
    {
        case EXTI_INT0: CLR_BIT(EIMSK, INT0); break;
        case EXTI_INT1: CLR_BIT(EIMSK, INT1); break;
        default: break;
    }
}

// ================= CALLBACK =================
void EXTI_SetCallBack(u8 Copy_u8INT, void (*ptr)(void))
{
    switch(Copy_u8INT)
    {
        case EXTI_INT0: EXTI0_CallBack = ptr; break;
        case EXTI_INT1: EXTI1_CallBack = ptr; break;
        default: break;
    }
}

// ================= ISR =================
ISR(INT0_vect)
{
    if(EXTI0_CallBack != 0)
        EXTI0_CallBack();
}

ISR(INT1_vect)
{
    if(EXTI1_CallBack != 0)
        EXTI1_CallBack();
}
