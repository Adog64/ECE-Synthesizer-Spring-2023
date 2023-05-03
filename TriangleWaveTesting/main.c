#include <msp430.h>
#include <stdbool.h>
#include "embedded_utils.h"

#define SAMPLE_COUNT 16
#define MAX_COUNT 31250

int p = 0;
int dutyCycle = 0;

void initSampleTimer();
void initTriGenTimer();

void main(void) 
{
  killWatchdogTimer();
  unlockGPIO();
  setAsOutput(4,1);
  clearPinValue(4,1);

  initSampleTimer();
  initSampleTimer();

  while(true) {}
}

void initTriGenTimer()
{
  TB0CTL = TBSSEL_2 | MC_3 | ID_2;    // Use 1 MHz clock divided by 4 in up/down mode
  TB0EX0 = TBIDEX_3;                  // Divide clock by 4 again for a total 16
  TB0CCR0 = 239;                      // Count up to 239 before counting down (generates C3)
}

void initSampleTimer()
{
  TB1CTL = TBSSEL_2 | MC_1 | TBIE;    // Use 1 MHz clock in up mode with interrupts
  TB1CCR0 = 1;                        // Set maximum count to 1
}

void __atribute__ (interrupt(TIMER1_VECTOR)) TIMER1_B1_ISR (void)

  p = (p >= SAMPLE_COUNT) ? 0 : p + 1;
  
  if (p == 0)
    dutyCycle = 2 * TB0R * SAMPLE_COUNT / MAX_COUNT;

  if (p > dutyCycle)
    setPinValue(4,1);
  else
    clearPinValue(4,1);
}
