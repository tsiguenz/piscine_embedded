#include <avr/io.h>
#include <util/delay.h>

#define GET_UBRR(BAUD_RATE) (float)((F_CPU / (16.0 * BAUD_RATE)) + 0.5) - 1
#define UART_READ 0
#define UART_WRITE 1
#define UART_ALL 2

void uart_init(uint16_t ubrr, uint8_t mode);
void uart_tx(char c);
void uart_printstr(const char *str);
char uart_rx(void);
void uart_printnl(void);
void uart_printbin(uint8_t n);
void uart_printhex(uint8_t n);
