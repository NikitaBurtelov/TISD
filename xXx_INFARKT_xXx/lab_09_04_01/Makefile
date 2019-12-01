CAT3 = headers/
EXECUTE = app.exe 
TEST_EXECUTE = test.exe
OBJECTS = main.o matrix_routines.o math.o
TEST_OBJECTS = test.o matrix_routines.o math.o
SOURSES = *.c
HEADERS = $(CAT3)types.h $(CAT3)matrix_routines.h $(CAT3)includes.h
DEBUG_KEYS = -g3 -pedantic -std=c99 -Wall -Werror 
RELEASE_KEYS = -pedantic -std=c99 -Wall -Werror 
DEBUG_COMP_KEYS = -g3 -pedantic -lm 
RELEASE_COMP_KEYS = -O3 -pedantic -lm 

app.exe: $(OBJECTS) $(HEADERS)
	gcc $(DEBUG_COMP_KEYS) $(OBJECTS) -o $(EXECUTE)

test.exe: $(TEST_OBJECTS) $(HEADERS)
	gcc $(RELEASE_COMP_KEYS) $(TEST_OBJECTS) -o $(TEST_EXECUTE)

math.o: math.c $(HEADERS)
	gcc $(DEBUG_KEYS) -c $<

test.o: test.c $(HEADERS)
	gcc $(DEBUG_KEYS) -c $<

main.o: main.c $(HEADERS)
	gcc $(DEBUG_KEYS) -c $<

matrix_routines.o: matrix_routines.c $(HEADERS)
	gcc $(DEBUG_KEYS) -c $<

clean:
	rm -R *.o *.exe
