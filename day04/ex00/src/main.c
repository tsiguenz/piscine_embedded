#include "../include/i2c.h"
#include "../include/uart.h"

#define BAUD_RATE 115200

int main(void) {
  uart_init(GET_UBRR(BAUD_RATE), UART_WRITE);
  i2c_init();
  i2c_start(0x34);
  i2c_stop();
  return 0;
}
