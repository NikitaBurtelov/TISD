CAT1 = Debug/
CAT2 = Release/
CAT3 = includes/
EXECUTE = app.exe 
OBJECTS = main.o table_routines.o file_routines.o idents.o sorts.o
SOURSES = *.c
HEADERS = $(CAT3)file_routines.h $(CAT3)table_routines.h $(CAT3)idents.h $(CAT3)types.h $(CAT3)sorts.h
DEBUG_KEYS = -g3 -pedantic -std=c17 -Wall -Werror 
RELEASE_KEYS = -pedantic -std=c17 -Wall -Werror 
DEBUG_COMP_KEYS = -g3 -pedantic -lm 
RELEASE_COMP_KEYS = -O3 -pedantic -lm 

app.exe: $(OBJECTS)
	gcc $(DEBUG_COMP_KEYS) $(OBJECTS) -o $(EXECUTE)
	mv -f $(OBJECTS) $(CAT1)
	mv -f $(EXECUTE) $(CAT1)

main.o: main.c $(HEADERS)
	mkdir -p $(CAT1)
	gcc $(DEBUG_KEYS) -c $<

file_routines.o: file_routines.c $(HEADERS)
	mkdir -p $(CAT1)
	gcc $(DEBUG_KEYS) -c $<

table_routines.o: table_routines.c $(HEADERS)
	mkdir -p $(CAT1)
	gcc $(DEBUG_KEYS) -c $<

idents.o: idents.c $(HEADERS)
	mkdir -p $(CAT1)
	gcc $(DEBUG_KEYS) -c $<

sorts.o: sorts.c $(HEADERS)
	mkdir -p $(CAT1)
	gcc $(DEBUG_KEYS) -c $<

cleanD:
	rm -R $(CAT1)

release: $(SOURSES)
	mkdir -p $(CAT2)
	gcc $(RELEASE_COMP_KEYS) -o $(CAT2)$(EXECUTE)

cleanR:
	rm -R $(CAT2)
