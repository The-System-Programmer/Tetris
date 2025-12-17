import pyrar as pr
import random

# -- Config -- 
Cell = 30
Cols = 10
Rows = 20
Width = Cols * Cell
Height= Rows * Cell

Shapes = [
    [[[1,1,1,1]], [[1],[1],[1],[1]]],                                                   # I
    [[[1,1],[1,1]]],                                                                    # O
    [[[0,1,0],[1,1,1]], [[1,0],[1,1],[1,0]], [[1,1,1],[0,1,0]], [[0,1],[1,1],[0,1]]],   # T
    [[[0,1,1],[1,1,0]], [[1,0],[1,1],[0,1]]],                                           # S
    [[[1,1,0],[0,1,1]], [[0,1],[1,1],[1,0]]],                                           # Z
    [[[1,0,0],[1,1,1]], [[1,1],[1,0],[1,0]], [[1,1,1],[0,0,1]], [[0,1],[0,1],[1,1]]],   # J
    [[[0,0,1],[1,1,1]], [[1,0],[1,0],[1,1]], [[1,1,1],[1,0,0]], [[1,1],[0,1],[0,1]]]    # L
]

# -- Helpers --
def new_piece():
    i = random.randrange(len(Shapes))
    return
    {
            'shape': Shapes[i],
            'rot' : 0,
            'x' : Cols // 2-2,
            'y' : 0,
    }

def collide(board,piece,dx = 0 , dy = 0 , drot = )):
    shape = piece['shape'][(piece)['rot']+dront)%len(piece['shape'])]
