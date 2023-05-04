#include <msp430.h>
#include <stdbool.h>
#include "embedded_utils.h"
#include "freq_period.h"

#define SAMPLE_COUNT 16
#define MAX_COUNT 31250

int p = 0;
int dutyCycle = 0;

int frequency;

void initSampleTimer();
void initTriGenTimer();

void main(void) 
{
  killWatchdogTimer();
  unlockGPIO();
  setAsOutput(1,0);
  clearPinValue(1,0);

  initSampleTimer();
  initSampleTimer();
  
  __bis_SR_register(GIE);
  while(true) {}
}

void initTriGenTimer()
{
  TB0CTL = TBSSEL__SMCLK | MC__UPDOWN | ID_2;    // Use 1 MHz clock divided by 4 in up/down mode
  TB0EX0 = TBIDEX_3;                             // Divide clock by 4 again for a total 16
  TB0CCR0 = f_C3_31250;                          // Count up to 239 before counting down (generates C3)
  freq = 
}

void initSampleTimer()
{
  TB1CTL = TBSSEL__SMCLK | MC__UP | TBIE;      // Use 1 MHz clock in up mode with interrupts
  TB1CCR0 = 1;                                // Set maximum count to 1
  TB1CCR1 = 1;
}

void __attribute__ ((interrupt(TIMER1_B1_VECTOR))) TIMER1_B1_ISR (void)
{
      switch(p)
      {
        case SAMPLE_COUNT:
          p = 0;
          dutyCycle = TB0R * SAMPLE_COUNT * 2 * freq;
          P1OUT |= BIT0;
          break;
        case dutyCycle:
          P1OUT &= ~BIT0;
        default:
      }
      p++;
}
