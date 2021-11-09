all: main.o multiplycomplexnumbers.o
	gcc -o complexnumbers main.o multiplycomplexnumbers.o -O0
	
main.o: main.c complexnumbers.h
	gcc -c main.c -O0

multiplycomplexnumbers.o: multiplycomplexnumbers.c complexnumbers.h
	gcc -c multiplycomplexnumbers.c -O0
	
clean:
	rm -f *.o *.out
