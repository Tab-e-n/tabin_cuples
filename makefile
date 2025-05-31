cuples.out : main.o cuplib.o units.o summon.o
	gcc -o cuples.out main.o cuplib.o units.o summon.o -lraylib

main.o : main.c cuplib.h
	gcc -c main.c -lraylib
cuplib.o : cuplib.c cuplib.h
	gcc -c cuplib.c -lraylib
units.o : units.c units.h cuplib.h
	gcc -c units.c -lraylib
summon.o : summon.c summon.h cuplib.h
	gcc -c summon.c -lraylib

clean :
	rm cuples.out main.o cuplib.o units.o summon.o
