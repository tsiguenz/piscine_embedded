#include <avr/io.h>
#include <util/delay.h>

#define RGB_BLUE PD3
#define RGB_RED PD5
#define RGB_GREEN PD6

int main(void) {
  // set rgb as output
  DDRD |= _BV(RGB_RED) | _BV(RGB_GREEN) | _BV(RGB_BLUE);
  while (1) {
    PORTD = _BV(RGB_RED);
    _delay_ms(1000);
    PORTD = _BV(RGB_GREEN);
    _delay_ms(1000);
    PORTD = _BV(RGB_BLUE);
    _delay_ms(1000);
  }
  return 0;
}
