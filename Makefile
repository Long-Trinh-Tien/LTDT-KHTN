#!/bin/bash
TARGET = phuong_an_A
CC = gcc
CFLAGS = -Wall -Wextra

SRCS = $(TARGET).c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	./$(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

run: all
	./$(TARGET)
.PHONY: all clean run
