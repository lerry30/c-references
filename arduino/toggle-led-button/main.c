#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRD = DDRD & ~(1 << DDD2);
    DDRB = DDRB | (1 << DDB4);

    while(1) {
        if(PIND & (1 << PIND2)) {
            PORTB = PORTB | (1 << PORTB4);
        } else {
            PORTB = PORTB & ~(1 << PORTB4);
        }
    }

    return 0;
}
