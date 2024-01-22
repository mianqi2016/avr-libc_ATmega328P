#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define SET(port,bit) port|=(1<<bit)
#define CLR(port,bit) port&=~(1<<bit)
#define TOGGLE(PORT,BIT) PORT^=(1<<BIT)


int count=0;
void timer0_init()
{
  CLR(TCCR0A,WGM00);//SET TIMER0 TO NORMAL MODE
  CLR(TCCR0A,WGM01);
  CLR(TCCR0B,WGM02);
  TCNT0=0X00;
  SET(SREG,7);
  SET(TIMSK0,TOIE0); // overflow interrupt enable
}

void enable_timer()
{
  SET(TCCR0B,CS00);//set prescalar to 1024
  CLR(TCCR0B,CS01);
  SET(TCCR0B,CS02);
}

int main()
{
  DDRD|=(1<<PD6); //LED CONNECTED TO DIGITAL PIN 6 ,and all the
                  //bits of the port is set so as to make it an 
                  //output port
  timer0_init();
  enable_timer();
  Serial.begin(9600);

  //_delay_ms(1000);

  while(1)
  {
    //Serial.println(PORTD);
    _delay_ms(10);

     if(count==62)
    {
      TOGGLE(PORTD,PD6);
      count=0;
    }  
  }
}

ISR(TIMER0_OVF_vect)
{
 count++; 
}
