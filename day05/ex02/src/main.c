#include "../include/eeprom.h"
#include "../include/uart.h"
#include <avr/io.h>

#define EEPROM_INDEX_ADDR 0
#define EEPROM_CTN_ADDR 1
#define NB_REGISTERS 4
#define BAUD_RATE 115200

void activate_leds(int number) {
  if (number & (1 << 0))
    PORTB |= (1 << PB0);
  if (number & (1 << 1))
    PORTB |= (1 << PB1);
  if (number & (1 << 2))
    PORTB |= (1 << PB2);
  if (number & (1 << 3))
    PORTB |= (1 << PB4);
}

void debounce(volatile uint8_t *reg, uint8_t pos) {
  for (uint32_t i = 0; i < F_CPU / 12 / 8; ++i) {
  }
  while ((*reg & (1 << pos)) == 0) {
  }
  for (uint32_t i = 0; i < F_CPU / 12 / 8; ++i) {
  }
}

int main(void) {
  char buffer[42] = {0};
  uart_init(GET_UBRR(BAUD_RATE), UART_WRITE);
  eeprom_write(0, 0xca);
  eeprom_write(1, 0xfe);
  uart_printstr("crash");
  uart_printnl();
  uart_printhex(safe_eeprom_read(buffer, 0, 2));
  uart_printstr("alooo");
  // // set PB0 as output
  // DDRB |= (1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
  // // set PD2 as input
  // DDRD &= ~(1 << PD2 | 1 << PD4);
  // uint8_t index_ctn = eeprom_read(EEPROM_INDEX_ADDR);
  // if (index_ctn > 4)
  //   index_ctn = 1;
  // uint8_t ctn = eeprom_read(EEPROM_CTN_ADDR + index_ctn);
  // activate_leds(ctn);
  // while (42) {
  //   // get PD2 value
  //   if (!(PIND & (1 << PD2))) {
  //     debounce(&PIND, PD2);
  //     // if PD2 is press
  //     ctn++;
  //     // light off all the leds
  //     PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
  //     activate_leds(ctn);
  //     eeprom_write(EEPROM_CTN_ADDR + index_ctn, ctn);
  //     // get PD4 value
  //   } else if (!(PIND & (1 << PD4))) {
  //     debounce(&PIND, PD4);
  //     index_ctn++;
  //     if (index_ctn > 4)
  //       index_ctn = 1;
  //     ctn = eeprom_read(EEPROM_CTN_ADDR + index_ctn);
  //     eeprom_write(EEPROM_INDEX_ADDR, index_ctn);
  //     // light off all the leds
  //     PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
  //     activate_leds(ctn);
  //   }
  // }
  return 0;
}
