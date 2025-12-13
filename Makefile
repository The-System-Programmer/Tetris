all : tetris

tetris : main.c libraylib.a raylib.h
	gcc main.c -o tetris -lraylib -lm

run : tetris
	./tetris

clean :
	rm -f tetris 
