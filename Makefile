CC=gcc
CFLAGS=-Wall -Wextra -std=c11
LDFLAGS=-lncurses
SRC=main.c game.c pieces.c render.c
OBJ=$(SRC:.c=.o)
BIN=tetris

all: $(BIN)
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)
clean:
	rm -f $(OBJ) $(BIN)
