#include "../include/i2c.h"
#include "../include/uart.h"

#define BAUD_RATE 115200
#define I2C_ADDR 0x42
#define WAIT_SLAVE 0x43
#define LOOSE_STATUS 0x43

int is_master = 0;

// set master and slave
void init(void) {
  i2c_init_slave();
#ifdef DEBUG
  uart_printstr("init\r\n");
#endif
  while (1) {
    // first to press button is master
    if (!(PIND & (1 << PD2))) {
      i2c_init();
      // send general call
      i2c_start(0, I2C_WRITE);
      i2c_stop();
      //       i2c_start(I2C_ADDR, I2C_READ);
      //       if (TWCR & (1 << TWINT)) {
      //         is_master = 1;
      //         i2c_stop();
      //         return;
      //       }
      is_master = 1;
      return;
    }
    // is slave
    if (TWCR & (1 << TWINT)) {
      //       i2c_write(1);
      return;
    }
  }
}

void run_game(void) {
#ifdef DEBUG
  uart_printstr("run game\r\n");
#endif
  // TODO: set timer with random value between 2 and 10
  int timer = 3;
  PORTB |= (1 << PB0);
  _delay_ms(timer * 1000);
  PORTB &= ~(1 << PB0);
  while (1) {
    if (!(PIND & (1 << PD2))) {
      // if (is_master) {
      // }
      uart_printstr("button is pressed");
      // uart_printstr("I'm the winner");
#ifdef DEBUG
      uart_printstr("end game\r\n");
#endif
      return;
    }
    if (TWDR == LOOSE_STATUS) {
#ifdef DEBUG
      uart_printstr("get signal\r\n");
#endif
      //       uart_printstr("I'm the looser");
      //       return;
    }
  }
}

void master_send_data(void) {
  i2c_start(0x42, I2C_READ);
  i2c_read(ACK);
  uart_printhex(TWDR);
  i2c_stop();
}

void slave_read_data(void) {
  while (TWSR == TW_ST_SLA_ACK)
    ;
  TWDR = 42;
  TWSR = (1 << TWINT);
  // uart_printhex(i2c_read(ACK));
  // uart_printhex(i2c_read(NACK));
}

int main(void) {
  // init led PB0 as output
  DDRB &= ~(1 << PB0);
  // init button SW1 as input
  DDRD &= ~(1 << PD2);
  uart_init(GET_UBRR(BAUD_RATE), UART_WRITE);
  init();
  if (is_master) {
    uart_printstr("I'm master\r\n");
  } else {
    uart_printstr("I'm slave\r\n");
  }
  if (is_master)
    master_send_data();
  else
    slave_read_data();
  // run_game();
  return 0;
}
