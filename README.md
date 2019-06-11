# Morse Code in C

### Options:

`--verbose` or `-v` will add the letter bring printed before the morse code (e.g. (C)-.-.)

`--slow` or `-s` will print each dash (-) and dot (.) with a delay inbetween them for effect. The dash delay is 3x that o the dot.

`--reverse` or `-x` will run this in reverse. Taking morse code and converting it to uppercase letters. (slow and verboce are not usable with this option).

`--dot-delay` or `-td` will let you set the delay for the morse code dots in microseconds (I think, I'm using usleep, whatever that uses). Reasonable balue is 150000, which is also the default. Use with -s option to enable slow printing.

`--dash-delay` or `-hd` will let you set the delay for the morse code dashes in microseconds (again, I think). Reasonable value is 300000, which is also the default. use with -s option to enable slow printing.

`./morse -hd 300000 -td 150000 --slow` for example.

You can pipe data in to be morse codeified

### Limits:


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
