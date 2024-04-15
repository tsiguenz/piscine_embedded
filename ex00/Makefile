F_CPU=16000000UL
NAME=main
CC=avr-gcc
SRC_PATH = src/
OBJ_PATH = obj/
INC = -Iinc
SRC=$(addsuffix .c, $(NAME))
HEX=$(addsuffix .hex, $(NAME))
BIN=$(addsuffix .bin, $(NAME))
BAUD_RATE=115200
PORT=/dev/ttyUSB0

all: hex flash

hex:
	$(CC) $(SRC) -o $(BIN) -mmcu=atmega328 -DF_CPU=$(F_CPU)
	avr-objcopy $(BIN) -O ihex $(HEX)

flash:
	avrdude -b $(BAUD_RATE) -c arduino -p m328p -P $(PORT) -e -U flash:w:$(HEX)

clean:
	rm -rf $(HEX) $(BIN)

.PHONY: all hex flash clean
