### Getting Started

Install libraries needed for linux system.

```bash
sudo apt install avr-libc avrdude binutils-avr gcc-avr
```

To run a certain app run this command in the root directory.
```bash
make
```

Make sure the root directory contains Makefile.

### Interaction with Arduino

Arduino's microcontroller(ATmega328p) uses ports to send signals for pins and allow
interaction on its outside world. It has 3 Ports Port D, B and C which is 8 bit regiter
each. It has 32 general purpose registers. It also consists of 14 digital I/O pins, 6 
analog inputs, and powered by a 16MHz crystal oscillator.

Pins has corresponding bit in microcontrollers. So handling microcontroller's regiters
are necessary to send signals to pins.

First having understanding on how program can set value to regiters.

The avr/io.h in C program provides special like variables to define each pin and register.

- DDRB for B register, it is normally used to modify the value of each bit in register
    of microcontroller.
- DDB5 is bit specific in B register. Therefore the B5 is a way to communicate on port B5
    which is the built in LED of arduino.
- PORTB is referring to all pins/ports or I/O B(B0-B7).
- PORTB5 is pin/port specific to communicate on outside world components.





