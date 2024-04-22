#include "../include/eeprom.h"
#include "../include/uart.h"

void eeprom_write(uint16_t addr, uint8_t data)
{
  /* Wait for completion of previous write */
  while(EECR & (1 << EEPE)) {}
  /* Set up address and Data Registers */
  EEAR = addr;
  EEDR = data;
  /* Write logical one to EEMPE */
  EECR |= (1 << EEMPE);
  /* Start eeprom write by setting EEPE */
  EECR |= (1 << EEPE);
}

uint8_t eeprom_read(uint16_t addr)
{
  /* Wait for completion of previous write */
  while(EECR & (1 << EEPE)) {}
  /* Set up address register */
  EEAR = addr;
  /* Start eeprom read by writing EERE */
  EECR |= (1 << EERE);
  /* Return data from Data Register */
  return EEDR;
}

// true if size it's ok
static bool _check_size(size_t offset, size_t length) {
  return !((bool)((offset + length + EEPROM_MAGIC_SIZE) >= EEPROM_MAX_SIZE
                  || !length));
}

static bool _check_magic(uint16_t *buffer) {
  return (*buffer == EEPROM_MAGIC);
}

bool safe_eeprom_read(void *buffer, size_t offset, size_t length) {
  eeprom_read_block(buffer, &offset, length);
  uart_printhex(*((unsigned char*)buffer));
  uart_printnl();
  return _check_magic(buffer);
  if (_check_size(offset, length) == false)
    return false;
  eeprom_read_block(buffer, &offset, length + 2);
  //if (buffer[)
  return true;
}

bool safe_eeprom_write(void * buffer, size_t offset, size_t length) {
  if (offset + length >= EEPROM_MAX_SIZE || length == 0)
    return false;
  // eeprom_read_block(, &offset, length);
  eeprom_write_block(buffer, &offset, length);
  return true;
}
