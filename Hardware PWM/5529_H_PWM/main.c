#include <msp430.h> 

int main(void) {
 WDTCTL = WDTPW + WDTHOLD;

 P4DIR |= BIT7;    //configure LEDs as outputs
 P4OUT &= ~BIT7;
 P1DIR |= BIT0;
 P1OUT &= ~BIT0;

 P2DIR  &= ~BIT1;  //configure button as input
 P2OUT |= BIT1;
 P2REN |= BIT1;

 TA0CCR0 |= 1000-1;                    // PWM period
 TA0CCR1 |= 500;                   // TA0CCR1 PWM duty cycle
 TA0CCTL1 |= OUTMOD_7;           // TA0CCR1 output mode = reset/set
 TA0CTL |= TASSEL_2 + MC_1 + TACLR;   // SMCLK, Up Mode (Counts to TA0CCR0)

 while (1)
 {
     if((P1IN&BIT1) != BIT1)
     {
         P4OUT |= BIT7;
         if(TA0CCR1 == 100)
         {
             TA0CCR0 = 0;
             TA0CCR1 = 0;
             TA0CCR0 = 100;
         }
         else
         {

             TA0CCR1 = TA0CCR1 + 100;

         }
     }
     else P4OUT &= ~BIT7;

 }
}
