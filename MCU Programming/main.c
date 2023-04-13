#include <msp430.h>
#include "embedded_utils.h"
#include "freq_period.h"

#define SquareWaveTimerControl TB0CTL
#define TriangleWaveTimerControl TB1CTL
#define SawtoothWaveTimerControl TB2CTL
#define SineWaveTimerControl TB3CTL

void initGPIO();
void initTimers();

void generateSquareWave(int frequency);


int main(void)
{
    initGPIO();
    initTimers();

    while (true)
    {
        
    }
}

void initGPIO()
{
    killWatchdogTimer();
    unlockGPIO();

    // Set input pins: 2 octaves = 24 notes

    // Set all 8 port 1 pins as input
    setAsInput(1, 0);       // 3C
    setAsInput(1, 1);       // 3C# 
    setAsInput(1, 2);       // 3D
    setAsInput(1, 3);       // 3D#
    setAsInput(1, 4);       // 3E
    setAsInput(1, 5);       // 3F
    setAsInput(1, 6);       // 3F
    setAsInput(1, 7);       // 3G

    // Set all 8 port 2 pins as input
    setAsInput(2, 0);       // 3G#
    setAsInput(2, 1);       // 4A
    setAsInput(2, 2);       // 4A#
    setAsInput(2, 3);       // 4B
    setAsInput(2, 4);       // 4C
    setAsInput(2, 5);       // 4C#
    setAsInput(2, 6);       // 4D
    setAsInput(2, 7);       // 4D#

    // Set all 8 port 3 pins as inputs
    setAsInput(3, 0);       // 4E
    setAsInput(3, 1);       // 4F
    setAsInput(3, 2);       // 4F#
    setAsInput(3, 3);       // 4G
    setAsInput(3, 4);       // 4G#
    setAsInput(3, 5);       // 4A
    setAsInput(3, 6);       // 4A#
    setAsInput(3, 7);       // 4B

    // Set 4 output pins (one for each waveform) on port 4
    setAsOutput(4, 0);      // Square wave out
    setAsOutput(4, 1);      // Triangle wave out
    setAsOutput(4, 2);      // Sawtooth wave out
    setAsOutput(4, 3);      // Sine wave out
}

void initTimers()
{
    SquareWaveTimerControl |= TBSSEL_2 | MC_1 | TBIDEX_4;
    TriangleWaveTimerControl |= TBSSEL_2 | MC_3 | TBIDEX_4;
    SawtoothWaveTimerControl |= TBSSEL_2 | MC_3 | TBIDEX_4;
}

void generateSquareWave(int frequency)
{
    TB0CCR0 = 62500/frequency;
    TB0CCR1 = 31250/frequency;
}

void generateTriangleWave(int frequency)
{
    TB1CCR0 = 31250/frequency;
    TB1CCR1 = 15625/frequency;
}

void generateSawtoothWave(int frequency)
{
    TB2CCR0 = 62500/frequency;
    TB2CCR1 = 31250/frequency;
}


// Output square wave on P4.0
void __attribute__ ((interrupt(TIMER0_B1_VECTOR))) TIMER0_B1_ISR (void)
{
    switch(__even_in_range(TB0IV,TB0IV_TBIFG))
    {
        case TB0IV_TBCCR1:
            setPinValue(4,0);
            break;                               // CCR1 Set the pin to a 0
        case TB0IV_TBIFG:
            clearPinValue(4,0);
            break;
    }
}

void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
{
    
}