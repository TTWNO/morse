# Morse Code in C

### Options:

`--verbose` or `-v` will add the letter bring printed before the morse code (e.g. (C)-.-.)

`--slow` or `-s` will print each dash (-) and dot (.) with a delay inbetween them for effect. The dash delay is 3x that o the dot.

`--reverse` or `-x` will run this in reverse. Taking morse code and converting it to uppercase letters. (slow and verboce are not usable with this option).

You can pipe data in to be morse codeified

### Limits:

Cannot change the length of the delay for the morse code printing.

### Tests:

`./morse < gettysburg.txt` should let you know if something went wrong.
It's quite a long passage in terms of what this program is meant to do, so if that woks, basically anything will.

## Behvaiour:

If any letters/numbers/symbols are not from the range [A-Za-z0-9] it simply will be ignored.
Only approved characters are dealt with.


### Install:

`make`
`make install`

Only installs in ~/.local/bin/
If this directory does not exist, I don't know what happens.

`make unisntall`
will remove the morse file at ~/.local/bin/morse
