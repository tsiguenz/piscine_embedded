#include "../include/i2c.h"
#include "../include/uart.h"
#include "../include/aht20.h"

#define BAUD_RATE 115200

int main(void) {
  uart_init(GET_UBRR(BAUD_RATE), UART_WRITE);
  i2c_init();
  aht20_init();
  while (1) {
    _delay_ms(1000);
    aht20_mesure();
    uart_printnl();
  }
  i2c_stop();
  return 0;
}
