CFLAGS = -g -Wno-unused-parameter -ggdb
CC = gcc 

PROGRAMS= mainLC mainH

.PHONY:	all clean

all: mainLC mainH

biblioLC: biblioLC.o  biblioLC.h
	$(CC) -o $@ $(CFLAGS) $^

entreeSortieLC: entreeSortieLC.o mainLC.o biblioLC.h 
	$(CC) -o $@ $(CFLAGS) $^

biblioH: biblioH.o biblioH.h
	$(CC) -o $@ $(CFLAGS) $^

entreeSortieH: entreeSortieH.o mainH.o biblioH.h
	$(CC) -o $@ $(CFLAGS) $^

mainLC: biblioLC.o entreeSortieLC.o mainLC.o
	$(CC) -o $@ $(CFLAGS) $^

mainH: biblioH.o entreeSortieH.o mainH.o

clean:
	rm -f *.o *~ $(PROGRAMS)

