#include <avr/eeprom.h>
#include <stdbool.h>

#define EEPROM_MAX_SIZE 1024
#define EEPROM_MAGIC_SIZE 2
#define EEPROM_MAGIC 0xcafe

uint8_t eeprom_read(uint16_t addr);
void eeprom_write(uint16_t addr, uint8_t data);
bool safe_eeprom_read(void *buffer, size_t offset, size_t length);
bool safe_eeprom_write(void *buffer, size_t offset, size_t length);
