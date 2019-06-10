defualt: all

all:
	gcc -O2 morse.c -o morse

install:
	cp morse ~/.local/bin/

uninstll:
	rm ~/.local/bin/morse

clean:
	rm morse
