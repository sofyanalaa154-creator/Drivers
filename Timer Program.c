#include "TIMER_YOUSH.h"
#include <stddef.h>

/* ATmega328P Manual Register Definitions */
#define TCCR0A  *((volatile u8*)0x44)
#define TCCR0B  *((volatile u8*)0x45)
#define TCNT0   *((volatile u8*)0x46)
#define OCR0A   *((volatile u8*)0x47)
#define TIMSK0  *((volatile u8*)0x6E)
#define TIFR0   *((volatile u8*)0x35)

static void (*Timer0_OVF_Callback)(void) = NULL;
static void (*Timer0_CTC_Callback)(void) = NULL;

void TIMER0_VidInit(u8 mode) {
    if (mode == TIMER_MODE_CTC) {
        SET_BIT(TCCR0A, 1); // WGM01
        CLR_BIT(TCCR0A, 0); // WGM00
    } else {
        CLR_BIT(TCCR0A, 0);
        CLR_BIT(TCCR0A, 1);
    }
}

void TIMER0_VidStart(u8 clock) {
    TCCR0B &= 0xF8; 
    TCCR0B |= (clock & 0x07); 
}

void TIMER0_VidStop(void) {
    TCCR0B &= 0xF8; 
}

void TIMER0_VidSetPreload(u8 value) {
    TCNT0 = value;
}

void TIMER0_VidSetCompareMatch(u8 value) {
    OCR0A = value;
}

void TIMER0_VidEnableOverflowInterrupt(void) {
    SET_BIT(TIMSK0, 0); // TOIE0
}

void TIMER0_VidDisableInterrupt(void) {
    TIMSK0 &= 0xFC;
}

void TIMER0_VidEnableCTCInterrupt(void) {
    SET_BIT(TIMSK0, 1); // OCIE0A
}

void TIMER0_VidSetOverflowCallback(void (*callback)(void)) {
    Timer0_OVF_Callback = callback;
}

void TIMER0_VidSetCTCCallback(void (*callback)(void)) {
    Timer0_CTC_Callback = callback;
}

/* Fixed Microsecond Delay (Safe Polling) */
void TIMER0_VidDelay_us(u32 us) {
    u8 saved_tccr0b = TCCR0B;
    
    // Force Prescaler 8 (1 tick = 0.5us at 16MHz, or 1us at 8MHz)
    TCCR0B = (TCCR0B & 0xF8) | TIMER0_PRESCALER_8;

    while (us--) {
        /* Preload for 1us target based on F_CPU */
        #if (F_CPU == 16000000UL)
            TCNT0 = 254; // 2 ticks @ 0.5us = 1us
        #else
            TCNT0 = 255; // 1 tick @ 1us (for 8MHz / 8)
        #endif

        SET_BIT(TIFR0, 0); // Clear TOV0 flag by writing 1
        while (GET_BIT(TIFR0, 0) == 0);
    }

    TCCR0B = saved_tccr0b; // Restore previous state
}

void TIMER0_VidDelay_ms(u32 ms) {
    while (ms--) {
        TIMER0_VidDelay_us(1000);
    }
}

/* Interrupt Service Routines for ATmega328P */
void __vector_17(void) __attribute__((signal)); // Timer0 Overflow
void __vector_17(void) {
    if (Timer0_OVF_Callback != NULL) Timer0_OVF_Callback();
}

void __vector_15(void) __attribute__((signal)); // Timer0 Compare Match A
void __vector_15(void) {
    if (Timer0_CTC_Callback != NULL) Timer0_CTC_Callback();
}
