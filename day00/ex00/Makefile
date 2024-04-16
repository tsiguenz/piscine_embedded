HEX = main.hex
F_CPU = 16000000UL
CC = avr-gcc
CFLAGS = -Wall -Werror -Wextra -mmcu=atmega328 -DF_CPU=$(F_CPU) -Os
INC = -Iinclude

SRC_PATH = src/
BIN_PATH = bin/
OBJ_PATH = obj/

SRC_NAME = main.c
BIN_NAME = $(HEX:.hex=.bin)
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
BIN = $(addprefix $(BIN_PATH), $(BIN_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

BAUD_RATE = 115200
PORT = /dev/ttyUSB0
DUDE_FLAGS = -b $(BAUD_RATE) -c arduino -p m328p -P $(PORT) -e -U flash:w:$(HEX)

all: $(HEX) flash

$(BIN): $(OBJ)
	$(eval DO_FLASH := 1)
	mkdir -p $(@D)
	$(CC) $(OBJ) $(CFLAGS) $(INC) -o $(BIN)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

$(OBJ_PATH):
	mkdir -p $@

$(HEX): $(BIN)
	avr-objcopy $(BIN) -O ihex $@

flash:
	if [ ! -z $(DO_FLASH) ]; then \
		avrdude $(DUDE_FLAGS); \
	fi

clean:
	rm -rf $(HEX) $(BIN_PATH) $(OBJ_PATH)

.PHONY: all hex flash clean
