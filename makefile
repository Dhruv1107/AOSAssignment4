all: main.o multiplycomplexnumbers.o
	gcc -o complexnumbers main.o multiplycomplexnumbers.o -lpthread
	
main.o: main.c complexnumbers.h
	gcc -c main.c -lpthread

multiplycomplexnumbers.o: multiplycomplexnumbers.c complexnumbers.h
	gcc -c multiplycomplexnumbers.c -lpthread
	
clean:
	rm -f *.o *.out
