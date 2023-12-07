CC := gcc
CFLAGS := -std=gnu17 -O -g -Wall -Wextra -Wpedantic

default: binary

binary: example.o
	@$(CC) $(CFLAGs) -I./ example.c -o $@

example.o: example.c test.h
	@$(CC) $(CFLAGS) -c example.c -o $@

test.h:

.PHONY: clean
clean:
	@rm -rf *.o binary

.PHONY: run
run: binary
	@./binary
