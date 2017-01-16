DEBUG = -DDEBUG -g -O0 -Wall -Wextra
CFLAGS = -O2 -Wall -Wextra

all:
	gcc stackmachine.c -o Bin/stackmachine $(CFLAGS)
	g++ assembler.cpp -o Bin/assembler -std=gnu++14 $(CFLAGS)

assembler:
	g++ assembler.cpp -o Bin/assembler -std=gnu++14 $(CFLAGS)

stackmachine:
	gcc stackmachine.c -o Bin/stackmachine $(CFLAGS)

debug:
	gcc stackmachine.c -o Debug/stackmachine $(DEBUG)
	g++ assembler.cpp -o Debug/assembler -std=gnu++14 $(DEBUG)

clean:
	rm -rf Bin/*
	rm -rf Debug/*
