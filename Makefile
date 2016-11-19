all:
	gcc stackmachine.c -o stackmachine

debug:
	gcc stackmachine.c -o stackmachine -DDEBUG

