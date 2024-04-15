#include <avr/io.h>

int main(void) {
  // set PB0 as output
  DDRB |= (1 << PB0);
  // set PD2 as input
  DDRD &= ~(1 << PD2);
  // get PD2 value
  while (42) {
    // check if PD2 is press
    if (!(PIND & (1 << PD2))) {
      // turn on the light on PB0
      PORTB |= (1 << PB0);
    } else {
      // turn off the light on PB0
      PORTB &= ~(1 << PB0);
    }
  }
  return 0;
}
