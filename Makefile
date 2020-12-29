CFLAGS=-Wall -Wextra -Wswitch-enum -std=c11 -pedantic
LIBS=

.PHONY: all
all: basm bmi

basm: ./src/basm.c ./src/bm.h
	$(CC) $(CFLAGS) -o basm ./src/basm.c $(LIBS)

bmi: ./src/bmi.c ./src/bm.h
	$(CC) $(CFLAGS) -o bmi ./src/bmi.c $(LIBS)


.PHONY: examples
examples: ./examples/fib.bm ./examples/123.bm

./examples/fib.bm: basm ./examples/fib.basm
	./basm ./examples/fib.basm ./examples/fib.bm

./examples/123.bm: basm ./examples/123.basm
	./basm ./examples/123.basm ./examples/123.bm
