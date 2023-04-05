CC=gcc
CFLAGS=-Wall
LDFLAGS=-lMLV
REPOBJ=bin/main.o bin/window.o
OBJ=main.o window.o 
MAIN=main
BIN=bin/

all: $(OBJ)
	$(CC) $(REPOBJ) $(LDFLAGS) -o $(MAIN)

main.o: src/main.c src/include/window.h
	$(CC) -c src/main.c $(CFLAGS) -o $(BIN)$@

window.o: src/view/window.c src/include/window.h
	$(CC) -c src/view/window.c $(CFLAGS) -o $(BIN)$@

run:
	./$(MAIN)
