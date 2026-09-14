#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include "STD_TYPES_C.h"
#include "BIT_MATH.h"

#ifndef F_CPU
#define F_CPU 16000000UL  /* Default to 16MHz (standard Arduino Uno clock) */
#endif

/* Timer Modes */
#define TIMER_MODE_NORMAL         0
#define TIMER_MODE_CTC            1

/* Clock Select / Prescalers */
#define TIMER0_NO_CLOCK           0
#define TIMER0_NO_PRESCALER       1
#define TIMER0_PRESCALER_8        2
#define TIMER0_PRESCALER_64       3
#define TIMER0_PRESCALER_256      4
#define TIMER0_PRESCALER_1024     5
#define TIMER0_EXTERNAL_FALLING   6
#define TIMER0_EXTERNAL_RISING    7

/* Function Prototypes */
void TIMER0_VidInit(u8 mode);
void TIMER0_VidStart(u8 clock);
void TIMER0_VidStop(void);

void TIMER0_VidSetPreload(u8 value);
void TIMER0_VidSetCompareMatch(u8 value);

void TIMER0_VidEnableOverflowInterrupt(void);
void TIMER0_VidDisableInterrupt(void);
void TIMER0_VidEnableCTCInterrupt(void);

void TIMER0_VidSetOverflowCallback(void (*callback)(void));
void TIMER0_VidSetCTCCallback(void (*callback)(void));

void TIMER0_VidDelay_ms(u32 ms);
void TIMER0_VidDelay_us(u32 us);

#endif /* TIMER_YOUSH_H */
