# SoftwareUart
Software UART library for serial communication with ATTiny and ATMega MCU's

SofwareUart is an evolution of of ATMEL's AVR304 UART proof of concept without
using the USI/USART module, but relies instead on timer and pin change
interrupts. The original software was written for the iar compiler and ATmega16/128/169 MCU's. It is now ported to gcc compiler, and extended to
ATTiny AVR's. SoftwareUart has been tested on an ATTiny85 and found working. 

## Compatibility
Minimal changes in the macro's should have maintained compatibility with the 
original ATmega devices. These are: 
- ATmega16, ATmega32
- ATmega128
- ATmega169
- ATmega48, ATmega88

The added ATtiny Devices:
- ATtiny85, ATtiny45
- Attiny25 should work as well. 

## Compiling 
The code is now compatible with avr-gcc compiler and the associated libraries. 
For convenience a compiler script is added which assumes a buspirate programmer 
on /dev/ttyUSB0. 

The code compiles to 628 bytes of program, and 48 bytes of data, which fits in 
flash of all 3 ATTiny MCU's mentioned above. 

## Default settings
- 9600 Baud, no parity, 1 stopbit (8N1)
- TX pin (on MCU): PB3
- RX pin (on MCU): PB2

Note that the RX (receiving) pin of the AVR must be an INT0 pin, so it can 
trigger an interrupt on rising/falling edge. For the ATTiny85/45/25 the only 
INT0 pin is PB2. 

## Code Specifics
Timer/Counter Control Register B is used to switch on/of the clock, by setting 
both 3 bits CS02/CS02/CS00 to 0. However in the code only CS01 used to perform 
this action. 
The code assumes the MCU is running on 8MHz, and uses a counter prescaler of
1/8th. 
initSoftwareUart:
- sets the RX and TX pins to in/output, and puts TX high. 
- initializes the timer to reset itself after compare match, and uses the 1/8th
prescaler. Timer interrup is disables. 
- sets the external interrup on the falling edge, and ebales it. 
- sets the state to IDLE.
ISR(INT0_vect)
- changes state to RECEIVE, and disables external iterrupt
- sets the counter forward to a predetermined (tuned) number of counts taking 
into account the required clock ticks to execute the interrupt service routine.
- sets the counter compare one and a half period further to skip to the first 
bit sent. 
- sets the bitoucter for RX to 0; 
- clears/enables timer interrupt (e.g. arms it). 
ISR(TIMER_COMP_VECT)
- in RECEIVE state (set by ISR(IN0_vect) when INT0 is trigered):
-- set the counter compare one bit further for the next bit already.
-- reads the bit from RX pin and puts in SWUartRXData, increases the bit counter, 
or puts the state to DATA_PENDING to indicate the tranmission of the byte is 
complete, disables timer iterrupt, clears the INT0 interrupt, and enables INT0 
again. 
-- Note that during reception the INT0 interrupt is first triggered, then the
timer interrupt is triggered multiple times to receive the byte, after which
the INT0 interrupt flag is cleared and armed again. 
- in TRANSMIT state ( set when ????????? ):
-- sends the bit in SwUartTXData and increases the bitcounter, or sends the stop-
bit and sets the state to TRANSMIT_STOP_BIT, or disables the timer interrupt, 
changes state to IDLE and enables INT0 iterrupt. 
putChar():
- sets state to TRANSMIT, disables INT0, writes byte to UART register, sets the
bitcount to 0
- clears the counter to 0
- sets the TX pin to 0 (start bit)
- Enable timer interrupt (was it not set?) 




Published under MIT License, Copyright © 2026 Joseph Heller / CATCH22eu / Github
