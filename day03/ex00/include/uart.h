#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void uart_init(uint16_t ubrr);
void uart_tx(char c);
