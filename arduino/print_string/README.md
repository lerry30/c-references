### Printing Text

It is really important for me to be able to inpect the value
of something to have wide range of understanding about it.

```c
#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD-1)
```

In this declarations of defined variables the computation for
identifying the baud size with 16Mhz clock speed is essential
for defining serial communication size and speed.

```c
UBRR0H = (unsigned char)(ubrr >> 8);
UBRR0L = (unsigned char)ubrr;
```

Lets say the above computation is 16000000/(16*9600)-1 = 130,
and from what I know it cannot be fit in 8 bit register that's
why 2 registers are utilized in this case(UBRR0H, UBRR0L). Therefor
they hold this value as configuration for serial communication.

```c
UCSR0B = (1 << TXEN0);                // Enable transmitter
```

Register UCSR0B handling for the control of enabling and disabling
the state of transmission and reception. The bit TXEN0 is to
activate the transmitter or deactivate it.

```c
UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
```

It is a register to define the size of data to be transmitted,
thereby these two bits represent 8 bits of data size, since 
dealing with characters A-Z and 0-9 and so on consist of 255
characters. 8 bit size has 255 combinations(range).

```c
while (1) {
    printString("Hello, Serial Monitor!\r\n");
    _delay_ms(10000);
}

void printString(const char *str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}
```
In C programming string is array of characters, so the printString
accepts string of pointer. The while(*str) loop loops this array
of string until it reach the null terminator, null terminator '\0',
is a character to indicates the end of string. Adding '*' refers to
the value which in this case it will start from first value of array
which is character. The USART_Transmit(*str++);, is a function that
acquire the character or single value of the array. '++' will jump
to the next slot in memory or next character.

```c
void USART_Transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait for empty buffer
    UDR0 = data;
}
```

The regiter UCSR0A holds the state of previous attemp of transmitting
data whether successfull or not. This while loop waits until the transmission
of previous data is done. So it ensure the completeness of data sent.

```c
UDR0 = data;
```

Is a regiter of 8 bits, it means 255 character in ASCII table can be sent.
It is me but it is like pouring data in this register triggers transmitter
to send data.
