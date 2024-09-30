.PHONY: test
test: tests
	./tests

tests: tests.o dynamic_array.o
	clang -o tests tests.o dynamic_array.o

tests.o: tests.c
	clang -c -o tests.o tests.c

dynamic_array.o: dynamic_array.c
	clang -c -o dynamic_array.o dynamic_array.c

.PHONY: clean
clean:
	rm dynamic_array.o tests.o
