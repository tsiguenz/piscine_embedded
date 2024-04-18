// http://www.rjhcoding.com/avrc-uart.php
#include "uart.h"

#define BAUD_RATE 115200

volatile uint8_t nb_interrupt = 0;

ISR(TIMER0_OVF_vect) {
  nb_interrupt += 1;
  if (nb_interrupt >= 200) {
    uart_printstr("Hello World!\r\n");
    nb_interrupt = 0;
  }
}

int main(void) {
  // TIMER 0
  // set mode 7 (top is OCRA)
  TCCR0A |= (1 << WGM00) | (1 << WGM01);
  TCCR0B |= (1 << WGM02);
  // set for 100 times per seconds
  OCR0A = F_CPU / 1024 / 100;
  // set timer0 prescaler to 1024
  TCCR0B |= (1 << CS02) | (1 << CS00);
  // set mode to overflow interupt
  TIMSK0 |= (1 << TOIE0);
  sei();
  uart_init(GET_UBRR(BAUD_RATE));
  while (1) { }
  return 0;
}
