
CC = gcc
CFLAGS = -I./algorithms -Wall
SRC = algorithms/queue.c algorithms/fcfs.c algorithms/grant_chart.c algorithms/scheduling.c algorithms/rr.c algorithms/sjf.c algorithms/fcfs_stack.c algorithms/stack.c
BIN_DIR = bin
TEST_FLAGS = -lcunit

all: directories test_fcfs cli_program

directories:
	mkdir -p $(BIN_DIR)

test_fcfs: directories
	$(CC) $(CFLAGS) -o $(BIN_DIR)/test_fcfs test/test_fcfs_m.c $(SRC)

test_sjf: directories
	$(CC) $(CFLAGS) -o $(BIN_DIR)/test_sjf test/test_sjf.c $(SRC) 


test_rr: directories
	$(CC) $(CFLAGS) -o $(BIN_DIR)/test_rr test/test_rr.c $(SRC) 


cli_program: directories
	$(CC) $(CFLAGS) -o $(BIN_DIR)/cli_program cli/main.c $(SRC)

clean:
	rm -rf $(BIN_DIR)/*

.PHONY: all clean test directories