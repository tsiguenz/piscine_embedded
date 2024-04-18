#include "../include/uart.h"

void uart_init(uint16_t ubrr) {
  // enable the transmitter
  UCSR0B |= (1 << TXEN0);
  // setting the baud rate
  UBRR0L = (uint8_t)(ubrr & 0xFF);
  UBRR0H = (uint8_t)(ubrr >> 8);
}

void uart_tx(char c) {
  // wait for transmit buffer to be empty
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  // load data into transmit register
  UDR0 = c;
}
