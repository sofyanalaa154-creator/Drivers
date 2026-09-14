#include "ADC_interface.h"
#include "BIT_MATH.h"

/* ========== ADC Registers (ATmega328P) ========== */
#define ADMUX   (*(volatile u8*)0x7C)
#define ADCSRA  (*(volatile u8*)0x7A)
#define ADCSRB  (*(volatile u8*)0x7B)
#define ADCL    (*(volatile u8*)0x78)
#define ADCH    (*(volatile u8*)0x79)
#define ADC_REG (*(volatile u16*)0x78)
#define DIDR0   (*(volatile u8*)0x7E)
#define SREG    (*(volatile u8*)0x5F)

/* ========== Bits ========== */
#define REFS0   6
#define REFS1   7
#define ADLAR   5

#define ADEN    7
#define ADSC    6
#define ADIE    3

/* ========== Callback Pointer ========== */
static void (*ADC_CallBack)(void) = 0;

/* ========== ADC Initialization ========== */
void ADC_VidInit(u8 Copy_u8Ref, u8 Copy_u8Prescaler, u8 Copy_u8Resolution)
{
    /* Reference Voltage */
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
    }

    /* Resolution */
    if (Copy_u8Resolution == ADC_RESOLUTION_8BIT)
        SET_BIT(ADMUX, ADLAR);
    else
        CLR_BIT(ADMUX, ADLAR);

    /* Prescaler */
    ADCSRA &= 0xF8;
    ADCSRA |= (Copy_u8Prescaler & 0x07);

    /* Enable ADC */
    SET_BIT(ADCSRA, ADEN);
}

/* ========== 10-bit Read (Polling) ========== */
u16 ADC_U16ReadChannel(u8 Copy_u8Channel)
{
    /* Select Channel & Keep Top 3 Bits (Ref + ADLAR) */
    ADMUX = (ADMUX & 0xE0) | (Copy_u8Channel & 0x07);

    /* Ensure ADLAR is cleared for 10-bit read */
    CLR_BIT(ADMUX, ADLAR);

    /* Disable Digital Input for lower 6 channels */
    if (Copy_u8Channel <= 5) {
        SET_BIT(DIDR0, Copy_u8Channel);
    }

    /* Dummy Conversion */
    SET_BIT(ADCSRA, ADSC);
    while (GET_BIT(ADCSRA, ADSC));

    /* Real Conversion */
    SET_BIT(ADCSRA, ADSC);
    while (GET_BIT(ADCSRA, ADSC));

    return ADC_REG;
}

/* ========== 8-bit Read (Polling) ========== */
u8 ADC_U8ReadChannel(u8 Copy_u8Channel)
{
    /* Select Channel & Force ADLAR for Left Adjust */
    ADMUX = (ADMUX & 0xE0) | (Copy_u8Channel & 0x07);
    SET_BIT(ADMUX, ADLAR);

    if (Copy_u8Channel <= 5) {
        SET_BIT(DIDR0, Copy_u8Channel);
    }

    /* Dummy Conversion */
    SET_BIT(ADCSRA, ADSC);
    while (GET_BIT(ADCSRA, ADSC));

    /* Real Conversion */
    SET_BIT(ADCSRA, ADSC);
    while (GET_BIT(ADCSRA, ADSC));

    return ADCH;
}

/* ========== Interrupt Control ========== */
void ADC_VidEnableInterrupt(void)
{
    SET_BIT(ADCSRA, ADIE);
    SET_BIT(SREG, 7);   /* Global Interrupt */
}

void ADC_VidDisableInterrupt(void)
{
    CLR_BIT(ADCSRA, ADIE);
}

/* ========== Callback Setter ========== */
void ADC_VidSetCallBack(void (*ptr)(void))
{
    ADC_CallBack = ptr;
}

/* ========== ADC ISR (ATmega328P Vector 21) ========== */
void __vector_21(void) __attribute__((signal));
void __vector_21(void)
{
    if (ADC_CallBack != 0)
        ADC_CallBack();
}
