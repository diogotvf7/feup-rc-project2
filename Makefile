# Makefile to build the project

# Parameters
CC = gcc
CFLAGS = -Wall

SRC = src/
INCLUDE = include/
BIN = bin/
OUT = output/

# ftp://[<user>:<password>@]<host>[:port][/<url-path>]


# URL = ftp://rcom:rcom@netlab1.fe.up.pt/files/pic1.jpg
# URL = ftp://rcom:rcom@netlab1.fe.up.pt/pipe.txt
# URL = ftp://ftp.up.pt/pub/kodi/robots.txt
URL = ftp://ftp.up.pt/pub/kodi/timestamp.txt

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
	rm -f $(BIN)/main $(OUT)/*
