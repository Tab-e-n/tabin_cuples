#include <raylib.h>
#include "cuplib.h"
#include "units.h"

int main(void)
{
	InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "CUPLES");

	SetTargetFPS(60);
	SetExitKey(KEY_NULL);

	const Vector2 LEFT_START_POS = (Vector2){128, 256}; 
	const Vector2 RIGHT_START_POS = (Vector2){496, 256};

	Unit units_left[MAX_UNITS] = {0};
	Unit units_right[MAX_UNITS] = {0};

	units_left[0] = MakeUnit(UNIT_BASIC, LEFT_START_POS, 1);
	units_left[1] = MakeUnit(UNIT_TALL, LEFT_START_POS, 1);
	units_right[0] = MakeUnit(UNIT_BASIC, RIGHT_START_POS, -1);
	units_right[1] = MakeUnit(UNIT_THROWER, RIGHT_START_POS, -1);

	while(!WindowShouldClose())
	{

		for(int i = 0; i < MAX_UNITS; i++)
		{
			UnitProcess(&units_left[i], units_right, units_left);
			UnitProcess(&units_right[i], units_left, units_right);
		}
		for(int i = 0; i < MAX_UNITS; i++)
		{
			UnitDamage(&units_left[i]);
			UnitDamage(&units_right[i]);
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		for(int i = 0; i < MAX_UNITS; i++)
		{
			DrawUnitDebug(units_left[i]);
			DrawUnitDebug(units_right[i]);
		}
		EndDrawing();

	}

	CloseWindow();

	return 0;
}
