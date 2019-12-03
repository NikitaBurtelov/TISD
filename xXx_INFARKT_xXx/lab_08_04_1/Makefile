CC = gcc
CFLAGS = -std=c99 -Wall -Werror -MMD -g3 -pedantic -c
TEST_OBJECTS = $(subst main.o,,$(patsubst %.c,%.o,$(wildcard *.c)))
MAIN_OBJECTS = $(subst test.o,,$(patsubst %.c,%.o,$(wildcard *.c)))

.PHONY: clean all headgen

all: app.exe test.exe

headgen: 
	python3 -m headgen.headgen
	rm -r main.h
	rm -r test.h
	mv *.h headers/

app.exe: $(MAIN_OBJECTS)
	$(CC) -o app.exe $(MAIN_OBJECTS)

test.exe: $(TEST_OBJECTS)
	$(CC) -o test.exe $(MAIN_OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean: 
	rm *.exe *.o *.d
	
include $(wildcard *.d) 
