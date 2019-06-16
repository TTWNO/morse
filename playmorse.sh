#!/bin/bash

# REQUIRES: play

# TODO: write using play libraries in C. Not sure if possible, but would be nice.
# ... even if just for compatibility reasons.

FILENAME="$1"
FILE_CONTENTS="$(cat $FILENAME)"



while read -n1 character; do
    if [ "$character" == "-" ]; then
        play -q -n synth 0.15 sine 850 vol 0.5
    elif [ "$character" == "." ]; then
        play -q -n synth 0.05 sine 850 vol 0.5
    elif [ "$chracter" == "" ]; then
        sleep 0.2
    elif [ "$character" == "/" ]; then
        sleep 0.5
    fi
done < <(echo -n "$FILE_CONTENTS")
