#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

volatile uint8_t pinb = 0;

int main(void){
  sei();  // call sei() to switch on the interrupting system
  //DDRB &= ~(1<<DDB0);
  DDRB |= (1<<PINB0);
  //DDRD |= (1<<DDD7);
  DDRD &= ~(1<<PIND7);

  PCICR = (1<<PCIE2);
  //PCICR = 0x00000100; // Pin Change Interrupt Enable 2
  PCMSK2 = (1<<PCINT23);  //0x10000000; PCINT23 enabled
  //PCMSK2 = (1<<PIND7);

  while(true){
    ;
  }
}

ISR(PCINT2_vect)
{
  //pinb = PINB;
  //PORTB = PINB ^ pinb;

  // Method-1:
  //PINB = (1 << PINB0);
  
  // Method-2:
  uint8_t rising = PIND & (1 << 7);
  if (rising) PORTB ^= (1 << 0);
}
