#include <raylib.h>
#include "cuplib.h"
#include "units.h"

int main(void)
{
	InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "CUPLES");

	SetTargetFPS(60);
	SetExitKey(KEY_NULL);

	Unit unit = (Unit){0};
	unit.position = (Vector2){256, 256};

	while(!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawUnitDebug(unit);
		EndDrawing();

	}

	CloseWindow();

	return 0;
}
