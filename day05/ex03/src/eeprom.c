#include "../include/eeprom.h"
#include "../include/uart.h"
#include <stdlib.h>

static bool _size_is_ok(uint16_t offset, uint16_t length) {
  return !((offset + length) >= EEPROM_MAX_SIZE || !length);
}

static uint16_t _read_uint16(uint16_t offset) {
  return (eeprom_read(offset) << 8) + eeprom_read(offset + 1);
}

static bool _write_uint16(uint16_t offset, uint16_t data) {
  if (!_size_is_ok(offset, 2))
    return EXIT_FAILURE;
  eeprom_write(offset, data >> 8);
  eeprom_write(offset + 1, (uint8_t)data);
  return EXIT_SUCCESS;
}

static bool _magic_is_ok(uint16_t offset) {
  return _read_uint16(offset) == EEPROM_MAGIC;
}

static bool _find_next_magic(uint16_t offset, uint16_t *next_magic) {
  for (uint16_t i = offset + 1; i < EEPROM_MAX_SIZE - 1; i++) {
    if (_magic_is_ok(i)) {
      *next_magic = i;
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}

static uint16_t _get_length(uint16_t offset) {
  return (_read_uint16(offset + EEPROM_LENGTH_OFFSET));
}

static uint16_t _get_data_offset(uint16_t offset) {
  return (offset + EEPROM_DATA_OFFSET);
}

static uint16_t _get_id(uint16_t offset) {
  return (_read_uint16(offset + EEPROM_ID_OFFSET));
}

static bool _find_id(uint16_t id, uint16_t *offset) {
  uint16_t current_offset = 0;
  if (_magic_is_ok(current_offset) && _get_id(current_offset) == id) {
    *offset = current_offset;
    return EXIT_SUCCESS;
  }
  while (!_find_next_magic(current_offset, &current_offset)) {
    if (_get_id(current_offset) == id) {
      *offset = current_offset;
      return EXIT_SUCCESS;
    }
  }
  return EXIT_FAILURE;
}

static bool _id_is_ok(uint16_t id) {
  uint16_t next_magic = 0;
  if (_magic_is_ok(0) && _get_id(0) == id)
    return false;
  while (!_find_next_magic(next_magic, &next_magic)) {
    if (_get_id(next_magic) == id)
      return false;
  }
  return true;
}

static bool _write_magic(uint16_t offset) {
  return _write_uint16(offset, EEPROM_MAGIC);
}

static bool _write_length(uint16_t offset, uint16_t length) {
  return _write_uint16(offset + EEPROM_LENGTH_OFFSET, length);
}

static bool _write_id(uint16_t offset, uint16_t length) {
  return _write_uint16(offset + EEPROM_ID_OFFSET, length);
}

static bool _write_header(uint16_t offset, uint16_t length, uint16_t id) {
  if (!_size_is_ok(offset, GET_CHUNK_SIZE(length)))
    return EXIT_FAILURE;
  _write_magic(offset);
  _write_length(offset, length);
  _write_id(offset, id);
  return EXIT_SUCCESS;
}

static uint16_t _get_offset_end_chunk(uint16_t offset) {
  return offset + GET_CHUNK_SIZE(_get_length(offset));
}

static bool _find_next_empty_chunk(uint16_t length,
                                   uint16_t *next_empty_chunk) {
  uint16_t offset_current_chunk = 0;
  uint16_t offset_next_chunk;
  uint16_t length_current_chunk = 0;
  bool no_chunk_after_current =
      _find_next_magic(offset_current_chunk, &offset_next_chunk);
  if (!_magic_is_ok(offset_current_chunk)) {
    if (no_chunk_after_current) {
      *next_empty_chunk = 0;
      return EXIT_SUCCESS;
    }
    if (offset_next_chunk <= length) {
      *next_empty_chunk = 0;
      return EXIT_SUCCESS;
    }
  }
  do {
    length_current_chunk = GET_CHUNK_SIZE(_get_length(offset_current_chunk));
    if (no_chunk_after_current && (offset_current_chunk + length_current_chunk +
                                   length) < EEPROM_MAX_SIZE) {
      *next_empty_chunk = offset_current_chunk + length_current_chunk + 1;
      return EXIT_SUCCESS;
    }
    if (no_chunk_after_current)
      return EXIT_FAILURE;
    if (offset_next_chunk - _get_offset_end_chunk(offset_current_chunk) >
        length) {
      *next_empty_chunk = offset_current_chunk + length_current_chunk;
      return EXIT_SUCCESS;
    }
    offset_current_chunk = offset_next_chunk;
    no_chunk_after_current =
        _find_next_magic(offset_current_chunk, &offset_next_chunk);
  } while (1);
}

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

bool safe_eeprom_read(void *buffer, uint16_t offset, uint16_t length) {
  uint8_t *ptr = buffer;
  if (_size_is_ok(offset, length + EEPROM_MAGIC_SIZE) == false ||
      _magic_is_ok(offset) == false)
    return EXIT_FAILURE;
  for (uint16_t i = 0; i < length; i++)
    ptr[i] = eeprom_read(offset + EEPROM_MAGIC_SIZE + i);
  return EXIT_SUCCESS;
}

bool safe_eeprom_write(void *buffer, uint16_t offset, uint16_t length) {
  uint8_t tmp = 0;
  uint8_t *ptr = buffer;
  if (_size_is_ok(offset, length + EEPROM_MAGIC_SIZE) == false)
    return EXIT_FAILURE;
  if (_magic_is_ok(offset) == false)
    _write_magic(offset);
  for (uint16_t i = 0; i < length; i++) {
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

bool eepromalloc_write(uint16_t id, void *buffer, uint16_t length) {
  if (!_id_is_ok(id)) {
#ifdef DEBUG
    uart_printstr("id is already taken");
    uart_printnl();
#endif
    return EXIT_FAILURE;
  }
  uint16_t offset;
  if (_find_next_empty_chunk(GET_CHUNK_SIZE(length), &offset)) {
#ifdef DEBUG
    uart_printstr("can't find empty chunck");
    uart_printnl();
#endif
    return EXIT_FAILURE;
  }
  if (_write_header(offset, length, id)) {
#ifdef DEBUG
    uart_printstr("can't write header");
    uart_printnl();
#endif
    return EXIT_FAILURE;
  }
  offset = offset + EEPROM_DATA_OFFSET;
  uint8_t tmp = 0;
  uint8_t *ptr = buffer;
  for (uint16_t i = 0; i < length; i++) {
    tmp = eeprom_read(offset + i);
    if (tmp != ptr[i]) {
#ifdef DEBUG
      uart_printstr("writing\r\n");
#endif
      eeprom_write(offset + i, ptr[i]);
    }
  }
  return EXIT_SUCCESS;
}

bool eepromalloc_read(uint16_t id, void *buffer, uint16_t length) {
  char *ptr = buffer;
  uint16_t offset;
  if (_find_id(id, &offset))
    return EXIT_FAILURE;
  if (_size_is_ok(offset + EEPROM_DATA_OFFSET, length) == false)
    return EXIT_FAILURE;
  uint16_t data_offset = _get_data_offset(offset);
  for (uint16_t i = 0; i < length; i++)
    ptr[i] = eeprom_read(data_offset + i);
  return EXIT_SUCCESS;
}

bool eepromalloc_free(uint16_t id) {
  uint16_t offset;
  if (_find_id(id, &offset))
    return EXIT_FAILURE;
  uint16_t length = GET_CHUNK_SIZE(_get_length(offset));
  uint8_t tmp = 0;
  for (uint16_t i = 0; i < length; i++) {
    tmp = eeprom_read(offset + i);
    if (tmp != 0)
      eeprom_write(offset + i, 0);
  }
  return EXIT_SUCCESS;
}
