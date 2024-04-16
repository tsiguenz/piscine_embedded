#include <avr/io.h>

int main(void) {
	// set PB1 as output
	DDRB |= (1 << PB1);
	// set mode 14 top is ICR1
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13 | 1 << WGM12);
	// set top value
	ICR1 = F_CPU / 1024;
	// set value to compare, ICR1 / 10
	OCR1A = ICR1 / 10;
	// set switch led when timer is equal to OCR1A
	TCCR1A |= (1 << COM1A1);
	// set timer clock predivider to 1024
	TCCR1B |= (1 << CS12 | 1 << CS10);
	while (1) {}
	return 0;
}
