CC = gcc
CFLAGS = -I./algorithms -Wall
LIB = algorithms/scheduling.c
BIN_DIR = bin

all: test_fcfs cli_program

test_fcfs:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/test_fcfs test/test_fcfs.c $(LIB)

cli_program:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/cli_program cli/main.c $(LIB)

clean:
	rm -rf $(BIN_DIR)/*
