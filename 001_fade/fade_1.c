#define F_CPU 16000000UL
#define VREF 5
#define POT 10000 // potentiometer - ohm10K

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile double potVal=0;

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
  sei();
}


void loop() {
    potVal=potVal/1023.0*255;
    Serial.print("potVal = ");
    Serial.println(potVal);
    OCR2B=potVal;
}

void initADC()
{
  //select ADC channel ADC0
  ADMUX &= 0x11110000;
  // Select Vref=AVcc
  ADMUX |= (1<<REFS0);
  //set prescaller to 128 and enable ADC 
  ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
  // Bit 6 – ADSC: ADC Start Conversion
  // In single conversion mode, write this bit to one to start each conversion. 
  // In free running mode, write this bit to one to start the first conversion.
  ADCSRA |= (1<<ADSC);
  // Bit 3 – ADIE: ADC Interrupt Enable
  // When this bit is written to one and the I-bit in SREG is set, the ADC conversion complete interrupt is activated.
  ADCSRA |= (1<<ADIE);
  // Bit 5 – ADATE: ADC Auto Trigger Enable
  // When this bit is written to one, auto triggering of the ADC is enabled. 
  // The ADC will start a conversion on a positive edge of the selected trigger signal. 
  // The trigger source is selected by setting the ADC trigger select bits, ADTS in ADCSRB.
  ADCSRA |= (1<<ADATE); 
  //In free running mode, the ADC is constantly sampling and updating the ADC Data Registers.  
  //This mode is selected by the ADFR bit in the ADC Control and Status Register.
  ADCSRB = 0x00000000;// Free running mode - ADTS2=ADTS1=ADTS0=0;  
}

ISR(ADC_vect){
  potVal=ADC;
  //_delay_ms(10);
}
