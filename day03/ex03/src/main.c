// http://www.rjhcoding.com/avrc-uart.php
#include "uart.h"

#define BAUD_RATE 115200

ISR(USART_RX_vect) {
  char c = UDR0;
  int switch_case = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  (switch_case) ? uart_tx(c ^ (1 << 5)) : uart_tx(c);
}

int main(void) {
  UCSR0B |= (1 << RXCIE0);
  sei();
  uart_init(GET_UBRR(BAUD_RATE));
  while (1) {
  }
  return 0;
}
