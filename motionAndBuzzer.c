#include <msp430.h>
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                                // Stop WDT

    // Configure GPIO
    P6DIR |= BIT0;                                           // Set P6.0/LED to output direction
    P6OUT &= ~BIT0;                                          // P6.0 LED off

    // Configure P1.1 as input (for motion sensor)
    P1DIR &= ~BIT1;
    P1REN |= BIT1; // Enable pull-up/pull-down resistor
    P1OUT |= BIT1; // Select pull-up resistor

    PM5CTL0 &= ~LOCKLPM5;


    while(1)
    {
            // Check the status of P1.1 (motion sensor input)
                if (P1IN & BIT1)
            {
                // Motion detected, turn on LED
                P6OUT |= BIT0;
                P1DIR |= BIT6 | BIT7;                      // P1.6 and P1.7 output
                P1SEL1 |= BIT6 | BIT7;                     // P1.6 and P1.7 options select

                    // Disable the GPIO power-on default high-impedance mode to activate
                    // previously configured port settings
                    PM5CTL0 &= ~LOCKLPM5;

                    TB0CCR0 = 128;                             // PWM Period/2
                    TB0CCTL1 = OUTMOD_6;                       // TBCCR1 toggle/set
                    TB0CCR1 = 32;                              // TBCCR1 PWM duty cycle
                    TB0CCTL2 = OUTMOD_6;                       // TBCCR2 toggle/set
                    TB0CCR2 = 96;                              // TBCCR2 PWM duty cycle
                    TB0CTL = TBSSEL_1 | MC_3;                  // ACLK, up-down mode

                __delay_cycles(5000);
            }
            else
            {
                // No motion, turn off LED
                P6OUT &= ~BIT0;
                P1DIR &= ~BIT6;                      // P1.6 and P1.7 output
                P1SEL1 &= ~BIT6;                     // P1.6 and P1.7 options select
                P1DIR &= ~BIT7;                      // P1.6 and P1.7 output
                P1SEL1 &= ~BIT7;                     // P1.6 and P1.7 options select
            }
        }
    }
