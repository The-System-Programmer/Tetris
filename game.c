#include <stdlib.h>
#include "game.h"
#include "pieces.h"

int field[HEIGHT][WIDTH] = {0};
int curPiece, px, py;

int check_collision(int nx, int ny) {
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (pieces[curPiece][y][x]) {
                int fx = nx + x;
                int fy = ny + y;
                if (fx < 0 || fx >= WIDTH || fy >= HEIGHT) return 1;
                if (fy >= 0 && field[fy][fx]) return 1;
            }
    return 0;
}

void lock_piece(void) {
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (pieces[curPiece][y][x])
                field[py + y][px + x] = 1;
}

void clear_lines(void) {
    for (int y = HEIGHT - 1; y >= 0; y--) {
        int full = 1;
        for (int x = 0; x < WIDTH; x++)
            if (!field[y][x]) full = 0;
        if (full) {
            for (int yy = y; yy > 0; yy--)
                for (int x = 0; x < WIDTH; x++)
                    field[yy][x] = field[yy-1][x];
            for (int x = 0; x < WIDTH; x++)
                field[0][x] = 0;
            y++;
        }
    }
}

void spawn_piece(void) {
    curPiece = rand() % 5;
    px = WIDTH / 2 - 2;
    py = 0;
}
