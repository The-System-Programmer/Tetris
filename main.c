#include "raylib.h"

#define Cell_Size 	50	
#define Grid_Width 	10
#define Grid_Height	20

static int grid[Grid_Height][Grid_Width] = {0};

int blockX = 5;
int blockY = 0;

float fallTimer = 0.0f;
int main()
{
	InitWindow(Grid_Width * Cell_Size , Grid_Height * Cell_Size,"Phase 1");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		fallTimer += GetFrameTime();
		if (fallTimer >= 0.5f)
		{
			fallTimer = 0.0f;
			blockY++;
		}

		BeginDrawing();
			ClearBackground(BLACK);

			for(int y = 0 ; y < Grid_Height ; y++)
			{
				for(int x = 0 ; x < Grid_Width ; x++)
				{
					DrawRectangleLines(x*Cell_Size,y*Cell_Size,Cell_Size,Cell_Size,DARKGRAY);
				}
			}
			DrawRectangle(blockX*Cell_Size,blockY*Cell_Size,Cell_Size,Cell_Size,ORANGE);
			EndDrawing();
	}
	CloseWindow();
	return 0;
}
