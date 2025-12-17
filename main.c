#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 10
#define HEIGHT 20

int field[HEIGHT][WIDTH];

// Piece definitions (no rotation)
// Max size 4x4
int pieces[5][4][4] = {
    // I
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    // _ (horizontal bar of 3)
    {
        {0,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // Square
    {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // L
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    // T
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }
};

int curPiece, px, py;

int check_collision(int nx, int ny) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (pieces[curPiece][y][x]) {
                int fx = nx + x;
                int fy = ny + y;
                if (fx < 0 || fx >= WIDTH || fy >= HEIGHT)
                    return 1;
                if (fy >= 0 && field[fy][fx])
                    return 1;
            }
        }
    }
    return 0;
}

void lock_piece() {
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (pieces[curPiece][y][x])
                field[py + y][px + x] = 1;
}

void clear_lines() {
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

void spawn_piece() {
    curPiece = rand() % 5;
    px = WIDTH / 2 - 2;
    py = 0;
}

void draw() {
    clear();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            mvprintw(y, x * 2, field[y][x] ? "[]" : " .");
        }
    }
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (pieces[curPiece][y][x]) {
                mvprintw(py + y, (px + x) * 2, "[]");
            }
        }
    }
    refresh();
}

int main() {
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
        if (ch == KEY_LEFT && !check_collision(px - 1, py)) px--;
        if (ch == KEY_RIGHT && !check_collision(px + 1, py)) px++;
        if (ch == KEY_DOWN && !check_collision(px, py + 1)) py++;

        if (tick++ > 20) {
            if (!check_collision(px, py + 1)) {
                py++;
            } else {
                lock_piece();
                clear_lines();
                spawn_piece();
                if (check_collision(px, py)) break; // game over
            }
            tick = 0;
        }
        draw();
        usleep(50000);
    }

    endwin();
    return 0;
}

