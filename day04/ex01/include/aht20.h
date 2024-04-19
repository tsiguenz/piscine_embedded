#include "../include/i2c.h"
#include "../include/uart.h"

#define AHT20_ADDR 0x38
#define AHT20_STATUS 0x71
#define AHT20_CALIBRATE 0xBE
#define AHT20_MESURE 0xAC

void  aht20_init(void);
void  aht20_mesure(void);

