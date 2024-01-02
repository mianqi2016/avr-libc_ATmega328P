// A program for LED Blink on ATmega328p

 /*
 * LED - 1.5Kohm - D8(PB0/PCINT0)
 */

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define BLINK_MS 500

int main(){

    DDRB |=  0b00000001;
    //DDRB |= (1 << PORTB0);
    //DDRB |= _BV(PORTB0);

    while(true){
        PORTB |= 0b00000001;
        _delay_ms(BLINK_MS);

        PORTB &= ~0b00000001;
        _delay_ms(BLINK_MS);

        //PORTB ^= _BV(PORTB0);
        //_delay_ms(BLINK_MS);
    }
}
