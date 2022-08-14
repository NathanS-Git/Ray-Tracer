main: src/main.c
	gcc -O2 -fno-omit-frame-pointer -g -Wall -std=gnu11 src/main.c -o output -lm
