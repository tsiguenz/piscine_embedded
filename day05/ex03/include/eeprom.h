#include <avr/eeprom.h>
#include <stdbool.h>

#define EEPROM_MAX_SIZE 1024
#define EEPROM_MAGIC_SIZE 2
#define EEPROM_MAGIC 0xcafe
#define EEPROM_LENGTH_OFFSET 2
#define EEPROM_ID_OFFSET 4
#define EEPROM_DATA_OFFSET 6

#define GET_CHUNK_SIZE(length) length + EEPROM_DATA_OFFSET

uint8_t eeprom_read(uint16_t addr);
void eeprom_write(uint16_t addr, uint8_t data);
bool safe_eeprom_read(void *buffer, uint16_t offset, uint16_t length);
bool safe_eeprom_write(void *buffer, uint16_t offset, uint16_t length);

bool eepromalloc_write(uint16_t id, void *buffer, uint16_t length);
bool eepromalloc_read(uint16_t id, void *buffer, uint16_t length);
bool eepromalloc_free(uint16_t id);
