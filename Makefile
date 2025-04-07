all:
	gcc -o main complex.c matrix.c integer.c MatrixError.c test.c interface.c main.c
run:
	./main
	rm main
