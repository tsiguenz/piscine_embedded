#include "../include/eeprom.h"
#include "../include/uart.h"
#include <avr/io.h>

#define BAUD_RATE 115200
#define OFFSET 0

void print_eeprom(uint16_t start, uint16_t max) {
  uart_printstr("0x00:     ");
  for (uint16_t i = start; i < max; i++) {
    uart_printhex(eeprom_read(i));
    uart_printstr("  ");
    if (!((i + 1) % 8) && i + 1 != max) {
      uart_printnl();
      uart_printhex(i + 1);
      uart_printstr(":     ");
    }
  }
}

void clear_eeprom(void) {
  for (uint16_t i = 0; i < EEPROM_MAX_SIZE; i++)
    eeprom_write(i, 0);
}

int main(void) {
  char buffer[42];
  bool ret;
  uart_init(GET_UBRR(BAUD_RATE), UART_WRITE);
  clear_eeprom();
  ret = eepromalloc_write(2, "AAAA", 5);
  uart_printstr("write ret: ");
  uart_printhex(ret);
  uart_printnl();

  ret = eepromalloc_write(2, "AAAA", 5);
  uart_printstr("same write ret: ");
  uart_printhex(ret);
  uart_printnl();

  ret = eepromalloc_read(2, buffer, 5);
  uart_printstr("read ret: ");
  uart_printhex(ret);
  uart_printnl();

  uart_printstr("print buffer: ");
  uart_printstr(buffer);
  uart_printnl();

  ret = eepromalloc_read(42, buffer, 5);
  uart_printstr("read unknown index ret: ");
  uart_printhex(ret);
  uart_printnl();

  ret = eepromalloc_free(2);
  uart_printstr("free ret: ");
  uart_printhex(ret);
  uart_printnl();

  ret = eepromalloc_free(42);
  uart_printstr("free unknown index ret: ");
  uart_printhex(ret);
  uart_printnl();

  ret = eepromalloc_write(2, "BBBB", 5);
  uart_printstr("write ret: ");
  uart_printhex(ret);
  uart_printnl();

  ret = eepromalloc_write(1234, "00000000000000000000", 11);
  uart_printstr("write ret: ");
  uart_printhex(ret);
  uart_printnl();

  ret = eepromalloc_read(1234, buffer, 5);
  uart_printstr("read ret: ");
  uart_printhex(ret);
  uart_printnl();

  uart_printstr("print buffer: ");
  uart_printstr(buffer);
  uart_printnl();

  ret = eepromalloc_read(2, buffer, 5);
  uart_printstr("read ret: ");
  uart_printhex(ret);
  uart_printnl();

  uart_printstr("print buffer: ");
  uart_printstr(buffer);
  uart_printnl();
  print_eeprom(0, 32);
  return 0;
}
