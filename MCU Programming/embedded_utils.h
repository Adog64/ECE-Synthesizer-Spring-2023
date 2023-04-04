/**
* Adog64's wonderful library of Embedded System Utility Functions for the MSP430FR2355
**/


#pragma once

#include <msp430.h>
#include <stdbool.h>

// #define OUTPUT 0x01
// #define INPUT 0x00

#define LOCATION_OF_P1DIR 0x0204
#define LOCATION_OF_P1OUT 0x0202
#define LOCATION_OF_P1IE  0x021A
#define LOCATION_OF_P1IES 0x0218
#define LOCATION_OF_P1IN  0x0200

#define LOCATION_OF_TB0CTL 0x0380

#define TIMER_SOURCE_SMCLK 0
#define TIMER_SOURCE_ACLK 1
#define TIMER_SOURCE_VLOCLK 2

#define TIMER_MODE_1STOP 0
#define TIMER_MODE_UP 1
#define TIMER_MODE_CONTINUOUS 2
#define TIMER_MODE_UP_DOWN 3

// ======= PORT MEMORY LOCATION TABLE =======
// | PORT   | DIR   | OUT   | IE    | IES   |
// |--------|-------|-------|-------|-------|
// | P1     | 0204h | 0202h | 021Ah | 0218h |
// | P2     | 0205h | 0203h | 021Bh | 0219h |
// | P3     | 0224h | 0222h | 023Ah | 0238h |
// | P4     | 0225h | 0223h | 023Bh | 0239h |
// | P5     | 0244h | 0242h | 025Ah | 0258h |
// | P6     | 0245h | 0243h | 025Bh | 0259h |

/// @brief kill the watchdog timer
void killWatchdogTimer();

/// @brief disable low power lock on GPIO
void unlockGPIO();

// ===== GPIO Config =====

/// @brief Set a pin as output P[port].[pin]
/// @param port port containing pin
/// @param pin bit index within port
void setAsOutput(char port, char pin);

/// @brief Set a pin as input P[port].[pin]
/// @param port port containing pin
/// @param pin bit index within port
void setAsInput(char port, char pin);

/// @brief Set the value of pin P[port].[pin] to logic 1
/// @param port port containing pin
/// @param pin bit index within port
void setPinValue(char port, char pin);

/// @brief Clear the value of pin P[port].[pin] to logic 0
/// @param port port containing pin
/// @param pin bit index within port
void clearPinValue(char port, char pin);

/// @brief Toggle the value of pin P[port].[pin]
/// @param port port containing pin
/// @param pin bit index within port
void togglePinValue(char port, char pin);

/// @brief Read the value from a GPIO pin
/// @param port the port containing pin
/// @param pin bit index within port
void getPinValue(char port, char pin);


// ===== Interrupt Config =====

/// @brief Enable interrupts locally on pin P[port].[pin]
/// @param port port containing pin
/// @param pin bit index within register
void enablePinInterrupt(char port, char pin);

/// @brief Set the interrupt trigger edge to the rising edge
/// @param port port containing pin
/// @param pin bit index within register
void setInterruptEdgeRising(char port, char pin);

/// @brief Set the interrupt trigger edge to the falling edge
/// @param port port containing pin
/// @param pin bit index within register
void setInterruptEdgeFalling(char port, char pin);

// ===== Timer Config =====


/// @brief Set the value of ID
/// @param timer Timer that ID 
/// @param n value of ID = 2^n
void setB3TimerID(char timer, char n);

/// @brief Set the value of IDEX for the timer
/// @param timer timer being modified
/// @param n value of ID = 2^n
// void setB3TimerIDEX(char timer, char n);

/// @brief Clear the timer register
/// @param timer timer being modified
void resetB3Timer(char timer);

/// @brief Set timer mode
/// @param timer timer being modified
void setB3TimerMode(char timer, char mode);

/// @brief Generate a PWM signal on the 1 MHz SMCLK
/// @param timer timer to generate signal on
/// @param duty_cycle_us the time the signal is high in microseconds
void generateTimerPWM(char timer, char duty_cycle_us);

/// @brief Undefined function; called for generating a PWM signal when TB0_PWM is a defined macro
void tb0SignalLow();

/// @brief Undefined function; called for generating a PWM signal when TB0_PWM is a defined macro
void tb0SignalHigh();

/// @brief Undefined function; called for generating a PWM signal when TB1_PWM is a defined macro
void tb1SignalLow();

/// @brief Undefined function; called for generating a PWM signal when TB1_PWM is a defined macro
void tb1SignalHigh();

//================= DEFINITIONS ==================

void setAsOutput(char port, char pin)
{
    char bit = BIT0 << pin;                                                 // select the bit to change by left shifting the logic 1 in BIT0 to its final spot
    port -= 1;                                                              // change from 1-indexed ports to 0-indexed ports
    char* dir = LOCATION_OF_P1DIR + ((port >> 1) << 5) + (port & 1);        // find the memory location of the selected port (3 groups of 2 consecutive memory locations; groups spaced by 20h)
    *dir |= bit;                                                            // set the bit in the memory location to logic 1
}

void setAsInput(char port, char pin)
{
    char bit = BIT0 << pin;                                                 // select the bit to change by left shifting the logic 1 in BIT0 to its final spot
    port -= 1;                                                              // change from 1-indexed ports to 0-indexed ports
    char* dir = LOCATION_OF_P1DIR + ((port >> 1) << 5) + (port & 1);        // find the memory location of the selected port (3 groups of 2 consecutive memory locations; groups spaced by 20h)
    *dir &= ~bit;                                                           // set the bit in the memory location to logic 0
}


void setPinValue(char port , char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* out = LOCATION_OF_P1OUT + ((port >> 1) << 5) + (port & 1);
    *out |= bit;
}

void clearPinValue(char port , char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* out = LOCATION_OF_P1OUT + ((port >> 1) << 5) + (port & 1);
    *out &= ~bit;
}

void getPinValue(char port, char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* out = LOCATION_OF_P1IN + ((port >> 1) << 5) + (port & 1);
    *out |= bit;
}

void togglePinValue(char port, char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* out = LOCATION_OF_P1OUT + ((port >> 1) << 5) + (port & 1);
    *out ^= bit;
}

void enablePinInterrupt(char port, char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* ie = LOCATION_OF_P1IE + ((port >> 1) << 5) + (port & 1);
    *ie |= bit;
}

void setInterruptEdgeRising(char port, char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* ies = LOCATION_OF_P1IES + ((port >> 1) << 5) + (port & 1);
    *ies &= ~bit;
}

void setInterruptEdgeFalling(char port, char pin)
{
    char bit = BIT0 << pin;
    port -= 1;
    char* ies = LOCATION_OF_P1IES + ((port >> 1) << 5) + (port & 1);
    *ies |= bit;
}

void killWatchdogTimer()
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
}

void unlockGPIO()
{
    PM5CTL0 &= ~LOCKLPM5;
}

void setB3TimerID(char timer, char n)
{
    // | n  | bit           | 
    // |----|---------------|
    // | 0  | 0b00xx_xxxx   |
    // | 1  | 0b01xx_xxxx   |
    // | 2  | 0b10xx_xxxx   |
    // | 3  | 0b11xx_xxxx   |

    int bit = n << 6;
    int* timer_ctl = LOCATION_OF_TB0CTL + (timer << 6);
    *timer_ctl |= ((BIT6|BIT7) & bit);
}