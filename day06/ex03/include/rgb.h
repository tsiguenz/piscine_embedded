#include <avr/io.h>

#define RGB_BLUE PD3
#define RGB_RED PD5
#define RGB_GREEN PD6

void init_rgb(void);
void set_rgb(uint8_t r, uint8_t g, uint8_t b);
