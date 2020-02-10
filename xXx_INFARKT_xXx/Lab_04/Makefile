CAT1 = Debug/
CAT3 = headers/
EXECUTE = app.exe 
OBJECTS = main.o mazeGen.o stackArrRoutines.o stackListRoutines.o
TEST_OBJ = mazeGen.o stackArrRoutines.o stackListRoutines.o mazeMain.o pathfind.o
SOURSES = *.c
HEADERS = $(CAT3)mazeGen.h $(CAT3)stackArrRoutines.h $(CAT3)stackListRoutines.h
DEBUG_KEYS = -g3
DEBUG_COMP_KEYS = -g3 -lm 
RELEASE_COMP_KEYS = -O3 -lm 

finvers: $(TEST_OBJ) $(OBJECTS) $(HEADERS)
	make -f Makefile app.exe
	make -f Makefile mazeMain.exe

app.exe: $(OBJECTS) $(HEADERS)
	gcc $(DEBUG_COMP_KEYS) $(OBJECTS) -o app.exe
	mv -f $(OBJECTS) $(CAT1)
	mv -f app.exe $(CAT1)

mazeMain.exe: $(TEST_OBJ) $(HEADERS)
	gcc $(DEBUG_COMP_KEYS) $(TEST_OBJ) -o mazeMain.exe
	mv -f $(TEST_OBJ) $(CAT1)
	mv -f mazeMain.exe $(CAT1)

main.o: main.c $(HEADERS)
	mkdir -p $(CAT1)
	gcc $(DEBUG_KEYS) -c $<

mazeMain.o: mazeMain.c $(HEADERS)
	mkdir -p $(CAT1)
	gcc $(DEBUG_KEYS) -c $<

stackArrRoutines.o: stackArrRoutines.c $(HEADERS)
	mkdir -p $(CAT1)
	gcc $(DEBUG_KEYS) -c $<

stackListRoutines.o: stackListRoutines.c $(HEADERS)
	mkdir -p $(CAT1)
	gcc $(DEBUG_KEYS) -c $<

mazeGen.o: mazeGen.c $(HEADERS)
	mkdir -p $(CAT1)
	gcc $(DEBUG_KEYS) -c $<

pathfind.o: pathfind.c $(HEADERS)
	mkdir -p $(CAT1)
	gcc $(DEBUG_KEYS) -c $<

clean:
	rm -R $(CAT1)
	mkdir -p $(CAT1)
