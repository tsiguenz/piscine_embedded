#include "../include/eeprom.h"
#include "../include/uart.h"
#include <stdlib.h>

void eeprom_write(uint16_t addr, uint8_t data) {
  /* Wait for completion of previous write */
  while (EECR & (1 << EEPE)) {
  }
  /* Set up address and Data Registers */
  EEAR = addr;
  EEDR = data;
  /* Write logical one to EEMPE */
  EECR |= (1 << EEMPE);
  /* Start eeprom write by setting EEPE */
  EECR |= (1 << EEPE);
}

uint8_t eeprom_read(uint16_t addr) {
  /* Wait for completion of previous write */
  while (EECR & (1 << EEPE)) {
  }
  /* Set up address register */
  EEAR = addr;
  /* Start eeprom read by writing EERE */
  EECR |= (1 << EERE);
  /* Return data from Data Register */
  return EEDR;
}

// true if size it's ok
static bool _check_size(size_t offset, size_t length) {
  return !((bool)((offset + length + EEPROM_MAGIC_SIZE) >= EEPROM_MAX_SIZE ||
                  !length));
}

// true if magic is ok
static bool _check_magic(size_t offset) {
  uint16_t magic = (eeprom_read(offset) << 8) + eeprom_read(offset + 1);
  return magic == EEPROM_MAGIC;
}

static void _write_magic(size_t offset) {
  eeprom_write(offset, EEPROM_MAGIC >> 8);
  eeprom_write(offset + 1, (uint8_t)EEPROM_MAGIC);
}

bool safe_eeprom_read(void *buffer, size_t offset, size_t length) {
  uint8_t *ptr = buffer;
  if (_check_size(offset, length) == false || _check_magic(offset) == false)
    return EXIT_FAILURE;
  for (size_t i = 0; i < length; i++)
    ptr[i] = eeprom_read(offset + EEPROM_MAGIC_SIZE + i);
  return EXIT_SUCCESS;
}

// #define DEBUG

bool safe_eeprom_write(void *buffer, size_t offset, size_t length) {
  uint8_t tmp = 0;
  uint8_t *ptr = buffer;
  if (_check_size(offset, length) == false)
    return EXIT_FAILURE;
  if (_check_magic(offset) == false)
    _write_magic(offset);
  for (size_t i = 0; i < length; i++) {
    tmp = eeprom_read(offset + EEPROM_MAGIC_SIZE + i);
    if (tmp != ptr[i]) {
#ifdef DEBUG
      uart_printstr("writing\r\n");
#endif
      eeprom_write(offset + EEPROM_MAGIC_SIZE + i, ptr[i]);
    }
  }
  return EXIT_SUCCESS;
}
