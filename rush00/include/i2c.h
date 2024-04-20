#include <util/twi.h>

#define SCL_CLOCK 100000L
#define GET_TWBR(scl_clock) ((F_CPU / scl_clock) - 16) / 2
#define I2C_WRITE 0
#define I2C_READ 1
#define ACK 1
#define NACK 0

#define DEBUG

void i2c_init(void);
void i2c_init_slave(void);
void i2c_start(uint8_t addr, uint8_t is_read);
void i2c_stop(void);
void i2c_write(unsigned char data);
uint8_t i2c_read(uint8_t ack);
uint8_t i2c_read_non_block(uint8_t ack);
