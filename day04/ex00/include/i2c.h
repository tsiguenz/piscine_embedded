#include <util/twi.h>

#define SCL_CLOCK 100000L
#define GET_TWBR(scl_clock) ((F_CPU / scl_clock) - 16) / 2

void i2c_init(void);
void i2c_start(uint8_t addr);
void i2c_stop(void);
