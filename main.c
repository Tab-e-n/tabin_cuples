#include <raylib.h>
#include "cuplib.h"
#include "units.h"

// Temporary randomness
#include <stdlib.h>
#include <time.h>

int main(void)
{
	InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "CUPLES");

	SetTargetFPS(60);
	SetExitKey(KEY_NULL);

	Camera2D camera = (Camera2D){0};
	camera.target = Vector2Zero();
	camera.offset = (Vector2){SCREEN_SIZE.x * 0.5, SCREEN_SIZE.y * 0.5};
	camera.zoom = 1.0;

	const Vector2 LEFT_START_POS = (Vector2){-256, 128}; 
	const Vector2 RIGHT_START_POS = (Vector2){256, 128};

	Unit units_left[MAX_UNITS] = {0};
	Unit units_right[MAX_UNITS] = {0};

	units_left[0] = MakeUnit(UNIT_BASE, LEFT_START_POS, 1);
	units_left[1] = MakeUnit(UNIT_HORSE, LEFT_START_POS, 1);
	units_left[2] = MakeUnit(UNIT_BASIC, LEFT_START_POS, 1);
	units_right[0] = MakeUnit(UNIT_BASE, RIGHT_START_POS, -1);
	units_right[1] = MakeUnit(UNIT_CANNON, RIGHT_START_POS, -1);
	units_right[2] = MakeUnit(UNIT_BASIC, RIGHT_START_POS, -1);

	srand(time(0));
	float tempo_spawn_timer = 0.0;
	int unit = 3;

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
		if(unit < MAX_UNITS)
		{
			tempo_spawn_timer += .016;
			if(tempo_spawn_timer > 20.0)
			{
				tempo_spawn_timer = 0.0;
				units_left[unit] = MakeUnit(rand()%7+1, LEFT_START_POS, 1);
				units_right[unit] = MakeUnit(rand()%7+1, RIGHT_START_POS, -1);
				unit++;
			}
		}


		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(camera);
		for(int i = 0; i < MAX_UNITS; i++)
		{
			DrawUnitDebug(units_left[i]);
			DrawUnitDebug(units_right[i]);
		}
		for(int i = 0; i < MAX_UNITS; i++)
		{
			DrawUnitDebugAttack(units_left[i]);
			DrawUnitDebugAttack(units_right[i]);
		}
		for(int i = 0; i < MAX_UNITS; i++)
		{
			DrawHealthBar(units_left[i]);
			DrawHealthBar(units_right[i]);
		}
		EndMode2D();
		EndDrawing();

	}

	CloseWindow();

	return 0;
}
