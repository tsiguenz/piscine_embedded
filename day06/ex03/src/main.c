#include "../include/rgb.h"
#include "../include/uart.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#define BAUD_RATE 115200

volatile char buffer[8] = {0};
volatile uint8_t i = 0;

#define FATAL(str)

ISR(USART_RX_vect) {
  char c = UDR0;
  uart_tx(c);
  switch (i) {
  case 0:
    if (c != '#')
      return;
  }
  if (i == 0 && c == '#')
    buffer[i] = c;
}

int main(void) {
  UCSR0B |= (1 << RXCIE0);
  init_rgb();
  uart_init(GET_UBRR(BAUD_RATE), UART_ALL);
  sei();
  while (1) {
    set_rgb(255, 255, 0);
    _delay_ms(10);
  }
  return 0;
}
