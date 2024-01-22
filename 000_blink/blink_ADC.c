/*
 * The program for adjusting the LED blinking frequency by a potentiometer
 * chip: ATmega328p
 * potentiometer --> ADC0
 * (ATmega328p)PB0 --> 1.5kOhm --> LED
 */
 
#define F_CPU 16000000UL
#define VREF 5
#define POT 10000 // potentiometer - 10Kohm

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t potVal = 0;

/* Sampling from ADC and then will be Transmitted through USART0 */
unsigned char digit_0 = 0;
unsigned char digit_1 = 0;
unsigned char digit_2 = 0;
unsigned char digit_3 = 0;

unsigned char helloworld[] = "potValue = ";

void PB0_init();
void initADC();
uint16_t readADC(uint8_t);


  
int main(void)
{       
    // initialize ADC
    initADC();

    // LED connected to PB0/D8
    //PB0_init();
    DDRB |= (1<<DDB0);
    

    // initialize Serial
    USART0_init();
 
    // loop forever
    while(1)
    {
      potVal = readADC(0);      
      PB0_toggle(potVal);
      regToDigitAndTransmit(potVal); 
    }
}

void initADC()
{
  // Select V ref=AVcc
  // Bit 7:6 – REFS1:0: Reference Selection Bits
  // REFS1 REFS0 - 0 / 1 - AVCC with external capacitor at AREF pin
  ADMUX |= (1<<REFS0);

  // Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
  // These bits determine the division factor between the system clock frequency and the input clock to the ADC.
  //set prescaler to 128 
  ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  // Bit 7 – ADEN: ADC Enable - Writing this bit to one enables the ADC.
  ADCSRA |= (1<<ADEN);

  // Bit 6 – ADSC: ADC Start Conversion
  // The first conversion after ADSC has been written after the ADC has been enabled, 
  // or if ADSC is written at the same time as the ADC is enabled, 
  // will take 25 ADC clock cycles instead of the normal 13. 
  // This first conversion performs initialization of the ADC.
  ADCSRA |= (1<<ADSC);
}

uint16_t readADC(uint8_t ADCchannel)
{
  //select ADC channel with safety mask
  ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);

  // A single conversion is started by disabling the power reduction ADC bit, PRADC, by writing a logical zero to it 
  // and writing a logical one to the ADC start conversion bit, ADSC.
  ADCSRA |= (1<<ADSC);
   
  // wait until ADC conversion is complete
  while( ADCSRA & (1<<ADSC) );
  
  return ADC;
}

void PB0_init(void){
   DDRB |= (1<<DDB0);
}

void PB0_toggle(int t){
   PORTB ^= (1<<PORTB0); // toggles the led
   for(int i = 0; i < t; i++){
     _delay_ms(1);
   }
}

void USART0_init(void) {
    UCSR0A = B00000000; //single transmission speed, multiprocessor disabled
    UCSR0B = B00011000; //enable Rx & Tx
    UCSR0C = B00000110; //asynchronous, no parity, 1 stop, 8 bits
    UBRR0 = 103;        //load the value for 9600 bps baud rate into whole UBRR register
}

void TX(unsigned char TXData) {
    //do nothing until UDR0 is ready for more data to be written to it; wait for USART UDRE flag
    while ((UCSR0A & (1 << UDRE0)) == 0) {}; 
    //when flag is set send data by placing the byte into UDR0
    UDR0 = TXData; 
}

void promptPrint(void){
  for(int i = 0; i < sizeof(helloworld); i++){
    TX(helloworld[i]);   //echo back the received byte to the computer
  }
  
  _delay_ms(100);  
}

unsigned char regToDigitAndTransmit(uint16_t valueADC){
    digit_0 = valueADC/1000;
    unsigned char number_0 = digit_0 + 48;
    digit_1 = (valueADC - (digit_0 * 1000))/100;
    unsigned char number_1 = digit_1 + 48;
    digit_2 = (valueADC - (digit_0 * 1000) - (digit_1 * 100))/10;
    unsigned char number_2 = digit_2 + 48;
    digit_3 = (valueADC - (digit_0 * 1000) - (digit_1 * 100) - (digit_2 * 10));
    unsigned char number_3 = digit_3 + 48;

    promptPrint();
    TX(number_0);
    TX(number_1);
    TX(number_2);
    TX(number_3);
  TX('.');
  TX('\n');
}
