# Hardware PWM
## Objective
To control the brightness of an LED in intervals of 10% with the push of a button. The bightness should restart at 
0% once it has reached 100%. An second LED should also turn on when the button is pushed to show possible button 
bouncing.
## How
First, the LED is initialized as an output with pull up and pull down resistors so that it may be toggled with a push of a
button. The button is needs to be initialized as an output but since this is a hardware PWM we do not need to initialize the
interrupt for the button.

Then, Timer A0 was initialized by the code "TA0CTL = TASSELx + MC_x + TACLR;" (x being 0,1,or2). The value of x determines 
whether the counter is in up mode, continous mode, or up/down mode. Variable x also specifies which clock is being 
used, whether it be ACLK, SMCLK or MCLK, in this case we set it to SMCLK. TA0CCTL0, sets the mode to either capture or compare if up or up/down
is used. This was set to OUTMOD_7. TA0CCR0 is the period of the PWM and this was set to 1000. TACCR1 is the PWM
duty cycle which is set to 500 as we want the LED to be 50% lit upon startup.

Now, we need to tell the board what do to depending on if the buton is being pushed. For this an if else statemnt was used. First we have an if statment
that checks to see if the button is being pressed, then we toggle the LED that is responsible for showing if the button is being pressed. Now that we know the
button is being pressed we have to check if the  brightness is already 100%. This requires another  if else statement. If the brightness is at 100% we leave 
TACCR0 unchanged and we set TACCR1 back to 0% as that is the duty cycle. If the brightness is less than 100% we leave TACCR0 unchaged and we add 100 to
TACCR1 (equivalent to 10%). Finallly, if the button is not being pressed, we simply turn off the LED responsible for identifying when the button is being pressed.

### Board Differences
Pins all change of course, but the line of code "PM5CTL0 &= ~LOCKLPM5;"is required in order to disable the GPIO 
power-on default high-impedance mode for the 2311 and 6989. The 2311 has no TimerA so TimerB was used for that 
implementation. 