CAT3 = headers/
OBJECTS = main.o array_routines.o my_math.o
TEST_OBJECTS = test.o array_routines.o my_math.o
SOURSES = *.c
HEADERS = $(CAT3)array_routines.h $(CAT3)my_math.h $(CAT3)includes.h
DEBUG_KEYS = -g3 -pedantic -std=c99 -Wall -Werror 
RELEASE_KEYS = -pedantic -std=c99 -Wall -Werror 
DEBUG_COMP_KEYS = -g3 -pedantic -lm 
RELEASE_COMP_KEYS = -O3 -pedantic -lm 

app.exe: $(OBJECTS) $(HEADERS)
	gcc $(DEBUG_COMP_KEYS) $(OBJECTS) -o app.exe

test.exe: $(TEST_OBJECTS) $(HEADERS)
	gcc $(RELEASE_COMP_KEYS) $(TEST_OBJECTS) -o test.exe

test.o: test.c $(HEADERS)
	gcc $(DEBUG_KEYS) -c $<

main.o: main.c $(HEADERS)
	gcc $(DEBUG_KEYS) -c $<

array_routines.o: array_routines.c $(HEADERS)
	gcc $(DEBUG_KEYS) -c $<

my_math.o: my_math.c $(HEADERS)
	gcc $(DEBUG_KEYS) -c $<

clean:
	rm -R *.o *.exe
