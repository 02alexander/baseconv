
CC = gcc
CFLAGS = -Wall -ftrapv -Wunreachable-code
TARGET = baseconv

all:
	$(CC) $(CFLAGS) *.c -o $(TARGET)