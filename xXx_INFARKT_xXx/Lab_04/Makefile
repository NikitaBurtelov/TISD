CC = gcc
CFLAGS = -MD -pedantic -c
MAZE_MAIN_OBJECTS = $(subst main.o,,$(patsubst %.c,%.o,$(wildcard *.c)))
MAIN_OBJECTS = $(subst mazeMain.o,,$(patsubst %.c,%.o,$(wildcard *.c)))

.PHONY: clean all

all: main.exe mazeMain.exe

main.exe: $(MAIN_OBJECTS)
	$(CC) -o main.exe $(MAIN_OBJECTS)

mazeMain.exe: $(MAZE_MAIN_OBJECTS)
	$(CC) -o mazeMain.exe $(MAZE_MAIN_OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean: 
	rm *.exe *.o *.d
	
include $(wildcard *.d) 
