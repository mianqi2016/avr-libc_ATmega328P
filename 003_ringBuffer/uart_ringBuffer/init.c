#include "init.h"

void Timer2_Init(void)
{
  //The simplest mode of operation is the normal mode (WGM22:0 = 0).
  TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20); // clkT2S/1024 (from prescaler)
  TIMSK2 = (1<<TOV2);
  TCNT2 = 0;
}

void LED_Init(void)
{
  DDRB |= (1<< DDB5) | (1<<DDB0);
  //DDRB = 0b00100001; // Turn off LED_13 on Arduino UNO
  PORTB |= (1<<PORTB0);
  //PORTB = 0b00000001;
}

