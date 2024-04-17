// https://www.arnabkumardas.com/arduino-tutorial/avr-interrupt-and-external-interrupt/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t toggle_led = 0;

ISR(INT0_vect) {
  toggle_led = 1;
}

int main(void) {
  // set led D1 as output
  DDRB |= (1 << PB0);
  // enable external interrupt
  EIMSK |= (1 << INT0);
  // set interrupt on falling edge
  // EICRA |= (1 << ISC01);
  // enable global interrupt
  sei();
  while (42) {
    if (toggle_led) {
      PORTB ^= (1 << PB0);
      _delay_ms(50);
      toggle_led = 0;
    }
  }
  return 0;
}
