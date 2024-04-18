// http://www.rjhcoding.com/avrc-uart.php
#include "uart.h"

#define BAUD_RATE 115200

int main(void) {
  uart_init(GET_UBRR(BAUD_RATE));
  while (1)
    uart_tx(uart_rx());
  return 0;
}
