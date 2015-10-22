CC = gcc
CFLAGS = -g -Wall -pedantic -O0
LFLAGS = 
LDLIBS =

SRC = $(wildcard ./src/*.c)
TARGET = $(patsubst %.c,%,$(SRC))

all: $(TARGET)


clean:
	rm -rf  $(TARGET)

