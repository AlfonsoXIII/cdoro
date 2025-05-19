# Makefile

CC = gcc

SRC_DIR = src

CLIENT_SRC = $(SRC_DIR)/cdoro_client.c
DAEMON_SRC = $(SRC_DIR)/cdoro_daemon.c

HEADERS = $(SRC_DIR)/cdoro_definitions.h

CLIENT_OUT = cdoro
DAEMON_OUT = cdoro_daemon

CFLAGS = -I$(SRC_DIR) -Wall -O2

# Reglas
all: $(CLIENT_OUT)

$(CLIENT_OUT): $(CLIENT_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_SRC)

$(DAEMON_OUT): $(DAEMON_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(DAEMON_SRC)

clean:
	rm -f $(CLIENT_OUT) $(DAEMON_OUT)

.PHONY: all clean
