CC = clang
CFLAGS = -Wall -Wextra

.PHONY: test
test: tests
	./tests

tests: tests.o dynamic_array.o
	$(CC) $(CFLAGS) -o tests tests.o dynamic_array.o

tests.o: tests.c
	$(CC) $(CFLAGS) -c -o tests.o tests.c

dynamic_array.o: dynamic_array.c dynamic_array.h
	$(CC) $(CFLAGS) -c -o dynamic_array.o dynamic_array.c

dict.o: dict.c dict.h
	$(CC) $(CFLAGS) -c -o dict.o dict.c

.PHONY: clean
clean:
	rm -f dynamic_array.o tests.o tests
