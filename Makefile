# Makefile for BitBoard Checkers
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

SRC = main.c board.c moves.c
OBJ = $(SRC:.c=.o)
OUT = main

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(OUT)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OBJ) $(OUT)