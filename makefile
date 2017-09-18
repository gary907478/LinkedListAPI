string:
	gcc -g -Wall -std=c11 LinkedListAPI.c StringListDemo.c -o string

struct:
	gcc -g -Wall -std=c11 LinkedListAPI.c StructListDemo.c -o struct

runstring:
	./string

runstruct:
	./struct

clean:
	rm string struct
