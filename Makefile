# Makefile to build the project

# Parameters
CC = gcc
CFLAGS = -Wall

SRC = src/
INCLUDE = include/
BIN = bin/

# ftp://[<user>:<password>@]<host>[:port][/<url-path>]
URL = ftp://anonymous:anonymous@ftp.up.pt:21/pub/kodi/timestamp.txt

# Targets
.PHONY: all
all: $(BIN)/main

$(BIN)/main: main.c $(SRC)/*.c
	$(CC) $(CFLAGS) -o $@ $^ -I$(INCLUDE)

.PHONY: run
run: $(BIN)/main
	./$(BIN)/main "$(URL)"

.PHONY: clean
clean:
	rm -f $(BIN)/main
