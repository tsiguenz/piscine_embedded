#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define GET_UBRR(BAUD_RATE) (float)((F_CPU / (16.0 * BAUD_RATE)) + 0.5) - 1

void uart_init(uint16_t ubrr);
void uart_tx(char c);
void uart_printstr(const char *str);
