#include "led_display.h"

uint8_t d_num[4]; // the get_digits() funtion will break the input to digits and store here as array.
uint8_t led_masks[] = {d4, d3, d2, d1}; // array contains digit 1-4 switch
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
    // 1. pin5  - A - PD5
    // 2. pin12 - B - PB4
    // 3. pin10 - C - PD7
    // 4. pin4  - D - PD4
    // 5. pin3  - E - PD3
    // 6. pin6  - F - PD6
    // 7. pin11 - G - PB3

    // set segment pins as output
    DDRD |= (1 << DDD5); // a
    DDRB |= (1 << DDB4); // b
    DDRD |= (1 << DDD7); // c
    DDRD |= (1 << DDD4); // d
    DDRD |= (1 << DDD3); // e
    DDRD |= (1 << DDD6); // f
    DDRB |= (1 << DDB3); // g

    DDRD |= (1 << DDD2); // decimal point pin2

    // set digit control pins as outputs
    DDRB |= (1 << DDB0); // D1 - pin8
    DDRB |= (1 << DDB1); // D2 - pin9
    DDRB |= (1 << DDB2); // D3 - pin10
    DDRB |= (1 << DDB5); // D4 - pin13
}

// break number to digits
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

    init_dr(); // set outputs of registers
}

// parameter num is the number to display
void run_led_display(uint16_t num) {
    get_digits(d_num, &num); // break digits and store to d_num array

    // to make sure if number is a single digit the follow digit display
    // will not display anything
    int8_t is_zero = 1; // boolea
    
    // reverse loop to ensure only digits needed to display and not
    // allowing 0s from the left of number
    // 4 digits - 1 for array, so initial value is 3
    for(int8_t i = 3; i >= 0; i--) { // make sure the i is signed integer since it inverts the loop when reaching -1 unsigned integer will be wrapped and restart its value to 255 ensuring no negative will happen.
        if(d_num[i] == 0 && is_zero == 1) continue; // prevents 0s in front(left) of number displayed
        is_zero = 0;

        // reset digti controls(switches)
        PORTB = (d1 | d2 | d3 | d4);
        
        // turn leds on by mapping to segment array base on digit passed as index
        // 7 segment
        if(segment[d_num[i]][0]) PORTD |= seg_a; else PORTD &= ~seg_a;
        if(segment[d_num[i]][1]) PORTB |= seg_b; else PORTB &= ~seg_b;
        if(segment[d_num[i]][2]) PORTD |= seg_c; else PORTD &= ~seg_c;
        if(segment[d_num[i]][3]) PORTD |= seg_d; else PORTD &= ~seg_d;
        if(segment[d_num[i]][4]) PORTD |= seg_e; else PORTD &= ~seg_e;
        if(segment[d_num[i]][5]) PORTD |= seg_f; else PORTD &= ~seg_f;
        if(segment[d_num[i]][6]) PORTB |= seg_g; else PORTB &= ~seg_g;

        // digit control(switch) mapping
        PORTB &= ~led_masks[i];

        // 2ms making short time illusion
        _delay_ms(2);
    }

    // reset digti controls(switches)
    PORTB = (d1 | d2 | d3 | d4);
}
