CC?=gcc

defualt: build

morse.o:
	$(CC) -O2 morse.c -c -o morse.o

build: morse.o
	$(CC) -O2 morse.o main.c -o morse

tests: morse.o
	$(CC) -O2 test.c morse.o -o test

install:
	cp morse ~/.local/bin/

uninstll:
	rm ~/.local/bin/morse

clean:
	rm morse || echo "No file 'morse' to delete"
	rm *out || echo "No \*.out files to delete"
	rm *o ||  echo "No \*.o files to delete"
	rm test || echo "No file 'test' to delete"
