#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdlib.h> //atoi & itoa
#include <string.h> //strcpy()

#include "init.h"
#include "uart.h"
#include "ringBuffer.h"

unsigned int sampleTicks = 0;

uint8_t charPut = '\0';

int main(void)
{
  LED_Init();
  Timer2_Init();
  uart0_init();
  
  sei();
  
  /* Replace with your application code */
  while (1)
  {
    if(sampleTicks >= 100)
    {
      PORTB ^= (1<<PORTB0);
      sampleTicks = 0;
      //TCNT0 = valueTCNT;
      
      charPut = remove();
      uart0_putChar(charPut);
    }
    _delay_ms(10);
  }
}

ISR(TIMER2_OVF_vect)
{
  ++sampleTicks;
  TCNT2 = 200;
}

ISR(USART_RX_vect)
{
  uint8_t dataRecv;
  dataRecv = UDR0;
  add(dataRecv);
}
