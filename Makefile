CC = gcc
CFLAGS = -g -Wall -pedantic -O0
LFLAGS = 
LDLIBS =

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,$(SRC))
TARGET = $(patsubst %.o,%,$(OBJ))

all: $(TARGET)

$(TARGET):$(OBJ)

clean:
	rm -rf $(OBJ) $(TARGET)

