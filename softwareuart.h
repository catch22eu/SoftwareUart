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
#ifndef SOFTWAREUART_H
#define SOFTWAREUART_H

#define BR_9600     //!< Desired baudrate...choose one, comment the others.
//#define BR_19200    //!< Desired baudrate...choose one, comment the others.
//#define BR_38400      //!< Desired baudrate...choose one, comment the others.

//This section chooses the correct timer values for the chosen baudrate.
#ifdef  BR_9600
    #define TICKS2COUNT         103  //!< Ticks between two bits.
    #define TICKS2WAITONE       103  //!< Wait one bit period.
    #define TICKS2WAITONE_HALF  155  //!< Wait one and a half bit period.
#endif
#ifdef  BR_19200
    #define TICKS2COUNT          51  //!< Ticks between two bits.
    #define TICKS2WAITONE        51  //!< Wait one bit period.
    #define TICKS2WAITONE_HALF   77  //!< Wait one and a half bit period.
#endif
#ifdef  BR_38400
    #define TICKS2COUNT          25  //!< Ticks between two bits.
    #define TICKS2WAITONE        25  //!< Wait one bit period.
    #define TICKS2WAITONE_HALF   38  //!< Wait one and a half bit period.
#endif

#define INTERRUPT_EXEC_CYCL   9       //!< Cycles to execute interrupt rutine from interrupt.

//Some IO, timer and interrupt specific defines.

#if  (defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__))
    #define ENABLE_TIMER_INTERRUPT( )       ( TIMSK |= ( 1<< OCIE0 ) )
    #define DISABLE_TIMER_INTERRUPT( )      ( TIMSK &= ~( 1<< OCIE0 ) )
    #define CLEAR_TIMER_INTERRUPT( )        ( TIFR |= ((1 << OCF0) ) )
    #define ENABLE_EXTERNAL0_INTERRUPT( )   ( GICR |= ( 1<< INT0 ) )
    #define DISABLE_EXTERNAL0_INTERRUPT( )  ( GICR &= ~( 1<< INT0 ) )
    #define TX_PIN           PD3               //!< Transmit data pin
    #define RX_PIN           PD2               //!< Receive data pin, must be INT0
    #define TCCR             TCCR0             //!< Timer/Counter Control Register
    #define TCCR_P           TCCR0             //!< Timer/Counter Control (Prescaler) Register
    #define OCR              OCR0              //!< Output Compare Register
    #define EXT_IFR          GIFR              //!< External Interrupt Flag Register
    #define EXT_ICR          MCUCR             //!< External Interrupt Control Register
    #define TIMER_COMP_VECT  TIMER0_COMP_vect  //!< Timer Compare Interrupt Vector
    #define TRXDDR  DDRD
    #define TRXPORT PORTD
    #define TRXPIN  PIND  
  
#elif defined(__AVR_ATmega128__)
    #define ENABLE_TIMER_INTERRUPT( )       ( TIMSK |= ( 1<< OCIE0 ) )
    #define DISABLE_TIMER_INTERRUPT( )      ( TIMSK &= ~( 1<< OCIE0 ) )
    #define CLEAR_TIMER_INTERRUPT( )        ( TIFR |= ((1 << OCF0) ) )
    #define ENABLE_EXTERNAL0_INTERRUPT( )   ( EIMSK |= ( 1<< INT0 ) )
    #define DISABLE_EXTERNAL0_INTERRUPT( )  ( EIMSK &= ~( 1<< INT0 ) )
    #define TX_PIN           PD1               //!< Transmit data pin
    #define RX_PIN           PD0               //!< Receive data pin, must be INT0
    #define TCCR             TCCR0             //!< Timer/Counter Control Register
    #define TCCR_P           TCCR0             //!< Timer/Counter Control (Prescaler) Register
    #define OCR              OCR0              //!< Output Compare Register
    #define EXT_IFR          EIFR              //!< External Interrupt Flag Register
    #define EXT_ICR          EICRA             //!< External Interrupt Control Register
    #define TIMER_COMP_VECT  TIMER0_COMP_vect  //!< Timer Compare Interrupt Vector
    #define TRXDDR  DDRD
    #define TRXPORT PORTD
    #define TRXPIN  PIND  
  
