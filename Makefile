CC = gcc
CFLAGS = -g -O2 -Wall `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`

main:
	$(CC) $(CFLAGS) $(LDFLAGS) main.c $(LDLIBS) -o main

run:
	rm main 
	make
	./main

