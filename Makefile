all:
	gcc -o main complex.c matrix.c integer.c MatrixError.c main.c
run:
	./main
	rm main