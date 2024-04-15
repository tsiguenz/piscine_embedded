#include <avr/io.h>

int main(void) {
  // set PB0 as output
  DDRB |= (1 << PB0);
  // turn on the light on PB0
  PORTB |= (1 << PB0);
  return 0;
}
