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


