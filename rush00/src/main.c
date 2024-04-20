// https://files.seeedstudio.com/wiki/Grove-AHT20_I2C_Industrial_Grade_Temperature_and_Humidity_Sensor/AHT20-datasheet-2020-4-16.pdf
#include "../include/aht20.h"
#include "../include/i2c.h"
#include "../include/uart.h"
#include <stdlib.h>

#define BAUD_RATE 115200

int main(void) {
  uart_init(GET_UBRR(BAUD_RATE), UART_WRITE);
  i2c_init();
  aht20_init();
  float humidity = 0, temperature = 0;
  char str[10] = {0};
  while (1) {
    _delay_ms(300);
    aht20_mesure(&humidity, &temperature);
    uart_printstr("Temperature: ");
    dtostrf(temperature, 0, 1, str);
    uart_printstr(str);
    uart_printstr("°C, ");
    uart_printstr("Humidity: ");
    dtostrf(humidity, 0, 0, str);
    uart_printstr(str);
    uart_printstr("%");
    uart_printnl();
  }
  i2c_stop();
  return 0;
}
