# Piscine Embedded

## Intro

This project is about learn the basics of embedded, we use a custom chipset  
made by the association [42chips](https://www.42chips.fr/). You can find the
schema of the chipset [here](assets/schema.pdf) and the documentation about the
atmega328p [here](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)

## Day00 Discover input and outputs

- ex00: write a basic makefile
- ex01: turn on a led
- ex02: turn on a led when button is pressed
- ex03: toggle led state when button is pressed (welcome to bounce effect)
- ex04: create a binary counter with 4 leds and 2 buttons (increase and decrease)

## Day01 Timers

- ex00: toggle led state every 500ms without delay function
- ex01: same as above but with timer (while loop need to be empty)
- ex02: turn on led with a duty cycle of 10% and 1hz frequence
- ex03: same as above but we can change the duty cycle with buttons

## Day02 Interrupt

- ex00: toggle led state with button interruption
- ex01: configure Timer0 to trigger a periodic interrupt that varies the
duty cycle of the LED PB1 controlled by Timer1

## Day03 UART

- ex00: write function to print a char on serial port
- ex01: write function to print a string on serial port
- ex02: write function to read and print a char on serial port
- ex03: same as ex02 but switch case and only use interrupt

## Day04 I2C

- ex00: create functions to initialize i2c communication
- ex01: print raw data from AHT20 temperature and humidity sensor
- ex02: print temperature in Celsius and humidity percentage

## Day05 EEPROM

- ex00: use eeprom to save and restore state of a counter increased by SW1
- ex01: same as above but we now have 4 counter and we can switch with SW2
- ex02: create functions to safe write in eeprom. Use magic number to recognize
our datas and don't rewrite the same data multiple times.
- ex03: create functions to allocate, read and free datas like a dictionnary

## Day05 RGB

- ex00: change RGB LED D5 color to red, green and blue with 1s delay
- ex01: add yellow, cyan, magenta and white
- ex02: display color wheel with the `wheel` function given
- ex03: read color on serial port and change the led color with it (format is: #RRGGBB)
