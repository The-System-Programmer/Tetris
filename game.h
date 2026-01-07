#ifndef GAME_H
#define GAME_H

#define WIDTH 10
#define HEIGHT 20

extern int field[HEIGHT][WIDTH];
extern int curPiece, px, py;

int check_collision(int nx, int ny);
void lock_piece(void);
void clear_lines(void);
void spawn_piece(void);

#endif
