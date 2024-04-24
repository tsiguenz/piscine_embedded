#include "../include/rgb.h"
#include "../include/uart.h"
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <util/delay.h>

#define BAUD_RATE 115200

volatile char buffer[8] = {0};
volatile uint8_t i = 0;

bool set_rgb_from_buffer(void) {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  unsigned char c = 0;
  for (size_t j = 0; j < 7; j++) {
    c = buffer[j];
    if (j == 0) {
      if (c == '#')
        continue;
      return EXIT_FAILURE;
    }
    if (c >= 'A' && c <= 'F')
      c = c - 'A' + 10;
    else if (c >= 'a' && c <= 'f')
      c = c - 'a' + 10;
    else if (c >= '0' && c <= '9')
      c = c - '0';
    else
      return EXIT_FAILURE;
    switch (j) {
    case 1:
      r += c << 4;
      break;
    case 2:
      r += c;
      break;
    case 3:
      g += c << 4;
      break;
    case 4:
      g += c;
      break;
    case 5:
      b += c << 4;
      break;
    case 6:
      b += c;
      break;
    }
  }
  set_rgb(r, g, b);
  return EXIT_SUCCESS;
}

ISR(USART_RX_vect) {
  char c = UDR0;
  if (c == '\r') {
    if (set_rgb_from_buffer())
      uart_printstr("\r\nError color not recognized.");
    i = 0;
    for (size_t j = 0; j < 7; j++)
      buffer[j] = 0;
    uart_printnl();
    return;
  }
  if (i >= 8)
    return;
  uart_tx(c);
  buffer[i] = c;
  ++i;
}

int main(void) {
  UCSR0B |= (1 << RXCIE0);
  init_rgb();
  uart_init(GET_UBRR(BAUD_RATE), UART_ALL);
  sei();
  while (1) {
  }
  return 0;
}
