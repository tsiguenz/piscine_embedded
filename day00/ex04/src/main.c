#include <avr/io.h>
#include <util/delay.h>

void activate_leds(int number) {
      if (number & 1)
        PORTB |= (1 << PB0);
      if (number & 2)
        PORTB |= (1 << PB1);
      if (number & 4)
        PORTB |= (1 << PB2);
      if (number & 8)
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
    // check if PD2 is press
    if (!(PIND & (1 << PD2))) {
      number++;
      PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
      activate_leds(number);
      while (!(PIND & (1 << PD2)))
        _delay_ms(50);
    } else if (!(PIND & (1 << PD4))) {
      number--;
      PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
      activate_leds(number);
      while (!(PIND & (1 << PD4)))
        _delay_ms(50);
    }
    number %= 16;
    _delay_ms(50);
  }
  return 0;
}
