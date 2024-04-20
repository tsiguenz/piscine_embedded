#include "../include/aht20.h"

void aht20_init(void) {
  _delay_ms(40);
  i2c_start(AHT20_ADDR, I2C_WRITE);
  // send check for calibration
  i2c_write(AHT20_STATUS);
  i2c_stop();
  i2c_start(AHT20_ADDR, I2C_READ);
  uint8_t data = i2c_read(NACK);
  i2c_stop();
  // check if calibration bit is on
  if (!(data & (1 << 3))) {
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

void aht20_mesure(float *humidity, float *temperature) {
  *humidity = 0;
  *temperature = 0;
  // loop for accuracy
  for (int i = 0; i < 3; i++) {
    unsigned char bytes[6] = {0};
    i2c_start(AHT20_ADDR, I2C_WRITE);
    i2c_write(AHT20_MESURE);
    i2c_write(0x33);
    i2c_write(0x00);
    i2c_stop();
    _delay_ms(100);
    i2c_start(AHT20_ADDR, I2C_READ);
    i2c_read(ACK);
    if (!(TWDR & (1 << 7)))
      for (int i = 0; i < 6; i++)
        bytes[i] = i2c_read(ACK);
    i2c_stop();
    uint32_t _h = 0, _t = 0;
    // calculate humidity
    _h = bytes[0];
    _h <<= 8;
    _h += bytes[1];
    _h <<= 4;
    _h += bytes[2] >> 4;
    *humidity += (float)(_h / 1048576.0) * 100;
    // calculate temperature
    _t = bytes[2] & 0x0f;
    _t <<= 8;
    _t += bytes[3];
    _t <<= 8;
    _t += bytes[4];
    *temperature += (float)(_t / 1048576.0) * 200.0 - 50.0;
  }
  *humidity /= 3;
  *temperature /= 3;
}
