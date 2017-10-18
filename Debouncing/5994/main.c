#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P5DIR &= ~(BIT6);
    P1DIR  |= BIT0;                     // Set output Direction
    P5REN  |= BIT6;                   // Enables resistor for P1.1
    P5OUT |= BIT6;                    // Makes resistor P1.1 a pull up
    P5IE |= BIT6;
    P5IES |= BIT6;                     // Interrupts when 1.1 is pressed or low to high transition
    P5IFG &= ~BIT6;                   // Clear interrupt flag
    TA0CTL = TASSEL_2 + MC_0;           // Timer_A Control Register - SMCLK high frequency clock, timer stopped
    TA0CCTL0 = 0x0010;                  // Enables Capture/compare register for interrupt of timer A0
    TA0CCR0 = 60000;                    // Set value for Timer A0 to count up to


        __enable_interrupt();

    }

    // Interrupt Service Routine 1 which toggles on the LED on the release of the Button and starts timer a to act as a delay
    #pragma vector = PORT5_VECTOR
    __interrupt void Interrupt_1(void)
    {
        P5IFG &= ~BIT6;                     // Clear interrupt flag
        P1OUT ^= BIT0;                      // Toggle LED
        P5IE &= ~BIT6;                    // reset interrupt
        TA0CTL = TASSEL_2 + MC_1;           // Timer_A Control Register - SMCLK high frequency clock, Up
    }

    // Interrupt Service Routine 2 which stops Timer A0 and resets the interrupt
    #pragma vector=TIMER0_A0_VECTOR
    __interrupt void Interrupt_2(void)
    {
        P5IFG &= ~BIT6;                     // Clear interrupt flag
        TA0CTL = MC_0;                      // Stop timer
        P5IE |= BIT6;                     // Interrupt enable set to BUTTON

    }
