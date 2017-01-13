DEBUG = -DDEBUG -g -O0

all:
	gcc stackmachine.c -o stackmachine

assembler:
	g++ assembler.cpp -o assembler -std=gnu++14

debug:
	gcc stackmachine.c -o stackmachine $(DEBUG)

