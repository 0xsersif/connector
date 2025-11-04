CC=gcc
CFLAGS=-Wall -Wextra -std=c99
TARGET=connector
SOURCE=connector.c

all: $(TARGET)

$(TARGET): $(SOURCE) connector.h
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
