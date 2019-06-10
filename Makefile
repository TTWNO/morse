defualt: all

all:
	gcc -O2 morse.c -o morse

clean:
	rm morse
