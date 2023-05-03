#include <msp430.h>
#include <stdbool.h>
#include "embedded_utils.h"

void main(void) 
{
  killWatchdogTimer();
  unlockGPIO();
  setAsOutput(6,6);
  clearPinValue(6,6);

  // TB0CTL = TBSSEL_1 | ID_3 | MC_3;
  // TB0CCTL0 = CCIE;
  // __bis_SR_register(GIE);
  //
  // TB0CCR0 = 500;
  //
  int p = 0;
  int dutyCycle = 0;
  int MAX_P = 16;
  int outs[512];
  for (int i = 0; i < 256; ++i)
    outs[i] = i;
  for (int i = 255; i >= 0; --i)
    outs[256 + 255 - i] = i;

  while(true)
  {
    p = 0;
    for (int i = 0; i < 512; i++)
    {
      if (p >= MAX_P)
      {
        p = 0;
        dutyCycle = (float)outs[i] / 256 * MAX_P;
      }
      else
        p++;
          
      if (p < dutyCycle)
        setPinValue(6,6);
      else
        clearPinValue(6,6);

      // __delay_cycles(10);
    }
  }
}
