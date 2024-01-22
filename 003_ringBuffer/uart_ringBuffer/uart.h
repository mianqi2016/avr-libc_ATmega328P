#include <avr/io.h>

#ifndef F_CPU
//#define F_CPU 16000000UL // Defining the CPU Frequency
#define F_CPU 16000000UL // Defining the CPU Frequency
#endif

#ifndef USART_H_
#define USART_H_

//It was tested, both 9600 and 250k work properly in this project
#define USART_BAUDRATE 250000 // Desired Baud Rate
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection

#define DISABLED    (0<<UPM00)
#define EVEN_PARITY (2<<UPM00)
#define ODD_PARITY  (3<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection

#define ONE_BIT (0<<USBS0)
#define TWO_BIT (1<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection

#define FIVE_BIT  (0<<UCSZ00)
#define SIX_BIT   (1<<UCSZ00)
#define SEVEN_BIT (2<<UCSZ00)
#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection

#define RX_COMPLETE_INTERRUPT         (1<<RXCIE0)
#define DATA_REGISTER_EMPTY_INTERRUPT (1<<UDRIE0)


void uart0_init(void);
uint8_t uart0_getChar(void);
void uart0_putChar(uint8_t DataByte);
void uart0_putString(char *str);


#endif /* USART_H_ */
