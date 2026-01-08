tetris: main.o game.o render.o pieces.o
	gcc main.o game.o render.o pieces.o -lncurses -o tetris

main.o: main.c game.h render.h
	gcc -Wall -Wextra -c main.c -o main.o

game.o: game.c game.h pieces.h config.h
	gcc -Wall -Wextra -c game.c -o game.o

render.o: render.c render.h game.h pieces.h
	gcc -Wall -Wextra -c render.c -o render.o

pieces.o: pieces.c pieces.h
	gcc -Wall -Wextra -c pieces.c -o pieces.o

clean:
	rm -f *.o tetris
