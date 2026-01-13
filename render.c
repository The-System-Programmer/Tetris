#include <ncurses.h>
#include "render.h"
#include "game.h"
#include "pieces.h"

void draw(void)
{
    int term_h, term_w;
    int offset_y, offset_x;

    getmaxyx(stdscr, term_h, term_w);

    offset_y = (term_h - HEIGHT) / 2;
    offset_x = (term_w - (WIDTH * 2)) / 2;

    clear();

    /* Draw field */
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            mvprintw(offset_y + y,offset_x + x * 2,field[y][x] ? "[]" : " .");
        }
    }

    /* Draw current piece */
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (pieces[curPiece][curRotation][y][x])
            {
                mvprintw(offset_y + py + y,offset_x + (px + x) * 2,"[]");
            }
        }
    }

    refresh();
}
