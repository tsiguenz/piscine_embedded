#include <avr/io.h>
#include <util/delay.h>

void activate_leds(int number) {
  if (number & (1 << 0))
    PORTB |= (1 << PB0);
  if (number & (1 << 1))
    PORTB |= (1 << PB1);
  if (number & (1 << 2))
    PORTB |= (1 << PB2);
  if (number & (1 << 3))
    PORTB |= (1 << PB4);
}

int main(void) {
  unsigned char number = 0;
  // set PB0 as output
  DDRB |= (1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
  // set PD2 as input
  DDRD &= ~(1 << PD2 | 1 << PD4);
  // get PD2 value
  while (42) {
    if (!(PIND & (1 << PD2))) {
      // if PD2 is press
      number++;
      // light off all the leds
      PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
      activate_leds(number);
      // avoid bounce
      while (!(PIND & (1 << PD2)))
        _delay_ms(50);
    } else if (!(PIND & (1 << PD4))) {
      // if PD4 is press
      number--;
      // light off all the leds
      PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
      activate_leds(number);
      // avoid bounce
      while (!(PIND & (1 << PD4)))
        _delay_ms(50);
    }
    _delay_ms(50);
  }
  return 0;
}
