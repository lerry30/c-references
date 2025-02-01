#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRD = DDRD & ~(1 << DDD2); // push button set as input
    DDRB = DDRB | (1 << DDB4); // led set as output
                               //
                               // PID = input
                               // PORT = output
    while(1) {
        // waiting for input
        if(PIND & (1 << PIND2)) { // check if button is push
            PORTB = PORTB | (1 << PORTB4); // turn on led
        } else {
            PORTB = PORTB & ~(1 << PORTB4); // turn off led
        }
    }

    return 0;
}
