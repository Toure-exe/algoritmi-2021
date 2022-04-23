CFLAGS 		= -g -O1 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS 	= src/*.h Makefile

all: bin/edit_dist bin/edit_dist_test

test: bin/edit_dist_test
	bin/edit_dist_test

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/edit_dist: build/edit_dist.o build/edit_dist_main.o $(COMMON_DEPS)
	$(CC) -o bin/edit_dist build/edit_dist.o build/edit_dist_main.o

bin/edit_dist_test: build/edit_dist_test.o build/edit_dist.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/edit_dist_test build/edit_dist_test.o build/edit_dist.o build/unity.o

clean:
	$(RM) build/*
	$(RM) bin/*
run:
	./bin/edit_dist /home/toure/Desktop/correctme.txt /home/toure/Desktop/dictionary.txt