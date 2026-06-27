//eint0.c
#include <lpc21xx.h>              // Header file for LPC21xx microcontroller definitions
#include "pin_connect_block.h"     // Header file for pin configuration functions
#include "pin_function_defines.h"  // Header file for pin function definitions
#include "delay.h"                 // User-defined delay function header

#define EINT0_CHNO 14              // Channel number of External Interrupt 0 (EINT0) in VIC
#define EINT0_LED 16               // LED connected to P1.16

// *************** EINT0 Interrupt Service Routine ***************
void eint0_isr(void) __irq          // ISR for External Interrupt 0
{
    IOPIN1 ^= 1 << EINT0_LED;       // Toggle the LED connected to P1.16
    delay_ms(100);                  // Small delay for visible LED toggle
    EXTINT = 1 << 0;                // Clear interrupt flag for EINT0
    VICVectAddr = 0;                // Signal end of ISR to the VIC
}

// *************** Function to Configure and Enable EINT0 ***************
void eint0_enable(void)
{
    IODIR1 |= 1 << EINT0_LED;       // Configure P1.16 as output (for LED)
    
    cfgportpin(0, 16, FUN2);        // Configure P0.16 pin function as EINT0 (PINSEL1 bits = 10)

    // VICIntSelect = 0;            // (Optional) Configure interrupt as IRQ (not FIQ)
    VICIntEnable = 1 << EINT0_CHNO; // Enable EINT0 interrupt in the VIC
    VICVectCntl0 = (1 << 5) | EINT0_CHNO; // Enable slot 0 and assign EINT0 channel number
    VICVectAddr0 = (unsigned int)eint0_isr; // Load address of ISR into VIC slot 0

    // EXTMODE = 1 << 0;            // (Optional) Configure EINT0 as edge-triggered interrupt
    // EXTPOLAR = 1 << 0;           // (Optional) Configure interrupt to trigger on rising edge
}

int cnt;                            // Counter variable

