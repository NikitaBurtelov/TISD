CC = gcc
CFLAGS = -MMD -g3 -c
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))

.PHONY: clean all

all: main.exe

main.exe: $(OBJECTS)
	$(CC) -o main.exe $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean: 
	rm *.exe *.o *.d
	
include $(wildcard *.d) 
