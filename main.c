#include <raylib.h>
#include "cuplib.h"
#include "units.h"
#include "summon.h"

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

	const Vector2 LEFT_START_POS = (Vector2){-256, 196}; 
	const Vector2 RIGHT_START_POS = (Vector2){256, 196};

	Side left = SideInit(LEFT_START_POS, 1);
	Side right = SideInit(RIGHT_START_POS, -1);

	/*
	SpawnUnit(UNIT_BASIC, &left, 0);
	SpawnUnit(UNIT_THROWER, &left, 0);
	SpawnUnit(UNIT_TALL, &left, 0);
	SpawnUnit(UNIT_BASIC, &right, 0);
	SpawnUnit(UNIT_THROWER, &right, 0);
	SpawnUnit(UNIT_TALL, &right, 0);
	*/

	bool processing = true;
	char win = 0;
	float resource_timer = 0.0;
	char resource = 3;
	srand(time(0));
	float tempo_spawn_timer = 20.0;

	const Vector2 GRID_POSITION = (Vector2){0, 0};
	Structure structure = StructureInit();

	while(!WindowShouldClose())
	{

		Vector2 mouse_pos = GetMousePosition();
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if(resource > 0)
			{
				if(StructureAddCup(&structure, StructureMousePos(GRID_POSITION, 1, mouse_pos), 1))
				{
					resource--;
				}
			}
			else
			{
				StructureFlipCup(&structure, StructureCupGridID(StructureMousePos(GRID_POSITION, 1, mouse_pos)));
			}
		}
		if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			if(StructureRemoveCup(&structure, StructureMousePos(GRID_POSITION, 1, mouse_pos)))
			{
				resource++;
			}
		}
		if(IsKeyPressed(KEY_ENTER))
		{
			UnitCode unitcode = InterpretPlayerStructure(structure);
			resource += SpawnUnitFromCode(unitcode, &left);
			structure = StructureInit();
		}

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
			if(tempo_spawn_timer > 27.5)
			{
				tempo_spawn_timer = 0.0;
				char left_alive = BaseAlive(&left);
				char right_alive = BaseAlive(&right);
				if(left_alive && right_alive)
				{
					SpawnUnit(rand()%8+2, &right, 0);
				}
				else
				{
					processing = false;
					win = left_alive - right_alive;
				}
			}
			resource_timer += .016;
			if(resource_timer > 10.0)
			{
				resource++;
				resource_timer = 0.0;
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
		DrawStructureGrid(GRID_POSITION, 1);
		DrawStructureDebug(structure, GRID_POSITION, 1);
		DrawText(TextFormat("%i", resource), GRID_POSITION.x, GRID_POSITION.y - 128, 16, BLACK);
		EndMode2D();
		EndDrawing();

	}

	CloseWindow();

	return 0;
}
