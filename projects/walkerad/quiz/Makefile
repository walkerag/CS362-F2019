CFLAGS= -Wall -fpic -ftest-coverage -fprofile-arcs -lm -std=c99

all:
	gcc -o testme testme.c -g $(CFLAGS)
	./testme

clean:
	rm -f *.o testme testme.exe  *.gcov *.gcda *.gcno *.so *.out
