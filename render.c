#include <ncurses.h>
#include "render.h"
#include "game.h"
#include "pieces.h"

void draw(void) {
    clear();

    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            mvprintw(y, x * 2, field[y][x] ? "[]" : " .");

    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (pieces[curPiece][y][x])
                mvprintw(py + y, (px + x) * 2, "[]");

    refresh();
}
