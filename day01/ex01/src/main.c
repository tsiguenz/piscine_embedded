// https://lab-allen.fr/atmega328-configuration-du-timer1/
#include <avr/io.h>

int main(void) {
  // set PB1 as output
  DDRB |= (1 << PB1);
  // set top to OCR1A
  TCCR1A |= (1 << WGM11 | 1 << WGM10);
  TCCR1B |= (1 << WGM13 | 1 << WGM12);
  // set top value
  OCR1A = (F_CPU / 1024) / 2;
  // set switch led when timer is equal to OCR1A
  TCCR1A |= (1 << COM1A0);
  // set timer clock predivider to 1024
  TCCR1B |= (1 << CS12 | 1 << CS10);
  while (1) {}
  return 0;
}
