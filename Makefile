CC = clang
CFLAGS = -Wall -Wextra

.PHONY: test
test: tests
	./tests

tests: tests.o dynamic_array.o
	$(CC) $(CFLAGS) -o tests tests.o dynamic_array.o

tests.o: tests.c
	$(CC) $(CFLAGS) -c -o tests.o tests.c

dynamic_array.o: dynamic_array.c
	$(CC) $(CFLAGS) -c -o dynamic_array.o dynamic_array.c

.PHONY: clean
clean:
	rm -f dynamic_array.o tests.o tests
