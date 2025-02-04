#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD-1)

void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << TXEN0);                // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
}

void USART_Transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait for empty buffer
    UDR0 = data;
}

void printString(const char *str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}

int main(void) {
    USART_Init(MYUBRR);

    while (1) {
        printString("Hello, Serial Monitor!\r\n");
        _delay_ms(10000);
    }

    return 0;
}
