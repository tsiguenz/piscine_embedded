#include "../include/uart.h"

void uart_init(uint16_t ubrr, uint8_t mode) {
  // enable the transmitter
  switch (mode) {
  case UART_READ:
    UCSR0B |= (1 << RXEN0);
    break;
  case UART_WRITE:
    UCSR0B |= (1 << TXEN0);
    break;
  case UART_ALL:
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
    break;
  }
  // setting the baud rate
  UBRR0L = (uint8_t)(ubrr & 0xFF);
  UBRR0H = (uint8_t)(ubrr >> 8);
}

void uart_tx(char c) {
  // wait for transmit buffer to be empty
  while (!(UCSR0A & (1 << UDRE0))) {
  }
  // load data into transmit register
  UDR0 = c;
}

char uart_rx(void) {
  // wait for received buffer to be empty
  while (!(UCSR0A & (1 << RXC0))) {
  }
  // return data
  return UDR0;
}

void uart_printstr(const char *str) {
  for (int i = 0; str[i]; i++)
    uart_tx(str[i]);
}

void uart_printnl(void) { uart_printstr("\r\n"); }

void uart_printbin(uint8_t n) {
  uart_printstr("0b");
  for (uint8_t i = 0; i < 8; ++i)
    uart_tx((n & (1 << (7 - i))) ? '1' : '0');
}

void uart_printhex(uint8_t n) {
  uart_printstr("0x");
  char c = n >> 4;
  uart_tx(c < 10 ? c + '0' : c - 10 + 'A');
  c = n & 0x0F;
  uart_tx(c < 10 ? c + '0' : c - 10 + 'A');
}
