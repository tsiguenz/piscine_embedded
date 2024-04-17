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
