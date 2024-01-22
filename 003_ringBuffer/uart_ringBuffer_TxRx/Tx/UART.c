#include "USART.h"

void USART0_Init()
{
  // Set Baud Rate
  UBRR0H = BAUD_PRESCALER >> 8;
  UBRR0L = BAUD_PRESCALER;
  
  // Set Frame Format
  UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
  
  // Enable Receiver and Transmitter
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

uint8_t USART0_getChar()
{
  uint8_t dataRecv;
  while((UCSR0A & (1<<RXC0)) == 0) {};
  dataRecv = UDR0;
  return dataRecv;
}

void USART0_putChar(uint8_t DataByte)
{
  while((UCSR0A & (1<<UDRE0)) == 0) {}; // Do nothing until UDR is ready
  UDR0 = DataByte;
  while((UCSR0A & (1<<TXC0)) == 0) {}; // Do nothing until TX is completed
}

void USART0_putString(char *str)
{
  int i = 0;
  
  while(str[i] != '\0')
  {
    USART0_putChar(str[i]);
    ++i;
  }
  USART0_putChar('\0');
}
