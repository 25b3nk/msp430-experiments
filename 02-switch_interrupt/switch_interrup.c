//Demo app to test switch S2 (P1.3) on the TI Launchpad
//which is attached to P1.3
//LED status toggles on switch press

#include <msp430g2553.h>

void main(void) {
  WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer
  P1DIR |= BIT0;  // Set P1.0 as output (RED LED)
  P1DIR &= ~BIT3;  // Set P1.3 as input (SWITCH)
  P1REN |= BIT3;  // Enable resistor for P1.3
  P1OUT |= BIT3;  // Select pull up for P1.3

  P1IE |= BIT3;  // Enable P1.3 (Switch) interrupt
  P1IES |= BIT3;  //  P1.3 Hi/lo edge
  P1IFG &= ~BIT3;  // P1.3 IFG cleared

  _BIS_SR(LPM4_bits + GIE);  // Enter LPM4 w/interrupt
}

// Port 1 interrupt service routine
#pragma  vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1OUT ^= BIT0;   // Toggle P1.0
  P1IFG &= ~BIT3;  // P1.3 IFG cleared
}

/**
 * Few observations and understandings:
 * Understandings:
 * * Interrupts are handled based on priority.
 * * We can use interrupts to communincate with peripherals like switch.
 * * We need to set/change Interrupt enable register, interrupt edge select reg and interrupt flag reg.
 * * Interrupt for Ports can catch only hi-lo or lo-hi transitions and are triggered on edges
 * 
 * Observatins:
 * * When switch is set as interrupt to toggle red LED, the LED sometimes toggles multiple times on one switch press
 * * This maybe due to switch bounce causing multiple edges I suppose
*/
