#include <avr/io.h>
#include <util/delay.h>

int main(void) {
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
    
    uint8_t brightness = 0;
    int8_t direction = 1;
    
    while(1) {
        OCR2A = brightness;
        
        if (direction > 0) {
            if (brightness < 255) {
                brightness++;
            } else {
                direction = -1;
            }
        } else {
            if (brightness > 0) {
                brightness--;
            } else {
                direction = 1;
            }
        }
        
        _delay_ms(20);
    }
    
    return 0;
}
