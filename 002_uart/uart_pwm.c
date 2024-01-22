/*
 * The program for adjusting the lightness of LED by a potentiometer
 * chip: ATmega328p
 * potentiometer --> ADC0
 * (ATmega328p)PB1 --> 1.5kOhm --> LED
 */
 
#define F_CPU 16000000UL
#define VREF 5
#define POT 10000 // potentiometer - 10Kohm

#include <avr/io.h>
#include <util/delay.h>

void timer1_init();
void initADC();
uint16_t readADC(uint8_t);
void promptPrint(void);

volatile uint16_t potVal = 0;
unsigned char helloworld[] = "potValue = ";

int main(void){
  // LED 接在：OC1A/ATmega328p PB1/Arduino UNO D9
    DDRB |= (1<<DDB1);

  // ADC 初始化
    initADC();

  // 初始化定时器1（16位）
    timer1_init();

  // 初始化串口
    USART0_init();

    while(1) {

  // ADC 读入
    potVal = readADC(0);
    OCR1A = (potVal/1023.0)*250;

  // 串口显示
    promptPrint();
    regToDigitAndTransmit(potVal);
    }
}

void timer1_init(){

  // OC1A 正向输出
    TCCR1A = (1 << COM1A1);

  // 模式14
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM13)|(1 << WGM12);

  // 预分频64 - frequency = 250kHz
    TCCR1B |= (1 << CS11)|(1 << CS10);

  // ICR1 作为置顶值
    ICR1 = 250;

  // OCR1A 初值：
    OCR1A = 3;

  // TCNT1 初值：
    TCNT1 = 0;
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

void promptPrint(void){
  for(int i = 0; i < sizeof(helloworld); i++){
    TX(helloworld[i]);   //echo back the received byte to the computer
  }
  _delay_ms(100);  
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

void TXstring(char* str) {
    while(*str) {
        TX(*str++);
    }
    TX('.');
    TX('\n');
}

unsigned char regToDigitAndTransmit(uint16_t valueADC){
    char buff[8];
    itoa(valueADC, buff, 10);
   //sprintf(buff, "%u.%02u", valueADC / 100, valueADC % 100);
    TXstring(buff);
}



