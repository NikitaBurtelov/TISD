CC = gcc
CFLAGS = -MMD -g3 -c
MAZE_MAIN_OBJECTS = $(subst main.o,,$(patsubst %.c,%.o,$(wildcard *.c)))
MAIN_OBJECTS = $(subst mazeMain.o,,$(patsubst %.c,%.o,$(wildcard *.c)))

.PHONY: clean all headgen

all: main.exe mazeMain.exe

main.exe: $(MAIN_OBJECTS)
	$(CC) -o main.exe $(MAIN_OBJECTS)

mazeMain.exe: $(MAZE_MAIN_OBJECTS)
	$(CC) -o mazeMain.exe $(MAZE_MAIN_OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $<

headgen: 
	python3 -m headgen.headgen
	rm -r main.h mazeMain.h
	mv *.h headers/

clean: 
	rm *.exe *.o *.d
	
include $(wildcard *.d) 
