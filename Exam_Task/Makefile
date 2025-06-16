all: program

program: main.c
	gcc -o program main.c -lm

run: program
	./program 0 2 0.5

clean:
	rm -f program output.csv
