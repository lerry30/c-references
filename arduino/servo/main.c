#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Set PB1 (Pin 9, OC1A) as output
    DDRB |= (1 << DDB1);
    
    // Clear any previous settings
    TCCR1A = 0;
    TCCR1B = 0;
    
    // Set Timer1 for 16MHz with prescaler of 8
    ICR1 = 40000;   // Set for 50Hz (20ms cycle)
    
    // Set up Timer1 in Fast PWM mode with ICR1 as TOP
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
    
    while(1) {
        // Go to 0 degrees
        OCR1A = 1000;  // Shorter pulse for 0 degrees
        _delay_ms(2000);
        
        // Go to 90 degrees
        OCR1A = 3000;  // Middle position
        _delay_ms(2000);
        
        // Go to 180 degrees
        OCR1A = 5000;  // Longer pulse for 180 degrees
        _delay_ms(2000);
    }
    
    return 0;
}
