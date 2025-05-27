cuples.out : main.o cuplib.o units.o
	gcc -o cuples.out main.o cuplib.o units.o -lraylib

main.o : main.c cuplib.h
	gcc -c main.c -lraylib
cuplib.o : cuplib.c cuplib.h
	gcc -c cuplib.c -lraylib
units.o : units.c units.h cuplib.h
	gcc -c units.c -lraylib

clean :
	rm cuples.out main.o cuplib.o units.o
