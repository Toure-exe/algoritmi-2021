CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS 	= src/*.h Makefile

all: bin/MergeBinaryInsertionSort bin/MergeBinaryInsertionSort_test

test: bin/MergeBinaryInsertionSort_test
	bin/MergeBinaryInsertionSort_test

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/MergeBinaryInsertionSort: build/MergeBinaryInsertionSort.o build/MergeBinaryInsertionSort_main.o $(COMMON_DEPS)
	$(CC) -o bin/MergeBinaryInsertionSort build/MergeBinaryInsertionSort.o build/MergeBinaryInsertionSort_main.o

bin/MergeBinaryInsertionSort_test: build/MergeBinaryInsertionSort_test.o build/MergeBinaryInsertionSort.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/MergeBinaryInsertionSort_test build/MergeBinaryInsertionSort_test.o build/MergeBinaryInsertionSort.o build/unity.o

clean:
	$(RM) build/*
	$(RM) bin/*

run:
	./bin/MergeBinaryInsertionSort /home/toure/Desktop/records.csv