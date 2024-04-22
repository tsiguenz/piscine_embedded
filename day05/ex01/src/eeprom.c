#include "../include/eeprom.h"

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
