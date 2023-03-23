#include <msp430.h>
#include "embedded_utils.h"

#define SquareWaveTimerControl TB0CTL
#define TriangleWaveTimerControl TB1CTL
#define SawtoothWaveTimerControl TB2CTL
#define SineWaveTimerControl TB3CTL

void initSquareWave(int frequency);
void initTriangleWave(int frequency);
void initSawtoothWave(int frequency);
void initSineWave(int frequency);


int main(void)
{

}