# Makefile to build the project

# Parameters
CC = gcc
CFLAGS = -Wall

SRC = src/
INCLUDE = include/
BIN = bin/

# ftp://[<user>:<password>@]<host>[:port][/<url-path>]

# URL = ftp://user:password@ftp.up.pt:21/pub/kodi/timestamp.txt
# URL = ftp://ftp.up.pt:21/pub/kodi/timestamp.txt
# URL = ftp://ftp.up.pt/pub/kodi/timestamp.txt
# URL = ftp://user@ftp.up.pt/pub/kodi/timestamp.txt
# URL = ftp://ftp.up.pt:21
# URL = ftp://ftp.up.pt
# URL = ftp://ftp.up.pt:21/

URL = ftp://rcom:rcom@netlab1.fe.up.pt

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
