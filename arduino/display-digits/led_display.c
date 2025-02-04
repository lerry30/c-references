#include "led_display.h"

uint8_t d_num[4];
uint8_t led_masks[] = {d4, d3, d2, d1};
uint8_t segment[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1} // 9
};

void init_dr(void) {
    // 1. 5  - A - PD5
    // 2. 12 - B - PB4
    // 3. 10 - C - PD7
    // 4. 4  - D - PD4
    // 5. 3  - E - PD3
    // 6. 6  - F - PD6
    // 7. 11 - G - PB3

    DDRD |= (1 << DDD5);
    DDRB |= (1 << DDB4);
    DDRD |= (1 << DDD7);
    DDRD |= (1 << DDD4);
    DDRD |= (1 << DDD3);
    DDRD |= (1 << DDD6);
    DDRB |= (1 << DDB3);

    DDRD |= (1 << DDD2); // decimal point

    DDRB |= (1 << DDB0); // D1 - pin8
    DDRB |= (1 << DDB1); // D2 - pin9
    DDRB |= (1 << DDB2); // D3 - pin10
    DDRB |= (1 << DDB5); // D4 - pin13
}
            
void get_digits(uint8_t* d_num, uint16_t* num) {
    uint16_t temp = *num;  // Create a temporary copy to preserve original number
    
    // Initialize all digits to 0
    for(uint8_t i = 0; i < 4; i++) {
        d_num[i] = 0;
    }
    
    // Fill in the actual numbers
    for(uint8_t i = 0; i < 4; i++) {
        if(temp == 0) break;
        d_num[i] = (uint8_t)(temp % 10);
        temp = temp / 10;
    }
}

void init_led_display() {
    // reset
    DDRB = 0b00000000;
    DDRD = 0b00000000;
    PORTB = 0b00000000;
    PORTD = 0b00000000;

    init_dr();
}

void run_led_display(uint16_t num) {
    get_digits(d_num, &num);

    int8_t is_zero = 1; // boolean
    // 4 digits - 1 for array, so initial value is 3
    for(int8_t i = 3; i >= 0; i--) {
        if(d_num[i] == 0 && is_zero == 1) continue;
        is_zero = 0;

        PORTB = (d1 | d2 | d3 | d4);
        
        // 7 segment
        if(segment[d_num[i]][0]) PORTD |= seg_a; else PORTD &= ~seg_a;
        if(segment[d_num[i]][1]) PORTB |= seg_b; else PORTB &= ~seg_b;
        if(segment[d_num[i]][2]) PORTD |= seg_c; else PORTD &= ~seg_c;
        if(segment[d_num[i]][3]) PORTD |= seg_d; else PORTD &= ~seg_d;
        if(segment[d_num[i]][4]) PORTD |= seg_e; else PORTD &= ~seg_e;
        if(segment[d_num[i]][5]) PORTD |= seg_f; else PORTD &= ~seg_f;
        if(segment[d_num[i]][6]) PORTB |= seg_g; else PORTB &= ~seg_g;

        PORTB &= ~led_masks[i];

        _delay_ms(2);
    }

    PORTB = (d1 | d2 | d3 | d4);
}
