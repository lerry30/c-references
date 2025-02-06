#include "print_string.h"

void usart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << TXEN0);                // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
}

void usart_transmit(char data) {
    while(!(UCSR0A & (1 << UDRE0))); // Wait for empty buffer
    UDR0 = data;
}

void printstring(const char *str) {
    while (*str) {
        usart_transmit(*str++);
    }
}
