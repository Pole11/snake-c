CC=gcc
CFLAGS=-g -Wall -fsanitize=address -fsanitize=undefined
HEADERS=pole.h
OBJ=game.o pole.o 

%.o: %.c $(HEADERS) 
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)