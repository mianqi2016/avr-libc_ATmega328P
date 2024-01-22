#ifndef F_CPU
#define F_CPU 16000000UL // Defining the CPU Frequency
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h> //atoi & itoa

#include "ADC.h"
#include "USART.h"

unsigned int valueADC = 0;
char stringADC[] = {'1', '2', '3', '4', '\0'}; // 0-1023 + '/0'
uint8_t freqADC = 0;


void Timer0_Init()
{
  //Normal Mode - The TOV0 Flag in this case behaves like a ninth bit, except
  //that it is only set, not cleared. However, combined with the timer overflow interrupt
  //that automatically clears the TOV0 flag, the timer resolution can be increased by software.
  
  TCCR0B |= (1<<CS02) | (0<<CS01) | (1<<CS00); // clkT2S/1024 (from prescaler)
  TIMSK0 |= (1<<TOIE0); //Timer/Counter0 Overflow Interrupt Enable
  TCNT0 = (255-125); // 15625=125*125;
}


int main(void)
{
  Timer0_Init();  
  USART0_Init();
  ADC_Init();
  
  sei();
  
  _delay_ms(10);
  
    /* Replace with your application code */
    while (1) 
    {
    if(freqADC >= 5)
    {
      valueADC = ADC_Read(5);
      itoa(valueADC, stringADC, 10);
      USART0_putChar('T');
      USART0_putString(stringADC);
      
      freqADC = 0;
    }
    _delay_ms(5);
    }
}

ISR(TIMER0_OVF_vect)
{
  ++freqADC;
  TCNT0 = (255-125); //15625/125/5=25, 1000/25=40ms
}


