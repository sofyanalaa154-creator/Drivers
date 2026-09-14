#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>
#include "KEYPAD_INTERFACE.h"

void KPD_Init(u8 copy_port) {
    /* Set pins 0..3 as Input (Rows) and 4..7 as Output (Cols) */
    GPIO_VidSetPortDirection(copy_port, GPIO_LOW_NOT_ALL);
    GPIO_VidSetPortValue(copy_port, GPIO_HIGH_ALL);
}

u8 KPD_GetKey(u8 copy_u8port) {
    u8 LOC_PinValue;
    u8 LOC_pressKEY = 0xFF;

    static const u8 LOC_Arr[KPD_ROWNUM][KPD_ColNUM] = Keypad_Arr;
    static const u8 LOC_ArrCol[KPD_ColNUM] = {KPD_col1, KPD_col2, KPD_col3, KPD_col4};
    static const u8 LOC_ArrROW[KPD_ROWNUM] = {KPD_Row1, KPD_Row2, KPD_Row3, KPD_Row4};

    /*
     * BLOCKING WAIT LOOP:
     * Continually polls the keypad matrix until a button press is detected.
     * The function will NOT return execution back to main() until LOC_pressKEY 
     * is updated with a valid ASCII character (i.e., no longer 0xFF).
     */
    do {
        for (u8 col = 0; col < KPD_ColNUM; col++) {
            /* Drive current column LOW */
            GPIO_VidSetPinValue(copy_u8port, LOC_ArrCol[col], GPIO_LOW);

            for (u8 row = 0; row < KPD_ROWNUM; row++) {
                LOC_PinValue = U8GetPinValue(copy_u8port, LOC_ArrROW[row]);

                if (LOC_PinValue == GPIO_LOW) {
                    /* Debounce Delay */
                    _delay_ms(20);
                    LOC_PinValue = U8GetPinValue(copy_u8port, LOC_ArrROW[row]);

                    if (LOC_PinValue == GPIO_LOW) {
                        LOC_pressKEY = LOC_Arr[row][col];

                        /* Wait until key release */
                        while (U8GetPinValue(copy_u8port, LOC_ArrROW[row]) == GPIO_LOW) {
                            _delay_ms(10);
                        }
                    }
                }
            }

            /* Restore column pin HIGH */
            GPIO_VidSetPinValue(copy_u8port, LOC_ArrCol[col], GPIO_HIGH);
        }
    } while (LOC_pressKEY == 0xFF);

    return LOC_pressKEY;
}
