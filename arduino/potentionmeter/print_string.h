#ifndef PRINT_STRING_H
#define PRINT_STRING_H

#include <avr/io.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD-1)

void usart_init(unsigned int ubrr);
void printstring(const char *str);

#endif
