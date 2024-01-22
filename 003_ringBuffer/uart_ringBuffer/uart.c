#include "uart.h"

void uart0_init(void)
{
  // Set Baud Rate
  UBRR0H = BAUD_PRESCALER >> 8;
  UBRR0L = BAUD_PRESCALER;
  
  // Set Frame Format
  UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
  
  // Enable Receiver and Transmitter
  UCSR0B = (1<<RXEN0) | (1<<TXEN0);
  
  // Enable Receiver Interrupt
  UCSR0B |= RX_COMPLETE_INTERRUPT;
}

uint8_t uart0_getChar(void)
{
  uint8_t dataRecv;
  while((UCSR0A & (1<<RXC0)) == 0) {};
  dataRecv = UDR0;
  return dataRecv;
}

void uart0_putChar(uint8_t DataByte)
{
  while((UCSR0A & (1<<UDRE0)) == 0) {}; // Do nothing until UDR is ready
  UDR0 = DataByte;
  while((UCSR0A & (1<<TXC0)) == 0) {}; // Do nothing until TX is completed
}

void uart0_putString(char *str)
{
  int i = 0;
  
  while(str[i] != '\0')
  {
    uart0_putChar(str[i]);
    ++i;
  }
  uart0_putChar('\0');
}
