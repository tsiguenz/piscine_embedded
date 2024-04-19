#include "../include/i2c.h"
#include "../include/uart.h"

void i2c_init(void) {
  // set the clock period
  TWBR = GET_TWBR(SCL_CLOCK);
  // enable i2c
  TWCR = (1 << TWEN);
}

void i2c_start(uint8_t addr) {
  // send start
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  // wait for start condition ack
  while ((TWCR & (1 << TWINT)) == 0) {
  }
  uart_printstr("after send bit start: ");
  uart_printhex(TW_STATUS);
  uart_printnl();
  // check if start is received
  if (TW_STATUS != TW_START)
    return ;
  // set data with address
  TWDR = (addr << 1);
  // sent data
  TWCR = (1 << TWINT) | (1 << TWEN);
  // wait the ack
  while ((TWCR & (1 << TWINT)) == 0) {
  }
  uart_printstr("after send start data: ");
  uart_printhex(TW_STATUS);
  if (TW_STATUS != TW_MT_SLA_ACK)
    return;
}

void i2c_stop(void) {
  // send stop
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}
