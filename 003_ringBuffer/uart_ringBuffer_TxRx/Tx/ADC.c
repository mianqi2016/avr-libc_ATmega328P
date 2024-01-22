#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"

void ADC_Init()
{
  // set REFS1=0,REFS0=1 (Vref as AVCC pin), ADLAR = 0(right adjusted),
  // MUX3 to MUX0 is 0000 for ADC0, 0101 for ADC5;
  ADMUX = 0b01000000;
  //enable ADC module, ADC Interrupt Enable, set prescalar of 128 which gives CLK/128
  ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

unsigned int ADC_Read(unsigned char channel)
{
  /* set input channel to read */
  ADMUX = 0x40 | (channel & 0x07);   // 0100 0000 | (channel & 0000 0111)
  /* Start ADC conversion */
  ADCSRA |= (1<<ADSC);
  /* Wait until end of conversion by polling ADC interrupt flag */
  while (!(ADCSRA & (1<<ADIF)));
  _delay_ms(1);                      /* Wait a little bit */
  /* Return ADC word */
  return ADCW;
}
