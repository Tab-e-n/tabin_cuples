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
	mouse_pos.x += CUP_SIZE * 2.25;
	mouse_pos.y += CUP_SIZE * 2.25;
	float scaling = CUP_SIZE_INV / scale;
	mouse_pos.x = mouse_pos.x * scaling * 2;
	mouse_pos.y = mouse_pos.y * scaling;
	mouse_pos.x = (int)mouse_pos.x;
	mouse_pos.y = (int)mouse_pos.y;
	return mouse_pos;
}

int StructureCupGridID(Vector2 pos)
{
	if(pos.x < -1 || pos.x >= GRID_SIZE.x)
	{
		return -1;
	}
	if(pos.y < 0 || pos.y >= GRID_SIZE.y)
	{
		return -1;
	}
	if(pos.x == -1)
	{
		pos.x++;
	}
	if(pos.x == GRID_SIZE.x - 1)
	{
		pos.x--;
	}
	return pos.x + pos.y * GRID_SIZE.x;
}

bool StructureAddCup(Structure* structure, Vector2 pos, char cup)
{
	if(structure->cups_present >= 5)
	{
		return false;
	}
	int i = StructureCupGridID(pos);
	if(structure->grid[i + 1] != 0 || structure->grid[i - 1] != 0)
	{
		return false;
	}
	if(structure->grid[i] == 0)
	{
		structure->grid[i] = cup;
		structure->cups_present++;
		return true;
	}
	else
	{
		return false;
	}
}

bool StructureRemoveCup(Structure* structure, Vector2 pos)
{
	if(structure->cups_present <= 0)
	{
		return false;
	}
	int i = StructureCupGridID(pos);
	if(structure->grid[i] != 0)
	{
		structure->grid[i] = 0;
		structure->cups_present--;
		return true;
	}
	else if(structure->grid[i - 1] != 0)
	{
		structure->grid[i - 1] = 0;
		structure->cups_present--;
		return true;
	}
	else
	{
		return false;
	}
}

char StructureCupToCode(Structure structure, int cup, int start_cup)
{
	char code = structure.grid[cup] == 0 ? 0b01 : 0b11;
	code += (cup - start_cup) << 2;
	return code;
}

UnitCode InterpretPlayerStructure(Structure structure)
{
	UnitCode unit = {0};
	char current_code = 0;

	for(int i = 0; i < GRID_AMOUNT; i++)
	{
		if(structure.cups_present == 0)
		{
			break;
		}
		if(structure.grid[i] != 0)
		{
			/*
			 * Array stores id in grid, -1 if no cup
			 * current cup under i is stored first
			 *
			 * while
			 * get current cup id in grin from array
			 * check bottom left, bottom center, bottom right for cups
			 * add their id in grid to array
			 * repeat with next cup in array if there is (!= -1)
			 * end while
			 *
			 * go through array and make UnitCode
			 * go through array and remove found cups from structure
			 * */
			char found_cups[CUPS_PER_UNIT];
			for(int j = 0; j < CUPS_PER_UNIT; j++)
			{
				found_cups[j] = -1;
			}
			found_cups[0] = i;
			char current_cup = 0, cup_amount = 1;
			while(current_cup < CUPS_PER_UNIT)
			{
				char current_i = found_cups[current_cup];
				if(current_i == -1 || cup_amount >= CUPS_PER_UNIT)
				{
				}
				else if(current_i + GRID_SIZE.x >= GRID_AMOUNT)
				{
				}
				else
				{
					current_i += GRID_SIZE.x;
					for(int j = current_i - 1; j <= current_i + 1; j++)
					{
						if(cup_amount >= CUPS_PER_UNIT)
						{
						}
						else if(structure.grid[j] != 0)
						{
							found_cups[cup_amount] = j;
							cup_amount++;
						}
					}
				}

				current_cup++;
			}
			char start_cup = found_cups[0];
			unit.codes[current_code] = StructureCupToCode(structure, start_cup, start_cup);
			current_code++;
			for(int j = 1; j < cup_amount; j++)
			{
				current_cup = found_cups[j];
				unit.codes[current_code] = StructureCupToCode(structure, current_cup, start_cup);
				current_code++;
				structure.grid[current_cup] = 0;
				structure.cups_present--;
			}
		}
	}

	return unit;
}

void DrawStructureGrid(Vector2 pos, float scale)
{
	pos.x -= CUP_SIZE * 2.5;
	pos.y -= CUP_SIZE * 2.5;
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

void DrawStructureDebug(Structure structure, Vector2 pos, float scale)
{
	for(int i = 0; i < GRID_SIZE.y; i++)
	{
		for(int j = 0; j < GRID_SIZE.x; j++)
		{
			int index = i * (int)GRID_SIZE.x + j;
			if(structure.grid[index] != 0)
			{
				Color color = GRAY;
				if(structure.grid[index] == 2)
				{
					color = BLACK;
				}
				Vector2 start = pos;
				start.x += j * CUP_SIZE * 0.5 * scale - CUP_SIZE * 2.5;
				start.y += i * CUP_SIZE * scale - CUP_SIZE * 2.5;
				Vector2 size = (Vector2){CUP_SIZE * scale, CUP_SIZE * scale};
				DrawRectangleV(start, size, color);
			}
		}
	}
}
