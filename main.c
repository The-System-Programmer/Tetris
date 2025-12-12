#include "raylib.h"
int main()
{
	const int screenwidth = 800;
	const int screenheight= 450;
	InitWindow(screenwidth,screenheight,"Basic Window");
	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(RAYWHITE);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
