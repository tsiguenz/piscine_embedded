#include <avr/eeprom.h>

uint8_t eeprom_read(uint16_t addr);
void eeprom_write(uint16_t addr, uint8_t data);
