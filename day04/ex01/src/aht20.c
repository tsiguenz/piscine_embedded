#include "../include/aht20.h"

void  aht20_init(void) {
  _delay_ms(100);
  i2c_start(AHT20_ADDR, I2C_WRITE);
  // send check for calibration
  i2c_write(AHT20_STATUS);
  i2c_stop();
  i2c_start(AHT20_ADDR, I2C_READ);
  uart_printstr("Check status: ");
  i2c_read(NACK);
  uart_printnl();
  i2c_stop();
  // check if calibration bit is on
  if (!(TWDR & (1 << 3))) {
    uart_printstr("Do calibration...");
    uart_printnl();
    // calibrate
    i2c_start(AHT20_ADDR, I2C_WRITE);
    i2c_write(AHT20_CALIBRATE);
    i2c_write(0x08);
    i2c_write(0x00);
    i2c_stop();
    _delay_ms(10);
  }
}

void  aht20_mesure(void) {
  i2c_start(AHT20_ADDR, I2C_WRITE);
  i2c_write(AHT20_MESURE);
  i2c_write(0x33);
  i2c_write(0x00);
  i2c_stop();
  _delay_ms(100);
  i2c_start(AHT20_ADDR, I2C_READ);
  i2c_read(ACK);
  if (!(TWDR & (1 << 7))) {
    i2c_read(ACK);
    i2c_read(ACK);
    i2c_read(ACK);
    i2c_read(ACK);
    i2c_read(ACK);
    i2c_read(NACK);
  }
  i2c_stop();
}
