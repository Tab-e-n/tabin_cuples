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

	Side left = SideInit(LEFT_START_POS, 1);
	Side right = SideInit(RIGHT_START_POS, -1);

	SpawnUnit(UNIT_HORSE, &left);
	SpawnUnit(UNIT_CANNON, &right);

	bool processing = true;
	char win = 0;
	srand(time(0));
	float tempo_spawn_timer = 0.0;

	while(!WindowShouldClose())
	{

		if(processing)
		{
			for(int i = 0; i < MAX_UNITS; i++)
			{
				UnitProcess(&left.units[i], &right, &left);
				UnitProcess(&right.units[i], &left, &right);
			}
			for(int i = 0; i < MAX_UNITS; i++)
			{
				UnitDamage(&left.units[i]);
				UnitDamage(&right.units[i]);
			}
			tempo_spawn_timer += .016;
			if(tempo_spawn_timer > 20.0)
			{
				tempo_spawn_timer = 0.0;
				char left_alive = BaseAlive(&left);
				char right_alive = BaseAlive(&right);
				if(left_alive && right_alive)
				{
					SpawnUnit(rand()%7+1, &left);
					SpawnUnit(rand()%7+1, &right);
				}
				else
				{
					processing = false;
					win = left_alive - right_alive;
				}
			}
		}


		BeginDrawing();
		ClearBackground(RAYWHITE);
		if(!processing)
		{
			if(win == 1)
			{
				DrawText("LEFT SIDE WON!!!", 64, 64, 32, BLACK);
			}
			else if(win == 0)
			{
				DrawText("DRAW", 64, 64, 32, BLACK);
			}
			else if(win == -1)
			{
				DrawText("RIGHT SIDE WON!!!", 64, 64, 32, BLACK);
			}
		}
		BeginMode2D(camera);
		for(int i = 0; i < MAX_UNITS; i++)
		{
			DrawUnitDebug(left.units[i]);
			DrawUnitDebug(right.units[i]);
		}
		for(int i = 0; i < MAX_UNITS; i++)
		{
			DrawUnitDebugAttack(left.units[i]);
			DrawUnitDebugAttack(right.units[i]);
		}
		for(int i = 0; i < MAX_UNITS; i++)
		{
			DrawHealthBar(left.units[i]);
			DrawHealthBar(right.units[i]);
		}
		EndMode2D();
		EndDrawing();

	}

	CloseWindow();

	return 0;
}
