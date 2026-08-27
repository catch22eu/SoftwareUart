# SoftwareUart
Software UART library for serial communication with ATTiny and ATMega MCU's

SofwareUart is an updated library of ATMEL's AVR304 software implementaitn of an UART, which was originally for the iar compiler and ATmega16/128/169 MCU's. It is now ported to gcc compiler, and extended to ATTiny AVR's. At least, the version in this github has been tested on an ATTiny85. 

Minimal changes in the macro's should have maintained compatibility with the original ATmega devices. These are: 
ATmega16, ATmega32
ATmega128
ATmega169
ATmega48, ATmega88

The added ATtiny Devices:
ATtiny85, ATtiny45

The code is now compatible with avr-gcc compiler and the associated libraries. For convenience a compiler script is added which assumes a buspirate programmer on /dev/ttyUSB0. 

Default settings
9600 Baud, no parity, 1 stopbit
TX pin: PB3
RX pin: PB2

Note that the RX (receiving) pin of the AVR must be an INT0 pin, so it can trigger an interrupt on rising/falling edge. For the ATTiny85 the only INT0 pin is PB2. 

Timer/Counter Control Register B is used to switch on/of the clock, by setting both 3 bits CS02/CS02/CS00 to 0. However in the code only CS01 used to perform this action. 


