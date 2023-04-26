#include <msp430.h>
#include "embedded_utils.h"
#include "freq_period.h"

#define SquareWaveTimerControl TB0CTL
#define TriangleWaveTimerControl TB1CTL
#define SawtoothWaveTimerControl TB2CTL
#define SineWaveTimerControl TB3CTL

#define ALL_ON_8b 0xFF
#define ALL_ON_16b 0xFFFF
#define ALL_OFF_8b 0x00
#define ALL_OFF_16b 0x0000

void initGPIO();
void initTimers();
void updateTimers();

int freq_31250, freq_62500;

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

    // enable interrupts on input ports
    P1IE = ALL_ON_8b;
    P2IE = ALL_ON_8b;
    P3IE = ALL_ON_8b;

    // button press interrupt edge low-to-high
    P1IES = ALL_OFF_8b;
    P2IES = ALL_OFF_8b;
    P3IES = ALL_OFF_8b;

    __bis_SR_register(GIE); // enable global interrupts

    // configure pull down resistor on all ports
    P1OUT = ALL_OFF_8b;          
    P2OUT = ALL_OFF_8b;          
    P2OUT = ALL_OFF_8b;        
    P1REN = ALL_ON_8b;
    P1REN = ALL_ON_8b;
    P1REN = ALL_ON_8b;

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
    SawtoothWaveTimerControl |= TBSSEL_2 | MC_1 | TBIDEX_4;
}

void updateTimers()
{
    TB0CCR0 = freq_62500;   // Square wave frequencies 
    TB0CCR1 = freq_31250;

    TB1CCR0 = freq_31250;   // Triangle wave frequencies

    TB2CCR0 = freq_62500;   // Sawtooth wave frequencies
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
    if (P1IFG & BIT0)
    {
        freq_62500 = f_C3_62500;
        freq_31250 = f_C3_31250;
    }
    else if (P1IFG & BIT1)
    {
        freq_62500 = f_Cs3_62500;
        freq_31250 = f_Cs3_31250;
    }
    else if (P1IFG & BIT2)
    {
        freq_62500 = f_D3_62500;
        freq_31250 = f_D3_31250;
    }
    else if (P1IFG & BIT3)
    {
        freq_62500 = f_Ds3_62500;
        freq_31250 = f_Ds3_31250;
    }
    else if (P1IFG & BIT4)
    {
        freq_62500 = f_E3_62500;
        freq_31250 = f_E3_31250;
    }
    else if (P1IFG & BIT5)
    {
        freq_62500 = f_F3_62500;
        freq_31250 = f_F3_31250;
    }
    else if (P1IFG & BIT6)
    {
        freq_62500 = f_Fs3_62500;
        freq_31250 = f_Fs3_31250;
    }
    else if (P1IFG & BIT7)
    {
        freq_62500 = f_G3_62500;
        freq_31250 = f_G3_31250;
    }
    updateTimers();
}

void __attribute__ ((interrupt(PORT2_VECTOR))) Port_2 (void)
{
    if (P2IFG & BIT0)
    {
        freq_62500 = f_Gs3_62500;
        freq_31250 = f_Gs3_31250;
    }
    else if (P2IFG & BIT1)
    {
        freq_62500 = f_A3_62500;
        freq_31250 = f_A3_31250;
    }
    else if (P2IFG & BIT2)
    {
        freq_62500 = f_As3_62500;
        freq_31250 = f_As3_31250;
    }
    else if (P2IFG & BIT3)
    {
        freq_62500 = f_B3_62500;
        freq_31250 = f_B3_31250;
    }
    else if (P2IFG & BIT4)
    {
        freq_62500 = f_C4_62500;
        freq_31250 = f_C4_31250;
    }
    else if (P2IFG & BIT5)
    {
        freq_62500 = f_Cs4_62500;
        freq_31250 = f_Cs4_31250;
    }
    else if (P2IFG & BIT6)
    {
        freq_62500 = f_D4_62500;
        freq_31250 = f_D4_31250;
    }
    else if (P2IFG & BIT7)
    {
        freq_62500 = f_Ds4_62500;
        freq_31250 = f_Ds4_31250;
    }
    updateTimers();
}

void __attribute__ ((interrupt(PORT3_VECTOR))) Port_3 (void)
{
    if (P3IFG & BIT0)
    {
        freq_62500 = f_E4_62500;
        freq_31250 = f_E4_31250;
    }
    else if (P2IFG & BIT1)
    {
        freq_62500 = f_F4_62500;
        freq_31250 = f_F4_31250;
    }
    else if (P3IFG & BIT2)
    {
        freq_62500 = f_Fs4_62500;
        freq_31250 = f_Fs4_31250;
    }
    else if (P3IFG & BIT3)
    {
        freq_62500 = f_G4_62500;
        freq_31250 = f_G4_31250;
    }
    else if (P3IFG & BIT4)
    {
        freq_62500 = f_Gs4_62500;
        freq_31250 = f_Gs4_31250;
    }
    else if (P3IFG & BIT5)
    {
        freq_62500 = f_A4_62500;
        freq_31250 = f_A4_31250;
    }
    else if (P3IFG & BIT6)
    {
        freq_62500 = f_As4_62500;
        freq_31250 = f_As4_31250;
    }
    else if (P3IFG & BIT7)
    {
        freq_62500 = f_B4_62500;
        freq_31250 = f_B4_31250;
    }
    updateTimers();
}
