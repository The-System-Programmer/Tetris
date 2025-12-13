#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// ============================================================
// SIMPLE TETRIS USING NCURSES
// Grid-based, multiple tetrominoes, rotation
// ============================================================

#define GRID_WIDTH  10
#define GRID_HEIGHT 20

#define FALL_DELAY_US 500000  // microseconds

// --------------------
// Tetromino definition
// --------------------
typedef struct {
    int blocks[4][2];
    char ch;
} Tetromino;

static const Tetromino TETROMINOS[] = {
    // O
    { {{0,0},{1,0},{0,1},{1,1}}, '#' },
    // I
    { {{0,1},{1,1},{2,1},{3,1}}, '#' },
    // T
    { {{1,0},{0,1},{1,1},{2,1}}, '#' },
    // L
    { {{0,0},{0,1},{0,2},{1,2}}, '#' },
    // J
    { {{1,0},{1,1},{1,2},{0,2}}, '#' }
};

#define TETROMINO_COUNT (sizeof(TETROMINOS)/sizeof(TETROMINOS[0]))

// --------------------
// Game state
// --------------------
static int grid[GRID_HEIGHT][GRID_WIDTH] = {0};

static int pieceX, pieceY;
static int pieceType;
static int rotation;

// --------------------
// Rotate point 90 deg clockwise
// --------------------
void rotate_point(int *x, int *y)
{
    int t = *x;
    *x = -*y;
    *y = t;
}

// --------------------
// Collision check
// --------------------
int can_place(int px, int py, int r)
{
    for (int i = 0; i < 4; i++)
    {
        int x = TETROMINOS[pieceType].blocks[i][0];
        int y = TETROMINOS[pieceType].blocks[i][1];

        for (int k = 0; k < r; k++)
            rotate_point(&x, &y);

        int gx = px + x;
        int gy = py + y;

        if (gx < 0 || gx >= GRID_WIDTH)  return 0;
        if (gy < 0 || gy >= GRID_HEIGHT) return 0;
        if (grid[gy][gx])                return 0;
    }
    return 1;
}

// --------------------
// Lock piece
// --------------------
void place_piece(void)
{
    for (int i = 0; i < 4; i++)
    {
        int x = TETROMINOS[pieceType].blocks[i][0];
        int y = TETROMINOS[pieceType].blocks[i][1];

        for (int k = 0; k < rotation; k++)
            rotate_point(&x, &y);

        grid[pieceY + y][pieceX + x] = 1;
    }
}

// --------------------
// Clear lines
// --------------------
void clear_lines(void)
{
    for (int y = GRID_HEIGHT - 1; y >= 0; y--)
    {
        int full = 1;
        for (int x = 0; x < GRID_WIDTH; x++)
            if (!grid[y][x]) { full = 0; break; }

        if (full)
        {
            for (int row = y; row > 0; row--)
                for (int col = 0; col < GRID_WIDTH; col++)
                    grid[row][col] = grid[row - 1][col];

            for (int col = 0; col < GRID_WIDTH; col++)
                grid[0][col] = 0;

            y++;
        }
    }
}

// --------------------
// Spawn piece
// --------------------
int spawn_piece(void)
{
    pieceType = rand() % TETROMINO_COUNT;
    pieceX = GRID_WIDTH / 2 - 1;
    pieceY = 0;
    rotation = 0;

    return can_place(pieceX, pieceY, rotation);
}

// --------------------
// Draw game
// --------------------
void draw(void)
{
    clear();

    // grid
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            if (grid[y][x])
            {
                mvaddch(y, x * 2, '[');
                mvaddch(y, x * 2 + 1, ']');
            }
            else
            {
                mvaddch(y, x * 2, '.');
                mvaddch(y, x * 2 + 1, ' ');
            }
        }
    }

    // active piece
    for (int i = 0; i < 4; i++)
    {
        int x = TETROMINOS[pieceType].blocks[i][0];
        int y = TETROMINOS[pieceType].blocks[i][1];

        for (int k = 0; k < rotation; k++)
            rotate_point(&x, &y);

        mvaddch(pieceY + y, (pieceX + x) * 2, '[');
        mvaddch(pieceY + y, (pieceX + x) * 2 + 1, ']');
    }

    refresh();
}

// ============================================================
// Main
// ============================================================
int main(void)
{
    srand(time(NULL));

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    if (!spawn_piece())
    {
        endwin();
        return 0;
    }

    while (1)
    {
        int ch = getch();

        if (ch == 'q') break;

        if (ch == KEY_LEFT && can_place(pieceX - 1, pieceY, rotation))
            pieceX--;
        else if (ch == KEY_RIGHT && can_place(pieceX + 1, pieceY, rotation))
            pieceX++;
        else if (ch == KEY_DOWN && can_place(pieceX, pieceY + 1, rotation))
            pieceY++;
        else if (ch == KEY_UP)
        {
            int nr = (rotation + 1) % 4;
            if (can_place(pieceX, pieceY, nr))
                rotation = nr;
        }

        if (can_place(pieceX, pieceY + 1, rotation))
        {
            pieceY++;
        }
        else
        {
            place_piece();
            clear_lines();
            if (!spawn_piece()) break;
        }

        draw();
        usleep(FALL_DELAY_US);
    }

    endwin();
    return 0;
}
