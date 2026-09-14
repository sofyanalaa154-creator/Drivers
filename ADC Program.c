#include <avr/io.h>
#include <avr/interrupt.h>
#include "BIT_MATH.h"
#include "ADC_interface.h"

#define REFS0   6
#define REFS1   7
#define ADLAR   5

#define ADEN    7
#define ADSC    6
#define ADIE    3

static void (*ADC_CallBack)(void) = NULL;

void ADC_VidInit(u8 Copy_u8Ref, u8 Copy_u8Prescaler, u8 Copy_u8Resolution)
{
    ADMUX &= ~(0xC0);

    switch (Copy_u8Ref)
    {
        case ADC_REF_AREF:
            break;

        case ADC_REF_AVCC:
            SET_BIT(ADMUX, REFS0);
            break;

        case ADC_REF_INTERNAL_1V1:
            SET_BIT(ADMUX, REFS0);
            SET_BIT(ADMUX, REFS1);
            break;

        default:
            break;
    }

    if (Copy_u8Resolution == ADC_RESOLUTION_8BIT)
    {
        SET_BIT(ADMUX, ADLAR);
    }
    else
    {
        CLR_BIT(ADMUX, ADLAR);
    }

    ADCSRA &= 0xF8;
    ADCSRA |= (Copy_u8Prescaler & 0x07);

    SET_BIT(ADCSRA, ADEN);
}

u16 ADC_U16ReadChannel(u8 Copy_u8Channel)
{
    ADMUX = (ADMUX & 0xF0) | (Copy_u8Channel & 0x07);

    CLR_BIT(ADMUX, ADLAR);

    if (Copy_u8Channel <= 5)
    {
        SET_BIT(DIDR0, Copy_u8Channel);
    }

    SET_BIT(ADCSRA, ADSC);

    while (GET_BIT(ADCSRA, ADSC));

    return ADC;
}

u8 ADC_U8ReadChannel(u8 Copy_u8Channel)
{
    ADMUX = (ADMUX & 0xF0) | (Copy_u8Channel & 0x07);

    SET_BIT(ADMUX, ADLAR);

    if (Copy_u8Channel <= 5)
    {
        SET_BIT(DIDR0, Copy_u8Channel);
    }

    SET_BIT(ADCSRA, ADSC);

    while (GET_BIT(ADCSRA, ADSC));

    return ADCH;
}

void ADC_VidEnableInterrupt(void)
{
    SET_BIT(ADCSRA, ADIE);
}

void ADC_VidDisableInterrupt(void)
{
    CLR_BIT(ADCSRA, ADIE);
}

void ADC_VidSetCallBack(void (*ptr)(void))
{
    ADC_CallBack = ptr;
}

ISR(ADC_vect)
{
    if (ADC_CallBack != NULL)
    {
        ADC_CallBack();
    }
}
