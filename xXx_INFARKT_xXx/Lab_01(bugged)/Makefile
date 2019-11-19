CAT1 = Debug/
CAT2 = Release/
SOURSES = main.c
OBJECT = main.o
EXECUTE = main.exe

debug:
	mkdir -p $(CAT1)
	gcc -g3 -pedantic -std=c99 -Wall -Werror -c $(SOURSES) 
	mv -f $(OBJECT) $(CAT1)$(OBJECT)
	gcc -g3 -pedantic -pthread $(CAT1)$(OBJECT) -o $(CAT1)$(EXECUTE) -lm
	
cleand:
	rm -R $(CAT1)

cleanr:
	rm -R $(CAT2)

release:
	mkdir -p $(CAT2)
	gcc -pedantic -std=c99 -Wall -Werror -c $(SOURSES) 
	mv -f $(OBJECT) $(CAT2)$(OBJECT)
	gcc -pedantic -pthread $(CAT2)$(OBJECT) -o $(CAT2)$(EXECUTE) -lm
