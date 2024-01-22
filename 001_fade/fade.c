#include <avr/io.h>
#include <util/delay.h>

void setup(){ 
  //WGM02/WGM01/WGM00 all set -> Mode 7, fast PWM
  //TCCR0A = (1<<COM0A1) + (1<<WGM01) + (1<<WGM00); // Set OC0A at bottom, clear OC0A at compare match
  //TCCR0B = (1<<CS02) + (1<<WGM02); // prescaler = 64; 
  //OCR0A = 249;
  //OCR0B = 49;
  //DDRD |= (1<<PD6);//D6 - 1.5Kohm - LED - GND

  // WGM22/WGM21/WGM20 all set -> Mode 7, fast PWM, TOP = OCR2A
  // Period = 2 ms / Frequenz = 500 Hz. 
  //TCCR2A = (1<<COM2A0) + (1<<WGM21) + (1<<WGM20); // Toggle OC2A at compare match
  //TCCR2B = (1<<CS22) + (1<<WGM22); // prescaler = 64; 
  //OCR2A = 249;
  //DDRB |= (1<<PB3); // PB3 = OC2A = Arduino Pin 11

  // Period = 1 ms => Frequenz = 1kHz
  // WGM22/WGM21/WGM20 all set -> Mode 7, fast PWM
  TCCR2A = (1<<COM2B1) + (1<<WGM21) + (1<<WGM20); // Set OC2B at bottom, clear OC2B at compare match
  TCCR2B = (1<<CS22) + (1<<WGM22); // prescaler = 64; 
  OCR2A = 249;
  OCR2B = 69;
  DDRD |= (1<<PD3);
} 

void loop() {
  for(int i = 49; i < 250; i++){
    OCR2B = i;
    _delay_ms(10);
  }
  for(int i = 249; i >= 49; i--){
    OCR2B = i;
    _delay_ms(10);
   }
 }
