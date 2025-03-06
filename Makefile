all:
	gcc -o main main.c complex.c matrix.c integer.c
run:
	./main
	rm main
