CC=gcc
CFLAGS=-Wall 
LDFLAGS=-lMLV -lm -g
REPOBJ=bin/main.o bin/window.o bin/key_listener.o bin/player_controller.o bin/enemies_controller.o bin/game.o bin/powerup.o bin/rocket_controller.o bin/home.o
OBJ=main.o window.o key_listener.o player_controller.o enemies_controller.o game.o powerup.o rocket_controller.o home.o
MAIN=main
BIN=bin/

all: $(OBJ)
	$(CC) $(REPOBJ) $(LDFLAGS) -o $(MAIN)

main.o:
	$(CC) -c src/main.c $(CFLAGS) -o $(BIN)$@

window.o: 
	$(CC) -c src/view/window.c $(CFLAGS) -o $(BIN)$@

key_listener.o: 
	$(CC) -c src/controller/key_listener.c $(CFLAGS) -o $(BIN)$@

player_controller.o: 
	$(CC) -c src/controller/player_controller.c $(CFLAGS) -o $(BIN)$@

enemies_controller.o: 
	$(CC) -c src/controller/enemies_controller.c $(CFLAGS) -o $(BIN)$@

game.o:
	$(CC) -c src/controller/game.c $(CFLAGS) -o $(BIN)$@

powerup.o:
	$(CC) -c src/controller/powerup.c $(CFLAGS) -o $(BIN)$@

rocket_controller.o: 
	$(CC) -c src/controller/rocket_controller.c $(CFLAGS) -o $(BIN)$@

home.o:
	$(CC) -c src/view/home.c $(CFLAGS) -o $(BIN)$@

run:
	./$(MAIN)

clean:
	rm -rf $(BIN)*.o $(MAIN)
