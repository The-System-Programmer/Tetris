import pyray as pr
import random

# --- Config ---
CELL = 30
COLS = 10
ROWS = 20
WIDTH = COLS * CELL
HEIGHT = ROWS * CELL

# Tetris shapes (rotation states)
SHAPES = [
    [[[1,1,1,1]], [[1],[1],[1],[1]]],                                                   # I
    [[[1,1],[1,1]]],                                                                    # O
    [[[0,1,0],[1,1,1]], [[1,0],[1,1],[1,0]], [[1,1,1],[0,1,0]], [[0,1],[1,1],[0,1]]],   # T
    [[[0,1,1],[1,1,0]], [[1,0],[1,1],[0,1]]],                                           # S
    [[[1,1,0],[0,1,1]], [[0,1],[1,1],[1,0]]],                                           # Z
    [[[1,0,0],[1,1,1]], [[1,1],[1,0],[1,0]], [[1,1,1],[0,0,1]], [[0,1],[0,1],[1,1]]],   # J
    [[[0,0,1],[1,1,1]], [[1,0],[1,0],[1,1]], [[1,1,1],[1,0,0]], [[1,1],[0,1],[0,1]]]    # L
]

COLORS = [pr.SKYBLUE, pr.YELLOW, pr.PURPLE, pr.GREEN, pr.RED, pr.BLUE, pr.ORANGE]

# --- Helpers ---
def new_piece():
    i = random.randrange(len(SHAPES))
    return {
        'shape': SHAPES[i],
        'rot': 0,
        'x': COLS // 2 - 2,
        'y': 0,
        'color': COLORS[i]
    }

def collide(board, piece, dx=0, dy=0, drot=0):
    shape = piece['shape'][(piece['rot'] + drot) % len(piece['shape'])]
    for y,row in enumerate(shape):
        for x,val in enumerate(row):
            if val:
                nx = piece['x'] + x + dx
                ny = piece['y'] + y + dy
                if nx < 0 or nx >= COLS or ny >= ROWS:
                    return True
                if ny >= 0 and board[ny][nx]:
                    return True
    return False

def lock(board, piece):
    shape = piece['shape'][piece['rot']]
    for y,row in enumerate(shape):
        for x,val in enumerate(row):
            if val and piece['y']+y >= 0:
                board[piece['y']+y][piece['x']+x] = piece['color']

# --- Game ---
pr.init_window(WIDTH, HEIGHT, "Tetris (pyray)")
pr.set_target_fps(60)

board = [[None for _ in range(COLS)] for _ in range(ROWS)]
piece = new_piece()
# No game-over condition: if spawn collides, reset the board
if collide(board, piece):
    board = [[None for _ in range(COLS)] for _ in range(ROWS)]
timer = 0
speed = 0.5
game_over = False

while not pr.window_should_close():
    if game_over:
        pr.begin_drawing()
        pr.clear_background(pr.BLACK)
        pr.draw_text("GAME OVER", WIDTH//2 - 120, HEIGHT//2 - 20, 40, pr.RED)
        pr.draw_text("Press ENTER to restart", WIDTH//2 - 160, HEIGHT//2 + 30, 20, pr.WHITE)
        pr.end_drawing()
        if pr.is_key_pressed(pr.KEY_ENTER):
            board = [[None for _ in range(COLS)] for _ in range(ROWS)]
            piece = new_piece()
            timer = 0
            game_over = False
        continue
    dt = pr.get_frame_time()
    timer += dt

    # Input
    if pr.is_key_pressed(pr.KEY_LEFT) and not collide(board, piece, dx=-1): piece['x'] -= 1
    if pr.is_key_pressed(pr.KEY_RIGHT) and not collide(board, piece, dx=1): piece['x'] += 1
    if pr.is_key_pressed(pr.KEY_UP) and not collide(board, piece, drot=1): piece['rot'] = (piece['rot']+1) % len(piece['shape'])
    if pr.is_key_down(pr.KEY_DOWN): timer += speed * 2

    # Gravity
    if timer >= speed:
        timer = 0
        if not collide(board, piece, dy=1):
            piece['y'] += 1
        else:
            lock(board, piece)
            piece = new_piece()
            if collide(board, piece):
                game_over = True

    # Clear lines
    board = [row for row in board if any(c is None for c in row)]
    while len(board) < ROWS:
        board.insert(0, [None]*COLS)

    # Draw
    pr.begin_drawing()
    pr.clear_background(pr.BLACK)

    for y in range(ROWS):
        for x in range(COLS):
            if board[y][x]:
                pr.draw_rectangle(x*CELL, y*CELL, CELL-1, CELL-1, board[y][x])

    shape = piece['shape'][piece['rot']]
    for y,row in enumerate(shape):
        for x,val in enumerate(row):
            if val and piece['y']+y >= 0:
                pr.draw_rectangle((piece['x']+x)*CELL, (piece['y']+y)*CELL, CELL-1, CELL-1, piece['color'])

    pr.end_drawing()

pr.close_window()

