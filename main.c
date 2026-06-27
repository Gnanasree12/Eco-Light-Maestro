#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "lcd.h"
#include "uart0.h"
#include "adc.h"
#include "rtc.h"
#include "kpm.h"

#include "lcd_defines.h"
#include "rtc_defines.h"
#include "adc_defines.h"

/* ---------------- DEFINES ---------------- */

#define STREET_LED   24        // P1.24
#define LDR_CH       1         // AD0.1

#define SETBIT(reg, bit)   ((reg) |= (1 << (bit)))
#define CLRBIT(reg, bit)   ((reg) &= ~(1 << (bit)))

/* ---------------- GLOBAL VARIABLES ---------------- */

u32 hr, mi, se;
u32 adcVal;
f32 volt;

u32 LDR_TH = 300;          // DEFAULT THRESHOLD
char ledStatus[4] = "OFF";
char key;

/* ---------------- NIGHT CHECK ---------------- */

u8 isNight(u32 hour)
{
    return (hour >= 18 || hour < 6);
}

/* ---------------- MAIN ---------------- */

int main()
{
    /* GPIO */
    SETBIT(IODIR1, STREET_LED);   // LED output

    /* INIT MODULES */
    InitLCD();
    UART0_Init();
    RTC_Init();
    Init_ADC();
    InitKPM();

    /* START MESSAGE */
    cmdLCD(CLEAR_LCD);
    strLCD("EcoLight Maestro");
    UART0_TxString("\r\nEcoLight Maestro Started\r\n");

    delay_ms(1000);

    while (1)
    {
        /* ---------- RTC ---------- */
        RTCGetTime(&hr, &mi, &se);

        /* ---------- ADC ---------- */
        Read_ADC(LDR_CH, &adcVal, &volt);

        /* ---------- KEYPAD (THRESHOLD CONTROL) ---------- */
      /*  key = readn();
			

        switch (key)
        {
            case '1': LDR_TH = 200; break;
            case '2': LDR_TH = 300; break;
            case '3': LDR_TH = 400; break;
            case '4': LDR_TH = 500; break;
            default: break;
        }*/

        /* ---------- STREET LIGHT LOGIC ---------- */
			      //  U32LCD(adcVal);

        if (isNight(hr) && adcVal < LDR_TH)
        {
            SETBIT(IOSET1, STREET_LED);
            ledStatus[0] = 'O';
            ledStatus[1] = 'N';
            ledStatus[2] = '\0';
        }
        else
        {
            SETBIT(IOCLR1, STREET_LED);
            ledStatus[0] = 'O';
            ledStatus[1] = 'F';
            ledStatus[2] = 'F';
            ledStatus[3] = '\0';
        }

        /* ---------- LCD DISPLAY ---------- */
        cmdLCD(CLEAR_LCD);
        strLCD("ADC:");
        U32LCD(adcVal);

        cmdLCD(GOTO_LINE2_POS0);
        strLCD("TH:");
        U32LCD(LDR_TH);
        strLCD(" LED:");
        strLCD(ledStatus);

        /* ---------- UART DISPLAY ---------- */
        UART0_TxString("\r\n[ADC] ");
        U32UART0(adcVal);

        UART0_TxString("  [TH] ");
        U32UART0(LDR_TH);

        UART0_TxString("  [LED] ");
        UART0_TxString(ledStatus);

        UART0_TxString("\r\n-----------------------");

        delay_s(1);
    }
}
