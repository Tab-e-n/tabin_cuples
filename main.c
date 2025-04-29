#include <raylib.h>
#include "cuplib.h"

int main(void)
{
	InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "CUPLES");

	SetTargetFPS(60);
	SetExitKey(KEY_NULL);

	while(!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello!", 0, 0, 32, BLACK);
		EndDrawing();

	}

	CloseWindow();

	return 0;
}
