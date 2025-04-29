cuples : main.o cuplib.o
	cc -o cuples main.o cuplib.o

main.o : main.c cuplib.h
	cc -c main.c -lraylib

cuplib.o : cuplib.c
	cc -c cuplib.c -lraylib

clean :
	rm cuples main.o cuplib.o
