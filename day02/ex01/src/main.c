// https://lab-allen.fr/atmega328-configuration-du-timer0/
// https://www.arnabkumardas.com/arduino-tutorial/avr-interrupt-and-external-interrupt/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t duty = 0;
volatile uint8_t go_top = 1;

ISR(TIMER0_OVF_vect) {
  if (duty == 100)
    go_top = 0;
  else if (duty == 0)
    go_top = 1;
  (go_top)? duty++ : duty--;
  OCR1A = duty;
}

int main(void) {
	// set PB1 as output
  DDRB |= (1 << PB1);
  // TIMER 0 who manage duty cycle
  // set mode 7 (top is OCRA)
  TCCR0A |= (1 << WGM00) | (1 << WGM01);
  TCCR0B |= (1 << WGM02);
  // set for 200 times per seconds
  OCR0A = F_CPU / 1024 / 200;
  // set timer0 prescaler to 1024
  TCCR0B |= (1 << CS02) | (1 << CS00);
  // set mode to overflow interupt
  TIMSK0 |= (1 << TOIE0);

  // TIMER 1 to turn on and off the led
  // set mode 14 top is ICR1
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM13 | 1 << WGM12);
  // set top value
  ICR1 = 100;
  // set switch led when timer is equal to OCR1A or ICR1
  TCCR1A |= (1 << COM1A1);
  // set prescaler
  TCCR1B |= (1 << CS10);
  sei();
  while (1) {}
	return 0;
}
