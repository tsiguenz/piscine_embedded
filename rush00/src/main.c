#include "../include/i2c.h"
#include "../include/uart.h"

#define BAUD_RATE 115200
#define I2C_ADDR 0x42

int is_master = 0;

// set master and slave
void init(void) {
  i2c_init_slave();
#ifdef DEBUG
  uart_printstr("init\r\n");
#endif
  TWAR = (I2C_ADDR << 1);
  while (1) {
    // first to press button is master
    if (!(PIND & (1 << PD2))) {
      // send general call
      i2c_start(0, I2C_WRITE);
      // send data to everyone
      i2c_write(1);
      i2c_stop();
      i2c_start(I2C_ADDR, I2C_READ);
      if (TWCR & (1 << TWINT)) {
        is_master = 1;
        return;
      }
    }
    // is slave
    if (TWCR & (1 << TWINT)) {
      return;
    }
  }
}

int main(void) {
  // init button SW1 as input
  DDRD &= ~(1 << PD2);
  uart_init(GET_UBRR(BAUD_RATE), UART_WRITE);
  // set PD2 as input
  i2c_init();
  init();
  if (is_master) {
    uart_printstr("I'm master\r\n");
  } else {
    uart_printstr("I'm slave\r\n");
  }
  return 0;
}
