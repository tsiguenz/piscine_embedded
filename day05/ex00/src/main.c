#include "../include/eeprom.h"
#include <avr/io.h>

#define EEPROM_ADDR 0

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
  unsigned char number = eeprom_read(EEPROM_ADDR);
  activate_leds(number);
  // set PB0 as output
  DDRB |= (1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
  // set PD2 as input
  DDRD &= ~(1 << PD2);
  // get PD2 value
  while (42) {
    if (!(PIND & (1 << PD2))) {
      debounce(&PIND, PD2);
      // if PD2 is press
      number++;
      // light off all the leds
      PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
      activate_leds(number);
      eeprom_write(EEPROM_ADDR, number);
    }
  }
  return 0;
}
