
CC = gcc
CFLAGS = -I./algorithms -Wall
SRC = algorithms/queue.c algorithms/fcfs.c algorithms/grant_chart.c algorithms/scheduling.c
BIN_DIR = bin
TEST_FLAGS = -lcunit

all: directories test_fcfs cli_program

directories:
	mkdir -p $(BIN_DIR)

test_fcfs: directories
	$(CC) $(CFLAGS) -o $(BIN_DIR)/test_fcfs test/test_fcfs_m.c $(SRC)

cli_program: directories
	$(CC) $(CFLAGS) -o $(BIN_DIR)/cli_program cli/main.c $(SRC)

clean:
	rm -rf $(BIN_DIR)/*

.PHONY: all clean test directories