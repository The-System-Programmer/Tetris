#ifndef GAME_H
#define GAME_H

#include "config.h"

extern int field[HEIGHT][WIDTH];
extern int curPiece;
extern int px, py;

int check_collision(int nx, int ny);
void lock_piece(void);
void clear_lines(void);
void spawn_piece(void);

#endif
