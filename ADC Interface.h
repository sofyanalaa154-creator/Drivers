#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "STD_TYPES.h"

/* ========== Reference Voltage ========== */
#define ADC_REF_AREF            0
#define ADC_REF_AVCC            1
#define ADC_REF_INTERNAL_1V1    2

/* ========== ADC Resolution ========== */
#define ADC_RESOLUTION_10BIT    0
#define ADC_RESOLUTION_8BIT     1

/* ========== ADC Prescaler ========== */
#define ADC_PRESCALER_2         1
#define ADC_PRESCALER_4         2
#define ADC_PRESCALER_8         3
#define ADC_PRESCALER_16        4
#define ADC_PRESCALER_32        5
#define ADC_PRESCALER_64        6
#define ADC_PRESCALER_128       7

/* ========== ADC Channels ========== */
#define ADC_CHANNEL_0           0
#define ADC_CHANNEL_1           1
#define ADC_CHANNEL_2           2
#define ADC_CHANNEL_3           3
#define ADC_CHANNEL_4           4
#define ADC_CHANNEL_5           5
#define ADC_CHANNEL_6           6  /* TQFP32 / Nano */
#define ADC_CHANNEL_7           7  /* TQFP32 / Nano */

/* ========== APIs ========== */
void ADC_VidInit(u8 Copy_u8Ref, u8 Copy_u8Prescaler, u8 Copy_u8Resolution);

/* Polling APIs */
u16 ADC_U16ReadChannel(u8 Copy_u8Channel);
u8  ADC_U8ReadChannel(u8 Copy_u8Channel);

/* Interrupt APIs */
void ADC_VidEnableInterrupt(void);
void ADC_VidDisableInterrupt(void);
void ADC_VidSetCallBack(void (*ptr)(void));

#endif /* ADC_INTERFACE_H */
