# Software Debouncing
## Objective
Bouning is defined as the tendency of any two metal contacts in an electronic device to generate multiple signals as 
the contacts close or open; debouncing is any kind of hardware device or software that ensures that only a single 
signal will be acted upon for a single opening or closing of a contact. This objective for this lab is to debounce 
through software.

## How

First, the LED is initialized as an output with pull up and pull down resistors so that it may be toggled with a push of a
button. The button is still initialized as an input, similar as to Lab 2, but we also need to enable the interupt of 
the button by using the code P1IE |=BIT1;. Further we need to set the button as falling edge using the code P1IES |=BIT1
and finally we must clear the interrupt flag of the button utilizing the code P1IFG &=~(BIT1);

Then, Timer A was initialized by the code "TA0CTL = TASSELx + MC_x;" (x being 0,1,or2). The value of x determines 
whether the counter is in up mode, continous mode, or up/down mode. Variable x also specifies which clock is being 
used, whether it be ACLK, SMCLK or MCLK. TA0CCTL0 sets the mode to either capture or compare if up or up/down
is used. TA0CCR0 is the period of the counter and is set to 60000.

As you may have already noticed, the debouncing code was designed for the same functionality as toggling an LED with a button. 
The major difference is that we are now using timers and interrupts to implement the debounce tactic. 
By using two interrupts and a timer we achieve the goal. The clock doesnt start until we go into the interrupt. 
This is the most efficient way to debounce so far. 

## Board Differences
Pins all change of course, but the line of code "PM5CTL0 &= ~LOCKLPM5;"is required in order to disable the 
GPIO power-on default high-impedance mode for the 2311 and 6989. The 2311 has no TimerA so TimerB was 
used for that implementation.