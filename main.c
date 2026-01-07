#define _XOPEN_SOURCE 500
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "render.h"

int main(void) {
    srand(time(NULL));
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    spawn_piece();

    int tick = 0;
    while (1) {
        int ch = getch();
        if (ch == 'q') break;
        if (ch == KEY_LEFT && !check_collision(px-1, py)) px--;
        if (ch == KEY_RIGHT && !check_collision(px+1, py)) px++;
        if (ch == KEY_DOWN && !check_collision(px, py+1)) py++;

        if (tick++ > 20) {
            if (!check_collision(px, py+1)) py++;
            else {
                lock_piece();
                clear_lines();
                spawn_piece();
                if (check_collision(px, py)) break;
            }
            tick = 0;
        }

        draw();
        nanosleep(&(struct timespec){0, 50 * 1000 * 1000}, NULL);
    }

    endwin();
    return 0;
}
