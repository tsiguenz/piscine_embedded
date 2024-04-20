// https://files.seeedstudio.com/wiki/Grove-AHT20_I2C_Industrial_Grade_Temperature_and_Humidity_Sensor/AHT20-datasheet-2020-4-16.pdf
#include "../include/i2c.h"
#include "../include/uart.h"
#include "../include/aht20.h"

#define BAUD_RATE 115200

int main(void) {
  uart_init(GET_UBRR(BAUD_RATE), UART_WRITE);
  i2c_init();
  aht20_init();
  while (1) {
    _delay_ms(500);
    aht20_mesure();
    uart_printnl();
  }
  i2c_stop();
  return 0;
}
