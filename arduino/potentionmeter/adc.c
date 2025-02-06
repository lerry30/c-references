#include "adc.h"

void adc_init() {
    ADMUX = (1 << REFS0);  // AVcc as reference, select ADC0 (A0)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Enable ADC, Prescaler = 128
}

uint16_t adc_read() {
    ADCSRA |= (1 << ADSC);  // Start conversion
    while (ADCSRA & (1 << ADSC));  // Wait for conversion to complete
    return ADC;  // Return 10-bit result
}
