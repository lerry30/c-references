#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // set PORTB5 as an output
    DDRB = DDRB | (1 << DDB4);
    DDRB = DDRB | (1 << DDB0);

    while(1) {
        // set PORTB4
        PORTB = PORTB | (1 << PORTB4);
        PORTB = PORTB & ~(1 << PORTB0);

        // wait
        _delay_ms(1000);

        // unset PORTB5
        PORTB = PORTB & ~(1 << PORTB4);
        PORTB = PORTB | (1 << PORTB0);

        // wait
        _delay_ms(1000);
    }

    return 0;
}
