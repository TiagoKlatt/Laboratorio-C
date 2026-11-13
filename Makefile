CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g
LDLIBS = -lm
OBJS = main.o artemis.o validaciones.o
TARGET = simulador_artemis

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDLIBS)

main.o: main.c artemis.h validaciones.h
artemis.o: artemis.c artemis.h validaciones.h
validaciones.o: validaciones.c validaciones.h

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe

.PHONY: all clean
