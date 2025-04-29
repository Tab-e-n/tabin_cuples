#include <raylib.h>
#include "cuplib.h"
#include "units.h"

int main(void)
{
	InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "CUPLES");

	SetTargetFPS(60);
	SetExitKey(KEY_NULL);

	Unit unit = UnitInit();
	unit.position = (Vector2){16, 256};
	unit.side = 1;

	Unit unit2 = UnitInit();
	unit2.position = (Vector2){496, 256};
	unit2.side = -1;

	while(!WindowShouldClose())
	{

		UnitProcess(&unit);
		UnitProcess(&unit2);

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawUnitDebug(unit);
		DrawUnitDebug(unit2);
		EndDrawing();

	}

	CloseWindow();

	return 0;
}
