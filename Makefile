CC=gcc
CFLAGS=-Wall
LDFLAGS=-lMLV
REPOBJ=bin/main.o bin/window.o bin/key_listener.o bin/player_controller.o
OBJ=main.o window.o key_listener.o player_controller.o
MAIN=main
BIN=bin/

all: $(OBJ)
	$(CC) $(REPOBJ) $(LDFLAGS) -o $(MAIN)

main.o: src/main.c src/include/window.h src/include/key_listener.h src/include/player_controller.h
	$(CC) -c src/main.c $(CFLAGS) -o $(BIN)$@

window.o: src/view/window.c src/include/window.h src/include/key_listener.h src/include/player_controller.h src/include/struct_entity.h
	$(CC) -c src/view/window.c $(CFLAGS) -o $(BIN)$@

key_listener.o: src/controller/key_listener.c src/include/key_listener.h src/include/player_controller.h
	$(CC) -c src/controller/key_listener.c $(CFLAGS) -o $(BIN)$@

player_controller.o: 
	$(CC) -c src/controller/player_controller.c $(CFLAGS) -o $(BIN)$@

run:
	./$(MAIN)
