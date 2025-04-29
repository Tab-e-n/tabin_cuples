cuples.out : main.o cuplib.o
	gcc -o cuples.out main.o cuplib.o -lraylib

main.o : main.c cuplib.h
	gcc -c main.c -lraylib

cuplib.o : cuplib.c
	gcc -c cuplib.c -lraylib

clean :
	rm cuples.out main.o cuplib.o
