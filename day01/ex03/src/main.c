#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	char cycle = 5;
	// set buttons as input
	DDRD &= ~(1 << PD2 | 1 << PD4);
	// set PB1 as output
	DDRB |= (1 << PB1);
	// set mode 14 top is ICR1
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM13 | 1 << WGM12);
	// set top value
	ICR1 = F_CPU / 1024;
	// set switch led when timer is equal to OCR1A or ICR1
	TCCR1A |= (1 << COM1A1);
	// set timer clock predivider to 1024
	TCCR1B |= (1 << CS12 | 1 << CS10);
	while (1) {
		// set value cycle percent of ICR1
		OCR1A = (ICR1 / 10) * cycle;
		// when button1 is pressed
		if (!(PIND & (1 << PD2))) {
			if (cycle < 10)
				cycle += 1;
			while (!(PIND & (1 << PD2)))
				_delay_ms(50);
		}
		// when button2 is pressed
		else if (!(PIND & (1 << PD4)) && cycle > 1) {
			if (cycle > 1)
				cycle -= 1;
			while (!(PIND & (1 << PD2)))
				_delay_ms(50);
		}
		_delay_ms(50);
	}
	return 0;
}
