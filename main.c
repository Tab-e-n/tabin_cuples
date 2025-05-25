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

	units_left[0] = UnitInit();
	units_left[0].position = LEFT_START_POS;
	units_left[0].side = 1;
	units_left[0].state = STATE_MOVE;

	units_left[1] = UnitInit();
	units_left[1].position = LEFT_START_POS;
	units_left[1].position.x -= 80;
	units_left[1].side = 1;
	units_left[1].length = 2.0;
	units_left[1].speed = 32.0;
	units_left[1].state = STATE_MOVE;
	units_left[1].cups[1].active = 1;
	units_left[1].cups[1].offset.x = 32;
	units_left[1].cups[2].active = 1;
	units_left[1].cups[2].offset.x = 16;
	units_left[1].cups[2].offset.y = 32;

	units_right[0] = UnitInit();
	units_right[0].position = RIGHT_START_POS;
	units_right[0].side = -1;
	units_right[0].state = STATE_MOVE;

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
