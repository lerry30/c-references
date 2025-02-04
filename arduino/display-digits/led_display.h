#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include <avr/io.h>
#include <util/delay.h>

// Define digit control pins
#define d1 (1 << PORTB0)
#define d2 (1 << PORTB1)
#define d3 (1 << PORTB2)
#define d4 (1 << PORTB5)

#define seg_a (1 << PORTD5)
#define seg_b (1 << PORTB4)
#define seg_c (1 << PORTD7)
#define seg_d (1 << PORTD4)
#define seg_e (1 << PORTD3)
#define seg_f (1 << PORTD6)
#define seg_g (1 << PORTB3)

// Function prototypes
void init_led_display(void);
void run_led_display(uint16_t num);

#endif
