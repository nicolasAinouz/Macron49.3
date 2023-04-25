CC=gcc
CFLAGS=-Wall 
LDFLAGS=-lMLV -lm -g
REPOBJ=bin/main.o bin/window.o bin/key_listener.o bin/player_controller.o bin/enemies_controller.o bin/game.o
OBJ=main.o window.o key_listener.o player_controller.o enemies_controller.o game.o
MAIN=main
BIN=bin/

all: $(OBJ)
	$(CC) $(REPOBJ) $(LDFLAGS) -o $(MAIN)

main.o: src/main.c src/include/window.h src/include/key_listener.h src/include/player_controller.h src/include/enemies_controller.h src/include/game.h
	$(CC) -c src/main.c $(CFLAGS) -o $(BIN)$@

window.o: src/view/window.c src/include/enemies_controller.h src/include/window.h src/include/key_listener.h src/include/player_controller.h src/include/struct_entity.h 
	$(CC) -c src/view/window.c $(CFLAGS) -o $(BIN)$@

key_listener.o: src/controller/key_listener.c src/include/key_listener.h src/include/player_controller.h src/include/main.h
	$(CC) -c src/controller/key_listener.c $(CFLAGS) -o $(BIN)$@

player_controller.o: 
	$(CC) -c src/controller/player_controller.c $(CFLAGS) -o $(BIN)$@

enemies_controller.o: src/include/key_listener.h src/include/player_controller.h src/include/window.h
	$(CC) -c src/controller/enemies_controller.c $(CFLAGS) -o $(BIN)$@

game.o: src/include/key_listener.h src/include/player_controller.h src/include/enemies_controller.h
	$(CC) -c src/model/game.c $(CFLAGS) -o $(BIN)$@

run:
	./$(MAIN)

clean:
	rm -rf $(BIN)*.o $(MAIN)
