#include <avr/io.h>

int main(void) {
  // set PB0 as output
  DDRB |= (1 << PB1);
  while (42) {
    // wait 500ms 
    for (uint64_t i = 0; i < 130000; i++) {}
    // switch the light on PB0
    PORTB ^= (1 << PB1);
  }
  return 0;
}
