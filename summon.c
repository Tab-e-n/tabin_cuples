#include <raylib.h>
#include <raymath.h>
#include "cuplib.h"
#include "units.h"
#include "summon.h"

Structure StructureInit(void)
{
	Structure structure = (Structure){0};
	return structure;
}

Vector2 StructureMousePos(Vector2 screen_pos, float scale, Vector2 mouse_pos)
{
	mouse_pos = Vector2Subtract(mouse_pos, SCREEN_SIZE_HALF);
	mouse_pos = Vector2Subtract(mouse_pos, screen_pos);
	float scaling = CUP_SIZE_INV / scale;
	mouse_pos.x = mouse_pos.x * scaling * 2;
	mouse_pos.y = mouse_pos.y * scaling;
	mouse_pos.x = (int)mouse_pos.x;
	mouse_pos.y = (int)mouse_pos.y;
	return mouse_pos;
}

bool StructureAddCup(Structure structure, Vector2 pos)
{
}

bool StructureRemoveCup(Structure structure, Vector2 pos)
{
}

UnitType InterpretPlayerStructure(Structure structure)
{
}

void DrawStructureGrid(Vector2 pos, float scale)
{
	for(int i = 0; i < 11; i++)
	{
		Vector2 hori_start = pos;
		hori_start.x += i * CUP_SIZE * 0.5 * scale;
		Vector2 hori_end = hori_start;
		hori_end.y += CUP_SIZE * 5 * scale;
		DrawLineV(hori_start, hori_end, GRAY);
	}

	for(int i = 0; i < 6; i++)
	{
		Vector2 veri_start = pos;
		veri_start.y += i * CUP_SIZE * scale;
		Vector2 veri_end = veri_start;
		veri_end.x += CUP_SIZE * 5 * scale;
		DrawLineV(veri_start, veri_end, GRAY);
	}
}

void DrawStructureDebug(Vector2 pos, float scale)
{
}
