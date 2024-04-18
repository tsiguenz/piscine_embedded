// http://www.rjhcoding.com/avrc-uart.php
#include "uart.h"

#define BAUD_RATE 115200

int main(void) {
  uint16_t ubrr = (float) ((F_CPU / (16.0 * BAUD_RATE)) + 0.5) - 1;
  uart_init(ubrr);
  while (1) {
    uart_tx('Z');
    _delay_ms(1000);
  }
  return 0;
}
