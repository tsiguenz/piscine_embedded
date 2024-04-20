#include "../include/i2c.h"
#include "../include/uart.h"

void i2c_init(void) {
  // set the clock period
  TWBR = GET_TWBR(SCL_CLOCK);
  // enable i2c
  TWCR = (1 << TWEN);
}

void i2c_init_slave(void) {
  // set the clock period
  TWBR = GET_TWBR(SCL_CLOCK);
  // enable i2c
  TWCR = (1 << TWEN) | (1 << TWEA);
}

void i2c_start(uint8_t addr, uint8_t is_read) {
  // send start
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  // wait for start condition ack
  while (!(TWCR & (1 << TWINT))) {
  }
  // check if start is received
  if (TW_STATUS != TW_START)
    return;
  // set data with address
  TWDR = (addr << 1) | is_read;
  // sent data
  TWCR = (1 << TWINT) | (1 << TWEN);
  // wait the ack
  while (!(TWCR & (1 << TWINT))) {
#ifdef DEBUG
    uart_printstr("start\r\n");
#endif
  }
  if (TW_STATUS != TW_MT_SLA_ACK && TW_STATUS != TW_MR_SLA_ACK)
    return;
}

void i2c_stop(void) {
  // send stop
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
  TWCR &= ~(1 << TWEN);
}

void i2c_write(unsigned char data) {
  // prepare data
  TWDR = data;
  // sent data
  TWCR = (1 << TWINT) | (1 << TWEN);
  // wait ack
  while ((TWCR & (1 << TWINT)) == 0) {
#ifdef DEBUG
    uart_printstr("write\r\n");
#endif
  }
}

uint8_t i2c_read(uint8_t ack) {
  // sent receive is ready
  TWCR = (1 << TWINT) | (1 << TWEN) | ((ack) ? (1 << TWEA) : 0);
  // wait ack
  while (!(TWCR & (1 << TWINT))) {
#ifdef DEBUG
    uart_printstr("read\r\n");
#endif
  }
  return TWDR;
}
