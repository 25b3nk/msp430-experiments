//Demo app to test switch S2 (P1.3) on the TI Launchpad
//which is attached to P1.3
// LED status toggles on switch press

#include <msp430g2553.h>
 
int main(void) {
  volatile int i;
 
  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;

  // set up bit 3 of P1 as input, bit 0 of P1 as output
  P1DIR |= BIT0;    // Set to 1 for output
  P1DIR &= ~BIT3;   // Set to 0 for input
  // enabling Pull up/down resistor
  P1REN |= BIT3;
  // setup pull up resistor
  P1OUT |= BIT3;

  
  // loop forever
  while (1)
  {
    if (P1IN & BIT3)   // SW not pressed
    {
      P1OUT = P1OUT;
    }
    else
    {
      P1OUT ^= BIT0;
      for (i = 0; i < 0x6000; i++);
    }
  }
}
