main: src/main.c
	gcc -O2 -fno-omit-frame-pointer -g -Wall -I ./include/ src/* -o output -lm
