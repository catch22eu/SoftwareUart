/* *********************************************************************
 *
 * This file is part of SoftwareUart Library
 *
 * original author
 *      Atmel Corporation: http://www.atmel.com
 *      Revision: 3778
 *      Date: 2008-04-11
 * updated by Joseph Heller / CATCH22eu @ Github
 *      MIT License
 *      Date: 2026-09-04
 ******************************************************************************/
#include <avr/io.h>      // Device specifics
#include <avr/interrupt.h>  // The __enable_interrupt() intrinsic.
#include "softwareuart.h"

/*  External interrupt service routine.
 *
 *  The falling edge in the beginning of the start
 *  bit will trig this interrupt. The state will
 *  be changed to RECEIVE, and the timer interrupt
 *  will be set to trig one and a half bit period
 *  from the falling edge. At that instant the
 *  code should sample the first data bit.
 *
 *  Note: initSoftwareUart( void ) must be called in advance.
 */
ISR(INT0_vect)
{

    state = RECEIVE;                  // Change state
    DISABLE_EXTERNAL0_INTERRUPT( );   // Disable interrupt during the data bits.

    DISABLE_TIMER_INTERRUPT( );       // Disable timer to change its registers.  
    TCCR_P &= ~( 1 << CS01 );         // Reset prescaler counter.

    TCNT0 = INTERRUPT_EXEC_CYCL;      // Clear counter register. Include time to run interrupt routine.

    TCCR_P |= ( 1 << CS01 );          // Start prescaler clock.

    OCR = TICKS2WAITONE_HALF;         // Count one and a half period into the future.

    SwUartRXBitCount = 0;             // Clear received bit counter.
    CLEAR_TIMER_INTERRUPT( );         // Clear interrupt bits
    ENABLE_TIMER_INTERRUPT( );        // Enable timer0 interrupt on again

}


/* Timer0 interrupt service routine.
 *
 *  Timer0 will ensure that bits are written and
 *  read at the correct instants in time.
 *  The state variable will ensure context
 *  switching between transmit and recieve.
 *  If state should be something else, the
 *  variable is set to IDLE. IDLE is regarded
 *  as a safe state/mode.
 *
 *  Note: initSoftwareUart( void ) must be called in advance.
 */
ISR(TIMER_COMP_VECT)
{

    switch (state) {
    // Transmit Byte.
    case TRANSMIT:
      // Output the TX buffer.
      if( SwUartTXBitCount < 8 ) {            
        if( SwUartTXData & 0x01 ) {           // If the LSB of the TX buffer is 1:
          SET_TX_PIN();                       // Send a logic 1 on the TX_PIN.
        }
        else {                                // Otherwise:
          CLEAR_TX_PIN();                     // Send a logic 0 on the TX_PIN.
        }
        SwUartTXData = SwUartTXData >> 1;     // Bitshift the TX buffer and
        SwUartTXBitCount++;                   // increment TX bit counter.
      }

      //Send stop bit.
      else {
        SET_TX_PIN();                         // Output a logic 1.
        state = TRANSMIT_STOP_BIT;
      }
    break;

    // Go to idle after stop bit was sent.
    case TRANSMIT_STOP_BIT:
      DISABLE_TIMER_INTERRUPT( );           // Stop the timer interrupts.
      state = IDLE;                         // Go back to idle.
      ENABLE_EXTERNAL0_INTERRUPT( );        // Enable reception again. 
    break;

    //Receive Byte.
    case RECEIVE:
      OCR = TICKS2WAITONE;                  // Count one period after the falling edge is trigged.
      //Receiving, LSB first.
      if( SwUartRXBitCount < 8 ) {
          SwUartRXBitCount++;
          SwUartRXData = (SwUartRXData>>1);   // Shift due to receiving LSB first.
          if( GET_RX_PIN( ) != 0 ) {
              SwUartRXData |= 0x80;           // If a logical 1 is read, let the data mirror this.
          }
        }

      //Done receiving
      else {
          state = DATA_PENDING;               // Enter DATA_PENDING when one byte is received.
          DISABLE_TIMER_INTERRUPT( );         // Disable this interrupt.
          EXT_IFR |= (1 << INTF0 );           // Reset flag not to enter the ISR one extra time.
          ENABLE_EXTERNAL0_INTERRUPT( );      // Enable interrupt to receive more bytes.
      }
    break;

    // Unknown state.
    default:        
      state = IDLE;                           // Error, should not occur. Going to a safe state.
    }
}


/*  Function to initialize the software UART.
 *
 *  This function will set up pins to transmit and
 *  receive on. Control of Timer0 and External interrupt 0.
 */
void initSoftwareUart( void )
{
    //PORT
    TRXPORT |= ( 1 << RX_PIN );       // RX_PIN is input, tri-stated.
    TRXDDR |= ( 1 << TX_PIN );        // TX_PIN is output.
    SET_TX_PIN( );                    // Set the TX line to idle state (high).

    // Timer0
    DISABLE_TIMER_INTERRUPT( );
    TCCR = 0x00;                      // Init.
    TCCR_P = 0x00;                    // Init.
    TCCR |= (1 << WGM01);			    // Timer in CTC mode (Clear Timer on Compare Match).
    TCCR_P |=  ( 1 << CS01 );         // Divide by 8 prescaler (assumes MCU is on assume 8Mhz).

    //External interrupt
    EXT_ICR = 0x00;                   // Init.
    EXT_ICR |= ( 1 << ISC01 );        // Interrupt sense control: falling edge.
    ENABLE_EXTERNAL0_INTERRUPT( );    // Turn external interrupt on.

    //Internal State Variable
    state = IDLE;
}


/*  Send a unsigned char.
 *
 *  This function sends a unsigned char on the TX_PIN
 *  using the timer0 isr.
 *
 *  Note: initSoftwareUart( void ) must be called in advance.
 */
void putChar( const unsigned char c )
{
    while( state != IDLE )
    {
      ;                               // Don't send while busy receiving or transmitting.
    }

    state = TRANSMIT;
    DISABLE_EXTERNAL0_INTERRUPT( );  // Disable reception.
    SwUartTXData = c;             // Put byte into TX buffer.
    SwUartTXBitCount = 0;         

    TCCR_P &= ~( 1 << CS01 );         // Reset prescaler counter.
    TCNT0 = 0;                        // Clear counter register.
    TCCR_P |= ( 1 << CS01 );          // CTC mode. Start prescaler clock.

    CLEAR_TX_PIN( );                   // Put TX line low: start bit

    ENABLE_TIMER_INTERRUPT( );        // Enable interrupt
}


/*  Print unsigned char string.
 *
 */
void print_string( const unsigned char *data )
{
    while( *data != '\0' )
    {
      putChar( *data++ );
    }
}
