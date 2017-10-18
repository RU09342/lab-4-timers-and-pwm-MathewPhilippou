#include <msp430.h>

/*** Global Variable ***/
int Push_Button;
void main(void){

    /*** Watchdog timer and clock Set-Up ***/
    WDTCTL = WDTPW + WDTHOLD;       // Stop watchdog timer
  //  DCOCTL = 0;                     // Select lowest DCOx and MODx
   // BCSCTL1 = CALBC1_1MHZ;          // Set range
   // DCOCTL = CALDCO_1MHZ;           // Set DCO step + modulation

    /*** GPIO Set-Up ***/
    P1DIR |= BIT6;                  // P1.6 set as output (Green LED)
  //  P1SEL |= BIT6;                  // P1.6 selected Timer0_A Out1 output

    P1DIR |= BIT0;

    P1REN |= BIT3;                              //setup button 1.3 using pull up resistor and enable
    P1OUT |= BIT3;
    P1IE |= BIT3;
    P1IES |= BIT3;
    P1IFG &= ~BIT3;

    /*** Timer0_A Set-Up ***/
    TB0CCR0 |= 1000;                    // PWM period
    TB0CCR1 |= 500;                   // TB0CCR1 PWM duty cycle
    TB0CCTL1 |= OUTMOD_7;           // TB0CCR1 output mode = reset/set
    TB0CTL |= TBSSEL_2 + MC_1;      // SMCLK, Up Mode (Counts to TB0CCR0)

    /*** Timer1_A Set-Up ***/
    TB1CCR0 |= 4000;                    // Counter value
    TB1CCTL0 |= CCIE;               // Enable Timer1_A interrupts
    TB1CTL |= TBSSEL_2 + MC_1;      // SMCLK, Up Mode (Counts to TB1CCR0)

    _BIS_SR(LPM0_bits + GIE);       // Enter Low power mode 0 with interrupts enabled


}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    if (Push_Button == 0)              //Falling-edge of button
{
    TB0CCR1 = TB0CCR1+100;               //Initialize value of TB1CCR0
    TB1CCTL0 = CAP;                 //Capture mode
    Push_Button = 1;
    P1OUT ^=  BIT0;
    if (TB0CCR1 == 1100)
                TB0CCR1 = 0;

}
else if (Push_Button == 1)         //Rising-edge of a button
{

    TB0CCR1 = TB0CCR1;
    P1OUT &=~  BIT0;
    Push_Button = 0;
}
    P1IES ^= BIT3;                      //toggle to set as rising edge
    P1IE |= BIT3;                       // Enable interrupt
    P1IFG &= ~(BIT3);

}
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_1B1(void) {
   TB1CTL &= ~(MC1 | MC0);     // Stop TimerB1
   P1IE |= BIT3;
 TB1CCTL0 &= ~CCIFG;
}
