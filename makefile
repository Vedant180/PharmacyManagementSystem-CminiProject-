output: project.o main.o
	gcc project.o main.o -o output

project.o: project.c project.h
	gcc -c project.c

clean:
	rm*.o


