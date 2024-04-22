#include "../include/eeprom.h"
#include "../include/uart.h"
#include <avr/io.h>

#define BAUD_RATE 115200
#define OFFSET 1009

int main(void) {
  char buffer[42] = {0};
  uart_init(GET_UBRR(BAUD_RATE), UART_WRITE);
  uart_printstr("safe_eeprom_write()");
  uart_printnl();
  uart_printhex(safe_eeprom_write("hello world", OFFSET, 12));
  uart_printnl();
  uart_printstr("safe_eeprom_read()");
  uart_printnl();
  uart_printhex(safe_eeprom_read(buffer, OFFSET, 12));
  uart_printnl();
  uart_printstr(buffer);
  return 0;
}
