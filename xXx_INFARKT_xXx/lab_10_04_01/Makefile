CC = gcc
CFLAGS = -std=c99 -Wall -Werror -MMD -g3 -pedantic -c
TEST_OBJECTS = $(subst main.o,,$(patsubst %.c,%.o,$(wildcard *.c)))
MAIN_OBJECTS = $(subst test.o,,$(patsubst %.c,%.o,$(wildcard *.c)))

.PHONY: clean all

all: app.exe test.exe

app.exe: $(MAIN_OBJECTS)
	$(CC) -o app.exe $(MAIN_OBJECTS)

test.exe: $(TEST_OBJECTS)
	$(CC) -o test.exe $(TEST_OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean: 
	rm *.exe *.o *.d
	
include $(wildcard *.d) 
