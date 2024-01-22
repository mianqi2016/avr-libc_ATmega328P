#define F_CPU 16000000UL
#define VREF 5
#define POT 10000 // potentiometer - ohm10K

#include <avr/io.h>
#include <util/delay.h>

double potVal=0;

void setup(){
  Serial.begin(115200);
  
  // Period = 1 ms => Frequenz = 1kHz
  // WGM22/WGM21/WGM20 all set -> Mode 7, fast PWM
  TCCR2A = (1<<COM2B1) + (1<<WGM21) + (1<<WGM20); // Set OC2B at bottom, clear OC2B at compare match
  TCCR2B = (1<<CS22) + (1<<WGM22); // prescaler = 64; 
  OCR2A = 249;
  OCR2B = 69;
  DDRD |= (1<<PD3);
  initADC(); 
} 

void loop() {
    potVal=readADC(0);
    potVal=readADC(0)/1023.0*255;
    OCR2B=potVal; 
}


// AVR ADC must be clocked at a frequency between 50 and 200kHz. 
// So we need to set proper prescaller bits so that the scaled system clock would fit in this range. 
// As our AVR is clocked at 16MHz, 
// we will use 128 scaling factors by setting ADPS0, ADPS1, and ADPS2 bits in the ADCSRA register. 
// This gives 16000000/128=125kHz of ADC clock.
void initADC()
{
 // Select Vref=AVcc
 ADMUX |= (1<<REFS0);
 //set prescaller to 128 and enable ADC 
 ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);    
}

uint16_t readADC(uint8_t ADCchannel)
{
 //select ADC channel with safety mask
 ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
 //single conversion mode
 ADCSRA |= (1<<ADSC);
 // wait until ADC conversion is complete
 while( ADCSRA & (1<<ADSC) );
 return ADC;
}
