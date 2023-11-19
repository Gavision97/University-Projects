JerryBoree: JerryBoreeMain.o Jerry.o HashTable.o KeyValuePair.o LinkedList.o MultiValueHashTable.o
	gcc JerryBoreeMain.o Jerry.o HashTable.o KeyValuePair.o LinkedList.o MultiValueHashTable.o -o JerryBoree

Jerry.o: Jerry.c Defs.h Jerry.h
	gcc -c Jerry.c

HashTable.o: HashTable.c Defs.h LinkedList.h KeyValuePair.h Hash.h
	gcc -c HashTable.c

KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c

LinkedList.o: LinkedList.c Defs.h LinkedList.h
	gcc -c LinkedList.c

MultiValueHashTable.o: MultiValueHashTable.c Defs.h LinkedList.h Hash.h  MultiValueHashTable.h KeyValuePair.h
	gcc -c MultiValueHashTable.c

JerryBoreeMain.o: JerryBoreeMain.c Defs.h LinkedList.h Hash.h MultiValueHashTable.h KeyValuePair.h Jerry.h 
	gcc -c JerryBoreeMain.c
clean:
	rm -f *.o
