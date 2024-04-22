HEX = main.hex
F_CPU = 16000000UL
CC = avr-gcc
CFLAGS = -Wall -Werror -Wextra -mmcu=atmega328 -DF_CPU=$(F_CPU) -Os
INC = -Iinclude
TMUX_PANE = $(shell tmux list-pane | grep active | cut -d ':' -f1)

SRC_PATH = src/
BIN_PATH = bin/
OBJ_PATH = obj/

SRC_NAME = aht20.c eeprom.c i2c.c main.c uart.c
BIN_NAME = $(HEX:.hex=.bin)
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
BIN = $(addprefix $(BIN_PATH), $(BIN_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

BAUD_RATE = 115200
PORT1 = /dev/ttyUSB0
PORT2 = /dev/ttyUSB1
DUDE_FLAGS = -b $(BAUD_RATE) -c arduino -p m328p -P $(PORT1) -e -U flash:w:$(HEX)

all: $(HEX) flash

$(BIN): $(OBJ)
	mkdir -p $(@D)
	$(CC) $(OBJ) $(CFLAGS) $(INC) -o $(BIN)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

$(HEX): $(BIN)
	avr-objcopy $(BIN) -O ihex $(HEX)

flash:
	pkill screen 2> /dev/null || true
	avrdude $(DUDE_FLAGS)

screen: all
	tmux split-window -h screen /dev/ttyUSB0 115200
	tmux select-pane -t $(TMUX_PANE)

clean:
	rm -rf $(HEX) $(BIN_PATH) $(OBJ_PATH)

.PHONY: all hex flash clean
