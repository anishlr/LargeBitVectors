.PHONY : all
.PHONY : clean

all:
	gcc -Wall --pedantic -std=c99 src/*.c include/*.h -o bin/BitVector -pthread -lgmp

clean:
	rm -rf bin/*