#elif defined(__AVR_ATmega169__)
    #define ENABLE_TIMER_INTERRUPT( )       ( TIMSK0 |= ( 1<< OCIE0A ) )
    #define DISABLE_TIMER_INTERRUPT( )      ( TIMSK0 &= ~( 1<< OCIE0A ) )
    #define CLEAR_TIMER_INTERRUPT( )        ( TIFR0 |= ((1 << OCF0A) ) )
    #define ENABLE_EXTERNAL0_INTERRUPT( )   ( EIMSK |= ( 1<< INT0 ) )
    #define DISABLE_EXTERNAL0_INTERRUPT( )  ( EIMSK &= ~( 1<< INT0 ) )
    #define TX_PIN           PD3               //!< Transmit data pin
    #define RX_PIN           PD1               //!< Receive data pin, must be INT0
    #define TCCR             TCCR0A            //!< Timer/Counter Control Register
    #define TCCR_P           TCCR0A            //!< Timer/Counter Control (Prescaler) Register
    #define OCR              OCR0A             //!< Output Compare Register
    #define EXT_IFR          EIFR              //!< External Interrupt Flag Register
    #define EXT_ICR          EICRA             //!< External Interrupt Control Register
    #define TIMER_COMP_VECT  TIMER0_COMP_vect  //!< Timer Compare Interrupt Vector
    #define TRXDDR  DDRD
    #define TRXPORT PORTD
    #define TRXPIN  PIND  
  
#elif (defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__))
    #define ENABLE_TIMER_INTERRUPT( )       ( TIMSK0 |= ( 1<< OCIE0A ) )
    #define DISABLE_TIMER_INTERRUPT( )      ( TIMSK0 &= ~( 1<< OCIE0A ) )
    #define CLEAR_TIMER_INTERRUPT( )        ( TIFR0 |= ((1 << OCF0A) ) )
    #define ENABLE_EXTERNAL0_INTERRUPT( )   ( EIMSK |= ( 1<< INT0 ) )
    #define DISABLE_EXTERNAL0_INTERRUPT( )  ( EIMSK &= ~( 1<< INT0 ) )
    #define TX_PIN           PD3                //!< Transmit data pin
    #define RX_PIN           PD2                //!< Receive data pin, must be INT0
    #define TCCR             TCCR0A             //!< Timer/Counter Control Register
    #define TCCR_P           TCCR0B             //!< Timer/Counter Control (Prescaler) Register
    #define OCR              OCR0A              //!< Output Compare Register
    #define EXT_IFR          EIFR               //!< External Interrupt Flag Register
    #define EXT_ICR          EICRA              //!< External Interrupt Control Register
    #define TIMER_COMP_VECT  TIMER0_COMPA_vect  //!< Timer Compare Interrupt Vector
    #define TRXDDR  DDRD
    #define TRXPORT PORTD
    #define TRXPIN  PIND  
  
#elif (defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny45__))
    #define ENABLE_TIMER_INTERRUPT( )       ( TIMSK |= ( 1<< OCIE0A ) )
    #define DISABLE_TIMER_INTERRUPT( )      ( TIMSK &= ~( 1<< OCIE0A ) )
    #define CLEAR_TIMER_INTERRUPT( )        ( TIFR  |= ((1 << OCF0A) ) )
    #define ENABLE_EXTERNAL0_INTERRUPT( )   ( GIMSK |= ( 1<< INT0 ) )
    #define DISABLE_EXTERNAL0_INTERRUPT( )  ( GIMSK &= ~( 1<< INT0 ) )
    #define TX_PIN           PB3                //!< Transmit data pin
    #define RX_PIN           PB2                //!< Receive data pin, must be INT0 (only PB2)
    #define TCCR             TCCR0A             //!< Timer/Counter Control Register
    #define TCCR_P           TCCR0B             //!< Timer/Counter Control (Prescaler) Register
    #define OCR              OCR0A              //!< Output Compare Register
    #define EXT_IFR          GIFR               //!< External Interrupt Flag Register
    #define EXT_ICR          MCUCR              //!< External Interrupt Control Register
    #define TIMER_COMP_VECT  TIMER0_COMPA_vect  //!< Timer Compare Interrupt Vector
    #define TRXDDR  DDRB
    #define TRXPORT PORTB
    #define TRXPIN  PINB
  
#else
    #warning Selected AVR device is not supported
#endif

#define SET_TX_PIN( )    ( TRXPORT |= ( 1 << TX_PIN ) )
#define CLEAR_TX_PIN( )  ( TRXPORT &= ~( 1 << TX_PIN ) )
#define GET_RX_PIN( )    ( TRXPIN & ( 1 << RX_PIN ) )

/* Type defined enumeration holding software UART's state.
 *
 */
typedef enum
{
    IDLE,                                       //!< Idle state, both transmit and receive possible.
    TRANSMIT,                                   //!< Transmitting byte.
    TRANSMIT_STOP_BIT,                          //!< Transmitting stop bit.
    RECEIVE,                                    //!< Receiving byte.
    DATA_PENDING                                //!< Byte received and ready to read.

}AsynchronousStates_t;

volatile AsynchronousStates_t state;     //!< Holds the state of the UART.
volatile unsigned char SwUartTXData;     //!< Data to be transmitted.
volatile unsigned char SwUartTXBitCount; //!< TX bit counter.
volatile unsigned char SwUartRXData;     //!< Storage for received bits.
volatile unsigned char SwUartRXBitCount; //!< RX bit counter.

void initSoftwareUart( void );
void print_string( const unsigned char *data );
void putChar( const unsigned char c );

#endif

