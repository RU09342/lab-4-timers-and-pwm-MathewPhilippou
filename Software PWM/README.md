# Software PWM
## Objective
To control the brightness of an LED in intervals of 10% with the push of a button. The bightness should restart at 
0% once it has reached 100%. An second LED should also turn on when the button is pushed to show possible button 
bouncing.
## How
First, the LED is initialized as an output with pull up and pull down resistors so that it may be toggled with a push of a
button. The button is still initialized as an input, similar as to Lab 2, but we also need to enable the interupt of 
the button by using the code P1IE |=BIT1;. Further we need to set the button as falling edge using the code P1IES |=BIT1
and finally we must clear the interrupt flag of the button utilizing the code P1IFG &=~(BIT1);

Then, Timer A0 was initialized by the code "TA0CTL = TASSELx + MC_x;" (x being 0,1,or2). The value of x determines 
whether the counter is in up mode, continous mode, or up/down mode. Variable x also specifies which clock is being 
used, whether it be ACLK, SMCLK or MCLK. TA0CCTL0 sets the mode to either capture or compare if up or up/down
is used. This was set to OUTMOD_7. TA0CCR0 is the period of the PWM and this was set to 1000. TACCR1 is the PWM
duty cycle which is set to 500 as we want the LED to be 50% lit upon startup.

Next, Timer A1 is initialized with a TA1CCR0 value of 4000. This will be the counter value. An interrupt is enabled for 
Timer A1 and it is set to SMCLK up mode which will code the clock to count up to TA1CCR0.

Further, an interrupt is innitialized and an if else statment is written to determine what to do when the user is interacting
with the button. When the button is pressed we add 100 to TACCR1, effectivley increasing the brightness of the  LED by 
10%. We then set TA1CCTL0 to capture mode, change the value of Push_Button to 1 and toggle the LED responsible for 
showing when the button is pushed. Lastly there is an if statent that checks if the brightness is already at 100% 
(TACCR1 == 1100). If this statent is true the brightness will be reset to 0. Next, an else if statment is written to identify 
what to do when the buton is being released. The value of the duty cycle remains the  same, the LED showing if the button 
is pushed is turned off, and the variable Push_Button is set back to zero. After the  if and else if statments there is 3 lines 
of code that enable the button interrupt. These are necesary to allow the button to control the duty cycle of our PWM.

Finally, a second interrupt is used to run the program. This will stop TimerA1 when neccessary and will enable interrupts
for the button.

### Board Differences
Pins all change of course, but the line of code "PM5CTL0 &= ~LOCKLPM5;"is required in order to disable the GPIO 
power-on default high-impedance mode for the 2311 and 6989. The 2311 has no TimerA so TimerB was used for that 
implementation. 