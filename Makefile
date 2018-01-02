
CC = gcc
CFLAGS = -Wall -ftrapv -Wfloat-equal -Wunreachable-code
TARGET = baseconv

all:
	$(CC) $(CFLAGS) *.c -o $(TARGET)