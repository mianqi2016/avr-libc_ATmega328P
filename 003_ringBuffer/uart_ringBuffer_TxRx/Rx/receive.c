
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdlib.h> //atoi & itoa
#include <string.h> //strcpy()
#include <ctype.h> //isdigit()

#include "init.h"
#include "uart.h"
#include "ringBuffer.h"

volatile unsigned int sampleTicks = 0;
char stringFromUART[5] = {'0'};
uint8_t charGet = '\0';
unsigned int freqLED = 0;

int main(void)
{
  LED_Init();
  Timer2_Init();
  uart0_init();
  ring_head = 0;
  ring_tail = 0;
  sei();
  
  /* Replace with your application code */
  while (1)
  {    
    if(remove() == 'T')
    {
      _delay_ms(1);
      stringFromUART[0] = remove();
      _delay_ms(1);
      stringFromUART[1] = remove();
      _delay_ms(1);
      stringFromUART[2] = remove();
      _delay_ms(1);
      stringFromUART[3] = remove();
      _delay_ms(1);
      stringFromUART[4] = '\0';
      _delay_ms(1);

      uart0_putString(stringFromUART);

      freqLED = atoi(stringFromUART);
      freqLED = freqLED/32;  //0-1023 --> 0-32
      OCR2A = freqLED;
    }

    //_delay_ms(10);
    if(sampleTicks >= 125)  //15625=125*125
    {
      PORTB ^= (1<<PORTB0);
      sampleTicks = 0;
    }
  }
}

ISR(TIMER2_COMPA_vect)
{
  ++sampleTicks;
}

ISR(USART_RX_vect)
{
  uint8_t dataRecv;
  dataRecv = UDR0;
  add(dataRecv);
}
