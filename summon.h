#ifndef CUPSUMMON
#define CUPSUMMON

#include <raylib.h>
#include <raymath.h>
#include "cuplib.h"
#include "units.h"


typedef struct Structure
{
	char cup_grid[50];
} Structure;


Structure StructureInit(void);

Vector2 StructureMousePos(Vector2 screen_pos, float scale, Vector2 mouse_pos);
bool StructureAddCup(Structure structure, Vector2 pos);
bool StructureRemoveCup(Structure structure, Vector2 pos);

UnitType InterpretPlayerStructure(Structure structure);

void DrawStructureGrid(Vector2 pos, float scale);
void DrawStructureDebug(Vector2 pos, float scale);


#endif
