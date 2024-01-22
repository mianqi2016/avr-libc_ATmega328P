#include <avr/io.h>

/*
 * A prescaler of 64 results in 249 for top. That’s 250 steps. 
 * One-fifth of it is 50. Since the counter starts at 0, OCR2B is 49, 
 * at least theoretically.
 */
// Period = 1 ms => Frequenz = 1kHz

void setup(){ 
  // WGM22/WGM21/WGM20 all set -> Mode 7, fast PWM
  TCCR2A = (1<<COM2B1) + (1<<WGM21) + (1<<WGM20); // Set OC2B at bottom, clear OC2B at compare match
  TCCR2B = (1<<CS22) + (1<<WGM22); // prescaler = 64; 
  OCR2A = 249;
  OCR2B = 49;
  DDRD |= (1<<PD3);//D3 - 1.5Kohm - LED - GND
  } 

void loop() {}
