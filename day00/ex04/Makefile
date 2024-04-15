HEX = main.hex
F_CPU= 16000000UL
CC = avr-gcc
BAUD_RATE = 115200
PORT = /dev/ttyUSB0
FLAGS = -mmcu=atmega328 -DF_CPU=$(F_CPU)
INC = -Iinc

SRC_PATH = src/
BIN_PATH = bin/

SRC_NAME = main.c
BIN_NAME = $(SRC_NAME:.c=.bin)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
BIN = $(addprefix $(BIN_PATH), $(BIN_NAME))

all: hex flash

$(HEX): $(BIN)
	$(eval DO_FLASH := 1)
	avr-objcopy $(BIN) -O ihex $(HEX)
	
$(BIN_PATH)%.bin: $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $< -o $@ -mmcu=atmega328 -DF_CPU=$(F_CPU) -Os

hex: $(HEX)

flash:
	if [ ! -z $(DO_FLASH) ]; then \
		avrdude -b $(BAUD_RATE) -c arduino -p m328p -P $(PORT) -e -U flash:w:$(HEX); \
	fi

clean:
	rm -rf $(HEX) $(BIN_PATH)

.PHONY: all hex flash clean
