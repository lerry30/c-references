#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "print_string.h"
#include "adc.h"

void pulse_init() {
    // Set PB3 (Pin 11, OC2A) as output
    DDRB |= (1 << DDB3);
    
    // Clear all timer settings first
    TCCR2A = 0;
    TCCR2B = 0;
    
    // Configure Timer2 for Phase Correct PWM mode
    TCCR2A |= (1 << WGM20);              // Phase Correct PWM mode
    TCCR2A |= (1 << COM2A1);             // Clear on compare match when up-counting
    TCCR2B |= (1 << CS22);               // Prescaler = 64
    
    OCR2A = 0;                           // Start with LED off
}

int main(void) {
    char text[10];

    usart_init(MYUBRR);
    adc_init();  // Initialize ADC
    pulse_init();

    while (1) {
        uint16_t adc_value = adc_read();
        uint8_t range_set = (adc_value * 255UL) / 1023;

        sprintf(text, "%d\r\n", range_set); // convert number to string
        printstring(text);

        OCR2A = range_set;
        
        _delay_ms(100);
    }

    return 0;
}

