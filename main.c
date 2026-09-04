/* *********************************************************************
 *
 * This file shows how to use SoftwareUart Library, a half duplex software driven uart.
 *
 * Note that the RX_PIN must be the external interrupt 0 pin on
 * your AVR of choice. The TX_PIN can be chosen to be any suitable
 * pin. Note that this code is intended to run from an internal
 * 8 MHz clock source.
 * If other operating voltages and/or temperatures than 5 Volts and 25 Degrees Celsius
 * are desired, consider calibrating the internal oscillator.
 *
 * original author
 *            Atmel Corporation: http://www.atmel.com
 *            Revision: 3778
 *            Date: 2008-04-11
 * updated by Joseph Heller / CATCH22eu @ Github
 *            MIT License
 *            Date: 2026-09-04
 ******************************************************************************/
#include <avr/io.h>            // Device specifics
#include <avr/interrupt.h>    // The __enable_interrupt() intrinsic.
#include "softwareuart.h"

/*    Main loop.
 *
 *    This loop will run forever.
 *
 *    Note: This main method will write back a predefined string depending upon the character received from the user.
 *                Only send one character at the time, or the loop will hang. To enable receiving of multiple chars look at
                     AVR306: Using the AVR UART. This application note describes a buffered solution.
    */

int main( )
{
    initSoftwareUart( );
    sei( );

    for( ; ; )
    {
        if( state == DATA_PENDING )
        {
            state = IDLE;

            switch( SwUartRXData )
            {

                case 'a':
                        print_string( "atmel avr\r\n" );
                break;

                case 'A':
                        print_string( "Atmel AVR\r\n" );
                break;

                default:
                        print_string( "Unknown command\r\n" );
                break;
            }
        }
    }
}
